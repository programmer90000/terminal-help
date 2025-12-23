#include <ncursesw/ncurses.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>

#define MAX_COMMANDS 1000
#define MAX_NAME_LEN 100
#define MAX_DESC_LEN 500
#define MAX_CATEGORY_LEN 100
#define MAX_FLAGS 50
#define MAX_EXAMPLES 50
#define MAX_SEARCH_LEN 100

// Color pair definitions (must be > 0)
#define COLOR_PAIR_DEFAULT 1
#define COLOR_PAIR_HIGHLIGHT 2
#define COLOR_PAIR_ERROR 3
#define COLOR_PAIR_SUCCESS 4
#define COLOR_PAIR_MAGENTA 5
#define COLOR_PAIR_CYAN 6
#define COLOR_PAIR_GREEN 7

// 256-color palette indices (standardized across terminals)
#define COLOR_256_WHITE     15    // Bright white
#define COLOR_256_BLACK     0     // Pure black (index 0)
#define COLOR_256_BLACK2    16    // Alternate pure black (also works)
#define COLOR_256_RED       9     // Bright red
#define COLOR_256_GREEN     10    // Bright green
#define COLOR_256_YELLOW    11    // Bright yellow
#define COLOR_256_BLUE      12    // Bright blue
#define COLOR_256_MAGENTA   13    // Bright magenta
#define COLOR_256_CYAN      14    // Bright cyan

// Application states
typedef enum {
    STATE_MAIN,
    STATE_DETAIL,
    STATE_EXIT
} AppState;

// Search mode flags (bitmask for multiple selection)
#define SEARCH_NAMES    (1 << 0)
#define SEARCH_DESCS    (1 << 1)
#define SEARCH_FLAGS    (1 << 2)
#define SEARCH_EXAMPLES (1 << 3)

// Command structure
typedef struct {
    char name[MAX_NAME_LEN];
    char description[MAX_DESC_LEN];
    char category[MAX_CATEGORY_LEN];
    int bookmarked;
    
    // Flags as key-value pairs
    char flag_names[MAX_FLAGS][20];
    char flag_descs[MAX_FLAGS][100];
    int flag_count;
    
    // Examples
    char basic_example[200];
    char basic_output[200];
    
    // Flag-specific examples
    char flag_examples[MAX_FLAGS][100];
    char flag_example_outputs[MAX_FLAGS][200];
    char flag_example_purposes[MAX_FLAGS][100];
    int flag_example_count;
} Command;

// Global variables
Command commands[MAX_COMMANDS];
int command_count = 0;
int selected_index = 0;
int scroll_offset = 0;
int detail_scroll = 0;
AppState current_state = STATE_MAIN;
char search_text[MAX_SEARCH_LEN] = "";
int search_mode = 0;  // Bitmask for search modes (0 = no mode selected)

// Function prototypes
void init_ncurses();
void cleanup_ncurses();
void handle_signal(int sig);
void load_commands();
void save_commands();
void draw_main_screen();
void draw_detail_screen();
void handle_input();
void show_error(const char *msg);
int matches_search(Command *cmd, const char *search_lower);

// Signal handler and cleanup function
void handle_signal(int sig) {
    cleanup_ncurses();
    exit(0);
}

void cleanup_ncurses() {
    endwin();  // CRITICAL: Restores terminal to original state
}

// Check if a command matches the current search criteria
int matches_search(Command *cmd, const char *search_lower) {
    if (search_mode == 0) {
        // If no search mode selected, search all fields
        return 1;
    }
    
    int found = 0;
    
    // Check names
    if (search_mode & SEARCH_NAMES) {
        char name_lower[MAX_NAME_LEN];
        strcpy(name_lower, cmd->name);
        for (int j = 0; name_lower[j]; j++) name_lower[j] = tolower(name_lower[j]);
        if (strstr(name_lower, search_lower) != NULL) {
            found = 1;
        }
    }
    
    // Check descriptions
    if (!found && (search_mode & SEARCH_DESCS)) {
        char desc_lower[MAX_DESC_LEN];
        strcpy(desc_lower, cmd->description);
        for (int j = 0; desc_lower[j]; j++) desc_lower[j] = tolower(desc_lower[j]);
        if (strstr(desc_lower, search_lower) != NULL) {
            found = 1;
        }
    }
    
    // Check flags
    if (!found && (search_mode & SEARCH_FLAGS)) {
        for (int f = 0; f < cmd->flag_count && !found; f++) {
            char flag_name_lower[20];
            char flag_desc_lower[100];
            
            strcpy(flag_name_lower, cmd->flag_names[f]);
            for (int j = 0; flag_name_lower[j]; j++) flag_name_lower[j] = tolower(flag_name_lower[j]);
            
            strcpy(flag_desc_lower, cmd->flag_descs[f]);
            for (int j = 0; flag_desc_lower[j]; j++) flag_desc_lower[j] = tolower(flag_desc_lower[j]);
            
            if (strstr(flag_name_lower, search_lower) != NULL ||
                strstr(flag_desc_lower, search_lower) != NULL) {
                found = 1;
                break;
            }
        }
    }
    
    // Check examples
    if (!found && (search_mode & SEARCH_EXAMPLES)) {
        // Check basic example
        char basic_example_lower[200];
        strcpy(basic_example_lower, cmd->basic_example);
        for (int j = 0; basic_example_lower[j]; j++) basic_example_lower[j] = tolower(basic_example_lower[j]);
        if (strstr(basic_example_lower, search_lower) != NULL) {
            found = 1;
        }
        
        // Check flag examples
        if (!found) {
            for (int e = 0; e < cmd->flag_example_count && !found; e++) {
                char example_lower[100];
                char purpose_lower[100];
                char output_lower[200];
                
                strcpy(example_lower, cmd->flag_examples[e]);
                for (int j = 0; example_lower[j]; j++) example_lower[j] = tolower(example_lower[j]);
                
                strcpy(purpose_lower, cmd->flag_example_purposes[e]);
                for (int j = 0; purpose_lower[j]; j++) purpose_lower[j] = tolower(purpose_lower[j]);
                
                strcpy(output_lower, cmd->flag_example_outputs[e]);
                for (int j = 0; output_lower[j]; j++) output_lower[j] = tolower(output_lower[j]);
                
                if (strstr(example_lower, search_lower) != NULL ||
                    strstr(purpose_lower, search_lower) != NULL ||
                    strstr(output_lower, search_lower) != NULL) {
                    found = 1;
                    break;
                }
            }
        }
    }
    
    return found;
}

// Load commands from JSON file
void load_commands() {
    FILE *file = fopen("commands.json", "r");
    if (!file) {
        show_error("Could not open commands.json");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *json_data = malloc(file_size + 1);
    if (!json_data) {
        fclose(file);
        show_error("Memory allocation failed");
        return;
    }
    
    fread(json_data, 1, file_size, file);
    json_data[file_size] = '\0';
    fclose(file);
    
    json_error_t error;
    json_t *root = json_loads(json_data, 0, &error);
    free(json_data);
    
    if (!root) {
        char err_msg[200];
        snprintf(err_msg, sizeof(err_msg), 
                "JSON parsing error at line %d, column %d: %s",
                error.line, error.column, error.text);
        show_error(err_msg);
        return;
    }
    
    json_t *commands_array = json_object_get(root, "commands");
    if (!json_is_array(commands_array)) {
        json_decref(root);
        show_error("Invalid JSON structure: 'commands' not found or not an array");
        return;
    }
    
    command_count = 0;
    size_t index;
    json_t *value;
    
    json_array_foreach(commands_array, index, value) {
        if (command_count >= MAX_COMMANDS) break;
        
        Command *cmd = &commands[command_count];
        memset(cmd, 0, sizeof(Command));
        
        // Parse basic fields
        json_t *name = json_object_get(value, "name");
        json_t *desc = json_object_get(value, "description");
        json_t *category = json_object_get(value, "category");
        json_t *bookmarked = json_object_get(value, "bookmarked");
        
        if (name) strncpy(cmd->name, json_string_value(name), MAX_NAME_LEN-1);
        if (desc) strncpy(cmd->description, json_string_value(desc), MAX_DESC_LEN-1);
        if (category) strncpy(cmd->category, json_string_value(category), MAX_CATEGORY_LEN-1);
        if (bookmarked) cmd->bookmarked = json_is_true(bookmarked);
        
        // Parse flags
        json_t *flags = json_object_get(value, "flags");
        if (flags && json_is_object(flags)) {
            const char *flag_key;
            json_t *flag_value;
            cmd->flag_count = 0;
            
            json_object_foreach(flags, flag_key, flag_value) {
                if (cmd->flag_count >= MAX_FLAGS) break;
                
                strncpy(cmd->flag_names[cmd->flag_count], flag_key, 19);
                strncpy(cmd->flag_descs[cmd->flag_count], 
                       json_string_value(flag_value), 99);
                cmd->flag_count++;
            }
        }
        
        // Parse examples
        json_t *examples = json_object_get(value, "examples");
        if (examples && json_is_object(examples)) {
            // Basic example
            json_t *basic = json_object_get(examples, "basic");
            if (basic && json_is_object(basic)) {
                json_t *cmd_run = json_object_get(basic, "command");
                json_t *output = json_object_get(basic, "output");
                
                if (cmd_run) strncpy(cmd->basic_example, 
                                   json_string_value(cmd_run), 199);
                if (output) strncpy(cmd->basic_output, 
                                  json_string_value(output), 199);
            }
            
            // Flag-specific examples
            json_t *with_flags = json_object_get(examples, "with_flags");
            if (with_flags && json_is_object(with_flags)) {
                const char *example_key;
                json_t *example_value;
                cmd->flag_example_count = 0;
                
                json_object_foreach(with_flags, example_key, example_value) {
                    if (cmd->flag_example_count >= MAX_EXAMPLES) break;
                    
                    strncpy(cmd->flag_examples[cmd->flag_example_count], 
                           example_key, 99);
                    
                    json_t *purpose = json_object_get(example_value, "purpose");
                    json_t *example_output = json_object_get(example_value, "output");
                    
                    if (purpose) strncpy(cmd->flag_example_purposes[cmd->flag_example_count],
                                       json_string_value(purpose), 99);
                    if (example_output) strncpy(cmd->flag_example_outputs[cmd->flag_example_count],
                                              json_string_value(example_output), 199);
                    
                    cmd->flag_example_count++;
                }
            }
        }
        
        command_count++;
    }
    
    json_decref(root);
}

// Save commands back to JSON file
void save_commands() {
    json_t *root = json_object();
    json_t *commands_array = json_array();
    
    for (int i = 0; i < command_count; i++) {
        Command *cmd = &commands[i];
        
        json_t *command_obj = json_object();
        json_object_set_new(command_obj, "name", json_string(cmd->name));
        json_object_set_new(command_obj, "description", json_string(cmd->description));
        json_object_set_new(command_obj, "category", json_string(cmd->category));
        json_object_set_new(command_obj, "bookmarked", json_boolean(cmd->bookmarked));
        
        // Add flags
        json_t *flags_obj = json_object();
        for (int j = 0; j < cmd->flag_count; j++) {
            json_object_set_new(flags_obj, cmd->flag_names[j], 
                              json_string(cmd->flag_descs[j]));
        }
        json_object_set_new(command_obj, "flags", flags_obj);
        
        // Add examples
        json_t *examples_obj = json_object();
        
        // Basic example
        json_t *basic_obj = json_object();
        json_object_set_new(basic_obj, "command", json_string(cmd->basic_example));
        json_object_set_new(basic_obj, "output", json_string(cmd->basic_output));
        json_object_set_new(examples_obj, "basic", basic_obj);
        
        // Flag-specific examples
        json_t *with_flags_obj = json_object();
        for (int j = 0; j < cmd->flag_example_count; j++) {
            json_t *example_obj = json_object();
            json_object_set_new(example_obj, "purpose", 
                              json_string(cmd->flag_example_purposes[j]));
            json_object_set_new(example_obj, "output", 
                              json_string(cmd->flag_example_outputs[j]));
            json_object_set_new(with_flags_obj, cmd->flag_examples[j], example_obj);
        }
        json_object_set_new(examples_obj, "with_flags", with_flags_obj);
        
        json_object_set_new(command_obj, "examples", examples_obj);
        json_array_append_new(commands_array, command_obj);
    }
    
    json_object_set_new(root, "commands", commands_array);
    
    // Write to file
    char *json_str = json_dumps(root, JSON_INDENT(2));
    if (json_str) {
        FILE *file = fopen("commands.json", "w");
        if (file) {
            fputs(json_str, file);
            fclose(file);
        }
        free(json_str);
    }
    
    json_decref(root);
}

void init_ncurses() {
    // Set locale for UTF-8 support
    setlocale(LC_ALL, "");
    
    // Initialize ncurses
    if (initscr() == NULL) {
        fprintf(stderr, "Error: Could not initialize ncurses\n");
        exit(1);
    }
    
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    curs_set(0); // Hide cursor
    
    // Check for color support
    if (has_colors()) {
        start_color();
        
        // DO NOT use default colors if you want black background
        // use_default_colors();  // COMMENT THIS LINE OUT
        
        // Check if we have extended color support
        if (COLORS >= 256) {
            // Some terminals map index 0 to something else
            // Index 16 is usually the first user-definable color (pure black in default palette)
            init_pair(COLOR_PAIR_DEFAULT, 15, 16);  // White on black
            init_pair(COLOR_PAIR_HIGHLIGHT, 11, 16); // Yellow on black
            init_pair(COLOR_PAIR_ERROR, 9, 16);     // Red on black
            init_pair(COLOR_PAIR_SUCCESS, 10, 16);  // Green on black
            init_pair(COLOR_PAIR_MAGENTA, 13, 16);  // Magenta on black
            init_pair(COLOR_PAIR_CYAN, 14, 16);     // Cyan on black
            init_pair(COLOR_PAIR_GREEN, 10, 16);    // Green on black (for highlighting)
        } else {
            // Fallback to basic 16 colors
            // White on black
            init_pair(COLOR_PAIR_DEFAULT, COLOR_WHITE, COLOR_BLACK);
            init_pair(COLOR_PAIR_HIGHLIGHT, COLOR_YELLOW, COLOR_BLACK);
            init_pair(COLOR_PAIR_ERROR, COLOR_RED, COLOR_BLACK);
            init_pair(COLOR_PAIR_SUCCESS, COLOR_GREEN, COLOR_BLACK);
            init_pair(COLOR_PAIR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
            init_pair(COLOR_PAIR_CYAN, COLOR_CYAN, COLOR_BLACK);
            init_pair(COLOR_PAIR_GREEN, COLOR_GREEN, COLOR_BLACK);
        }
        
        // Set the entire screen background
        bkgd(COLOR_PAIR(COLOR_PAIR_DEFAULT));
        
        // Set default color
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    }
    
    // Enable mouse
    mouseinterval(0);
    
    // Clear screen to start
    clear();
    refresh();
}

void draw_main_screen() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Clear screen
    erase();
    
    // Draw border with default color
    attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    border(0, 0, 0, 0, 0, 0, 0, 0);
    
    // Draw search bar with mode indicator
    attron(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
    
    // Build mode string
    char mode_str[50] = "";
    if (search_mode == 0) {
        strcpy(mode_str, "ALL");
    } else {
        if (search_mode & SEARCH_NAMES) strcat(mode_str, "N");
        if (search_mode & SEARCH_DESCS) {
            if (mode_str[0]) strcat(mode_str, "+");
            strcat(mode_str, "D");
        }
        if (search_mode & SEARCH_FLAGS) {
            if (mode_str[0]) strcat(mode_str, "+");
            strcat(mode_str, "F");
        }
        if (search_mode & SEARCH_EXAMPLES) {
            if (mode_str[0]) strcat(mode_str, "+");
            strcat(mode_str, "E");
        }
    }
    
    mvprintw(1, 2, "Search [%s]: [", mode_str);
    attroff(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
    
    // Show search text with default color
    attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    mvprintw(1, 14 + strlen(mode_str), "%-*s", max_x - 15 - (int)strlen(mode_str), search_text);
    attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    
    attron(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
    mvprintw(1, max_x - 3, "]");
    attroff(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
    
    // Draw separator line
    attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    mvhline(2, 0, ACS_HLINE, max_x);
    
    // Draw column titles
    mvprintw(3, 2, "Commands");
    mvprintw(3, max_x/2 + 2, "Selected Command Preview");
    
    // Draw vertical separator
    mvvline(3, max_x/2, ACS_VLINE, max_y - 7);
    
    // Draw bottom info bar with highlighted active modes
    mvhline(max_y - 4, 0, ACS_HLINE, max_x);
    
    // Calculate positions for each shortcut
    int start_x = 2;
    int spacing = 3;
    
    // Ctrl+N:Names
    if (search_mode & SEARCH_NAMES) {
        attron(COLOR_PAIR(COLOR_PAIR_GREEN) | A_BOLD);
    } else {
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT) | A_BOLD);
    }
    mvprintw(max_y - 3, start_x, "Ctrl+N:Names");
    attroff(A_BOLD);
    
    // Ctrl+D:Desc
    start_x += 13 + spacing;
    if (search_mode & SEARCH_DESCS) {
        attron(COLOR_PAIR(COLOR_PAIR_GREEN) | A_BOLD);
    } else {
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT) | A_BOLD);
    }
    mvprintw(max_y - 3, start_x, "Ctrl+D:Desc");
    attroff(A_BOLD);
    
    // Ctrl+F:Flags
    start_x += 11 + spacing;
    if (search_mode & SEARCH_FLAGS) {
        attron(COLOR_PAIR(COLOR_PAIR_GREEN) | A_BOLD);
    } else {
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT) | A_BOLD);
    }
    mvprintw(max_y - 3, start_x, "Ctrl+F:Flags");
    attroff(A_BOLD);
    
    // Ctrl+E:Examples
    start_x += 12 + spacing;
    if (search_mode & SEARCH_EXAMPLES) {
        attron(COLOR_PAIR(COLOR_PAIR_GREEN) | A_BOLD);
    } else {
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT) | A_BOLD);
    }
    mvprintw(max_y - 3, start_x, "Ctrl+E:Examples");
    attroff(A_BOLD);
    
    attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    
    // Draw command list
    int visible_items = max_y - 9;
    int start_idx = scroll_offset;
    
    // Filter and display commands
    int display_count = 0;
    char search_lower[MAX_SEARCH_LEN] = "";
    
    // Convert search text to lowercase if it exists
    if (search_text[0] != '\0') {
        strcpy(search_lower, search_text);
        for (int j = 0; search_lower[j]; j++) search_lower[j] = tolower(search_lower[j]);
    }
    
    for (int i = 0; i < command_count && display_count < visible_items; i++) {
        // Apply search filter if search text exists
        if (search_text[0] != '\0') {
            // If no search mode is selected, search all fields
            if (search_mode == 0) {
                // Check all fields
                char name_lower[MAX_NAME_LEN];
                strcpy(name_lower, commands[i].name);
                for (int j = 0; name_lower[j]; j++) name_lower[j] = tolower(name_lower[j]);
                
                char desc_lower[MAX_DESC_LEN];
                strcpy(desc_lower, commands[i].description);
                for (int j = 0; desc_lower[j]; j++) desc_lower[j] = tolower(desc_lower[j]);
                
                if (strstr(name_lower, search_lower) == NULL &&
                    strstr(desc_lower, search_lower) == NULL) {
                    // Also check other fields if needed
                    continue;
                }
            } else {
                // Use the matches_search function for selected modes
                if (!matches_search(&commands[i], search_lower)) {
                    continue;
                }
            }
        }
        
        int list_y = 4 + display_count;
        
        // Highlight selected command
        if (i == selected_index) {
            attron(A_REVERSE);
        }
        
        // Draw bookmark indicator with magenta color
        if (commands[i].bookmarked) {
            attron(COLOR_PAIR(COLOR_PAIR_MAGENTA));
            mvprintw(list_y, 2, "[*] %s", commands[i].name);
            attroff(COLOR_PAIR(COLOR_PAIR_MAGENTA));
        } else {
            attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
            mvprintw(list_y, 2, "[ ] %s", commands[i].name);
            attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
        }
        
        if (i == selected_index) {
            attroff(A_REVERSE);
        }
        
        display_count++;
    }
    
    // Draw preview of selected command (right side)
    if (selected_index >= 0 && selected_index < command_count) {
        Command *cmd = &commands[selected_index];
        
        // Draw a simple box for preview
        int preview_start_x = max_x/2 + 1;
        int preview_width = max_x/2 - 1;
        
        // Draw box border with default color
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
        mvaddch(4, preview_start_x, ACS_ULCORNER);
        mvaddch(4, max_x - 1, ACS_URCORNER);
        mvaddch(max_y - 5, preview_start_x, ACS_LLCORNER);
        mvaddch(max_y - 5, max_x - 1, ACS_LRCORNER);
        
        for (int x = preview_start_x + 1; x < max_x - 1; x++) {
            mvaddch(4, x, ACS_HLINE);
            mvaddch(max_y - 5, x, ACS_HLINE);
        }
        
        for (int y = 5; y < max_y - 5; y++) {
            mvaddch(y, preview_start_x, ACS_VLINE);
            mvaddch(y, max_x - 1, ACS_VLINE);
        }
        
        // Draw command info
        mvprintw(5, preview_start_x + 2, "Name: %s", cmd->name);
        mvprintw(6, preview_start_x + 2, "Desc: %s", cmd->description);
        
        // Draw flags (first few only)
        mvprintw(7, preview_start_x + 2, "Flags: ");
        int x_pos = preview_start_x + 9;
        for (int i = 0; i < cmd->flag_count && i < 4; i++) {
            int flag_len = (int)strlen(cmd->flag_names[i]);
            if (x_pos + flag_len + 2 < max_x - 1) {
                mvprintw(7, x_pos, "%s", cmd->flag_names[i]);
                x_pos += flag_len + 2;
            }
        }
        
        // Draw basic example with cyan color
        mvprintw(9, preview_start_x + 2, "Example:");
        attron(COLOR_PAIR(COLOR_PAIR_CYAN));
        mvprintw(10, preview_start_x + 4, "%s", cmd->basic_example);
        attroff(COLOR_PAIR(COLOR_PAIR_CYAN));
        attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    }
    
    refresh();
}

void draw_detail_screen() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Check bounds
    if (selected_index < 0 || selected_index >= command_count) {
        // Invalid index, go back to main screen
        current_state = STATE_MAIN;
        draw_main_screen();
        return;
    }
    
    Command *cmd = &commands[selected_index];
    
    // Clear screen
    erase();
    
    // Draw border with default color
    attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    border(0, 0, 0, 0, 0, 0, 0, 0);
    
    // Draw header
    attron(A_BOLD);
    mvprintw(1, 2, "Command: %s", cmd->name);
    attroff(A_BOLD);
    
    attron(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
    mvprintw(1, max_x - 30, "(press 'b' to bookmark)");
    attroff(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
    
    // Draw separator
    mvhline(2, 1, ACS_HLINE, max_x - 2);
    
    int y_pos = 3;
    
    // Draw description with default color
    attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    mvprintw(y_pos++, 2, "Description: %s", cmd->description);
    y_pos++; // Blank line
    
    // Draw category
    mvprintw(y_pos++, 2, "Category: %s", cmd->category);
    y_pos++; // Blank line
    
    // Draw flags section
    mvprintw(y_pos++, 2, "Flags:");
    y_pos++;
    
    for (int i = 0; i < cmd->flag_count && y_pos < max_y - 5; i++) {
        mvprintw(y_pos++, 4, "%s: %s", 
                cmd->flag_names[i], cmd->flag_descs[i]);
    }
    
    y_pos++; // Blank line
    
    // Draw examples section
    mvprintw(y_pos++, 2, "Examples:");
    y_pos++;
    
    // Basic example
    mvprintw(y_pos++, 4, "Basic:");
    attron(COLOR_PAIR(COLOR_PAIR_CYAN));
    mvprintw(y_pos++, 6, "%s", cmd->basic_example);
    attroff(COLOR_PAIR(COLOR_PAIR_CYAN));
    
    if (strlen(cmd->basic_output) > 0) {
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
        mvprintw(y_pos++, 6, "Output: %s", cmd->basic_output);
        attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    }
    
    y_pos++; // Blank line
    
    // Flag-specific examples
    if (cmd->flag_example_count > 0) {
        mvprintw(y_pos++, 4, "With flags:");
        y_pos++;
        
        for (int i = 0; i < cmd->flag_example_count && y_pos < max_y - 5; i++) {
            attron(COLOR_PAIR(COLOR_PAIR_CYAN));
            mvprintw(y_pos++, 6, "%s", cmd->flag_examples[i]);
            attroff(COLOR_PAIR(COLOR_PAIR_CYAN));
            
            if (strlen(cmd->flag_example_purposes[i]) > 0) {
                attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
                mvprintw(y_pos++, 8, "Purpose: %s", 
                        cmd->flag_example_purposes[i]);
                attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
            }
            
            if (strlen(cmd->flag_example_outputs[i]) > 0) {
                attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
                mvprintw(y_pos++, 8, "Output: %s", 
                        cmd->flag_example_outputs[i]);
                attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
            }
            
            y_pos++; // Blank line between examples
        }
    }
    
    // Draw footer
    mvhline(max_y - 2, 1, ACS_HLINE, max_x - 2);
    attron(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
    mvprintw(max_y - 1, 2, "(press Backspace to return)");
    attroff(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
    attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    
    refresh();
}

void show_error(const char *msg) {
    printf("Error: %s\n", msg);
    exit(1);
}

int main() {
    // Set up signal handlers for clean exit
    signal(SIGINT, handle_signal);
    atexit(cleanup_ncurses);
    
    // Load commands from JSON
    load_commands();
    
    if (command_count == 0) {
        printf("No commands loaded. Please check commands.json file.\n");
        return 1;
    }
    
    // Initialize ncurses
    init_ncurses();
    
    // Draw initial screen
    draw_main_screen();
    
    // Main input loop
    int ch;
    while ((ch = getch()) != KEY_F(1)) { // F1 to exit
        switch (current_state) {
            case STATE_MAIN:
                {
                    int max_y, max_x;
                    getmaxyx(stdscr, max_y, max_x);
                    int visible_items = max_y - 9;
                    
                    switch (ch) {
                        case KEY_UP:
                            if (selected_index > 0) {
                                selected_index--;
                                if (selected_index < scroll_offset) {
                                    scroll_offset = selected_index;
                                }
                            }
                            break;
                            
                        case KEY_DOWN:
                            if (selected_index < command_count - 1) {
                                selected_index++;
                                if (selected_index >= scroll_offset + visible_items) {
                                    scroll_offset = selected_index - visible_items + 1;
                                }
                            }
                            break;
                            
                        case 10: // Enter key
                            if (command_count > 0) {
                                current_state = STATE_DETAIL;
                                detail_scroll = 0;
                            }
                            break;
                            
                        case KEY_BACKSPACE:
                        case 127: // Backspace/Delete
                            // Remove last character from search text
                            int len = strlen(search_text);
                            if (len > 0) {
                                search_text[len - 1] = '\0';
                                selected_index = 0;
                                scroll_offset = 0;
                            }
                            break;
                            
                        case 'b':
                        case 'B':
                            // Toggle bookmark
                            if (selected_index < command_count) {
                                commands[selected_index].bookmarked = !commands[selected_index].bookmarked;
                                save_commands();
                            }
                            break;
                            
                        // Handle Ctrl+key combinations
                        case 14:  // Ctrl+N (ASCII 14)
                            // Toggle search in names
                            search_mode ^= SEARCH_NAMES;
                            selected_index = 0;
                            scroll_offset = 0;
                            break;
                            
                        case 4:   // Ctrl+D (ASCII 4)
                            // Toggle search in descriptions
                            search_mode ^= SEARCH_DESCS;
                            selected_index = 0;
                            scroll_offset = 0;
                            break;
                            
                        case 6:   // Ctrl+F (ASCII 6)
                            // Toggle search in flags
                            search_mode ^= SEARCH_FLAGS;
                            selected_index = 0;
                            scroll_offset = 0;
                            break;
                            
                        case 5:   // Ctrl+E (ASCII 5)
                            // Toggle search in examples
                            search_mode ^= SEARCH_EXAMPLES;
                            selected_index = 0;
                            scroll_offset = 0;
                            break;
                            
                        default:
                            // Handle text input for search
                            if (isprint(ch) && strlen(search_text) < MAX_SEARCH_LEN - 1) {
                                strncat(search_text, (char*)&ch, 1);
                                selected_index = 0;
                                scroll_offset = 0;
                            }
                            break;
                    }
                    draw_main_screen();
                }
                break;
                
            case STATE_DETAIL:
                switch (ch) {
                    case KEY_BACKSPACE:
                    case 127: // Backspace
                        current_state = STATE_MAIN;
                        draw_main_screen();
                        break;
                        
                    case 'b':
                    case 'B':
                        // Toggle bookmark
                        if (selected_index < command_count) {
                            commands[selected_index].bookmarked = !commands[selected_index].bookmarked;
                            save_commands();
                            draw_detail_screen();
                        }
                        break;
                        
                    case KEY_UP:
                        if (detail_scroll > 0) {
                            detail_scroll--;
                        }
                        break;
                        
                    case KEY_DOWN:
                        detail_scroll++;
                        break;
                }
                
                if (current_state == STATE_DETAIL) {
                    draw_detail_screen();
                }
                break;
        }
    }
    
    // Cleanup
    cleanup_ncurses();
    
    return 0;
}