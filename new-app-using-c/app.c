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

#define MAX_COMMANDS 1000
#define MAX_NAME_LEN 100
#define MAX_DESC_LEN 500
#define MAX_CATEGORY_LEN 100
#define MAX_FLAGS 50
#define MAX_EXAMPLES 50
#define MAX_SEARCH_LEN 100

// Color definitions
#define COLOR_DEFAULT 1
#define COLOR_HIGHLIGHT 2
#define COLOR_ERROR 3
#define COLOR_SUCCESS 4
#define COLOR_MAGENTA 5
#define COLOR_CYAN 6

// Application states
typedef enum {
    STATE_MAIN,
    STATE_DETAIL,
    STATE_EXIT
} AppState;

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
int search_mode = 0;

// Function prototypes
void init_ncurses();
void cleanup_ncurses();
void load_commands();
void save_commands();
void draw_main_screen();
void draw_detail_screen();
void handle_input();
void show_error(const char *msg);

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
        
        // Define color pairs
        init_pair(COLOR_DEFAULT, COLOR_WHITE, COLOR_BLACK);
        init_pair(COLOR_HIGHLIGHT, COLOR_YELLOW, COLOR_BLACK);
        init_pair(COLOR_ERROR, COLOR_RED, COLOR_BLACK);
        init_pair(COLOR_SUCCESS, COLOR_GREEN, COLOR_BLACK);
        init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
    }
    
    // Enable mouse
    mouseinterval(0);
    
    // Clear screen to start
    clear();
    refresh();
}

void cleanup_ncurses() {
    // End ncurses
    endwin();
}

void draw_main_screen() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Clear screen
    erase();  // Use erase() instead of clear() to avoid issues
    
    // Draw border
    border(0, 0, 0, 0, 0, 0, 0, 0);
    
    // Draw search bar
    attron(COLOR_PAIR(COLOR_HIGHLIGHT));
    mvprintw(1, 2, "Search: [");
    attroff(COLOR_PAIR(COLOR_HIGHLIGHT));
    
    // Show search text
    mvprintw(1, 11, "%-*s", max_x - 12, search_text);
    
    attron(COLOR_PAIR(COLOR_HIGHLIGHT));
    mvprintw(1, max_x - 3, "]");
    attroff(COLOR_PAIR(COLOR_HIGHLIGHT));
    
    // Draw separator line
    mvhline(2, 0, ACS_HLINE, max_x);
    
    // Draw column titles
    mvprintw(3, 2, "Commands");
    mvprintw(3, max_x/2 + 2, "Selected Command Preview");
    
    // Draw vertical separator
    mvvline(3, max_x/2, ACS_VLINE, max_y - 7);
    
    // Draw bottom info bar
    mvhline(max_y - 4, 0, ACS_HLINE, max_x);
    attron(A_BOLD);
    mvprintw(max_y - 3, 2, 
            "Ctrl+N:Names  Ctrl+D:Desc  Ctrl+F:Flags  Ctrl+E:Examples  Ctrl+A:All");
    attroff(A_BOLD);
    
    // Draw command list (simplified - left side)
    int visible_items = max_y - 9;
    int start_idx = scroll_offset;
    int end_idx = start_idx + visible_items;
    
    // Simple display without filtering first
    int display_count = 0;
    for (int i = 0; i < command_count && display_count < visible_items; i++) {
        // Simple search filter
        if (search_text[0] != '\0') {
            char name_lower[MAX_NAME_LEN];
            strcpy(name_lower, commands[i].name);
            for (int j = 0; name_lower[j]; j++) name_lower[j] = tolower(name_lower[j]);
            
            char search_lower[MAX_SEARCH_LEN];
            strcpy(search_lower, search_text);
            for (int j = 0; search_lower[j]; j++) search_lower[j] = tolower(search_lower[j]);
            
            if (strstr(name_lower, search_lower) == NULL) {
                // Also check description
                char desc_lower[MAX_DESC_LEN];
                strcpy(desc_lower, commands[i].description);
                for (int j = 0; desc_lower[j]; j++) desc_lower[j] = tolower(desc_lower[j]);
                
                if (strstr(desc_lower, search_lower) == NULL) {
                    continue; // Skip if not found
                }
            }
        }
        
        int list_y = 4 + display_count;
        
        // Highlight selected command
        if (i == selected_index) {
            attron(A_REVERSE);
        }
        
        // Draw bookmark indicator with color
        if (commands[i].bookmarked) {
            attron(COLOR_PAIR(COLOR_MAGENTA));
            mvprintw(list_y, 2, "[*] %s", commands[i].name);
            attroff(COLOR_PAIR(COLOR_MAGENTA));
        } else {
            mvprintw(list_y, 2, "[ ] %s", commands[i].name);
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
        
        // Draw box border
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
        
        // Draw basic example with syntax highlighting
        mvprintw(9, preview_start_x + 2, "Example:");
        attron(COLOR_PAIR(COLOR_CYAN));
        mvprintw(10, preview_start_x + 4, "%s", cmd->basic_example);
        attroff(COLOR_PAIR(COLOR_CYAN));
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
    
    // Draw border
    border(0, 0, 0, 0, 0, 0, 0, 0);
    
    // Draw header
    attron(A_BOLD);
    mvprintw(1, 2, "Command: %s", cmd->name);
    attroff(A_BOLD);
    
    attron(COLOR_PAIR(COLOR_HIGHLIGHT));
    mvprintw(1, max_x - 30, "(press 'b' to bookmark)");
    attroff(COLOR_PAIR(COLOR_HIGHLIGHT));
    
    // Draw separator
    mvhline(2, 1, ACS_HLINE, max_x - 2);
    
    int y_pos = 3;
    
    // Draw description
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
    attron(COLOR_PAIR(COLOR_CYAN));
    mvprintw(y_pos++, 6, "%s", cmd->basic_example);
    attroff(COLOR_PAIR(COLOR_CYAN));
    
    if (strlen(cmd->basic_output) > 0) {
        attron(COLOR_PAIR(COLOR_DEFAULT));
        mvprintw(y_pos++, 6, "Output: %s", cmd->basic_output);
        attroff(COLOR_PAIR(COLOR_DEFAULT));
    }
    
    y_pos++; // Blank line
    
    // Flag-specific examples
    if (cmd->flag_example_count > 0) {
        mvprintw(y_pos++, 4, "With flags:");
        y_pos++;
        
        for (int i = 0; i < cmd->flag_example_count && y_pos < max_y - 5; i++) {
            attron(COLOR_PAIR(COLOR_CYAN));
            mvprintw(y_pos++, 6, "%s", cmd->flag_examples[i]);
            attroff(COLOR_PAIR(COLOR_CYAN));
            
            if (strlen(cmd->flag_example_purposes[i]) > 0) {
                mvprintw(y_pos++, 8, "Purpose: %s", 
                        cmd->flag_example_purposes[i]);
            }
            
            if (strlen(cmd->flag_example_outputs[i]) > 0) {
                attron(COLOR_PAIR(COLOR_DEFAULT));
                mvprintw(y_pos++, 8, "Output: %s", 
                        cmd->flag_example_outputs[i]);
                attroff(COLOR_PAIR(COLOR_DEFAULT));
            }
            
            y_pos++; // Blank line between examples
        }
    }
    
    // Draw footer
    mvhline(max_y - 2, 1, ACS_HLINE, max_x - 2);
    attron(COLOR_PAIR(COLOR_HIGHLIGHT));
    mvprintw(max_y - 1, 2, "(press Backspace to return)");
    attroff(COLOR_PAIR(COLOR_HIGHLIGHT));
    
    refresh();
}

void show_error(const char *msg) {
    printf("Error: %s\n", msg);
    exit(1);
}

int main() {
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
                            // Clear search
                            search_text[0] = '\0';
                            selected_index = 0;
                            scroll_offset = 0;
                            break;
                            
                        case 'b':
                        case 'B':
                            // Toggle bookmark
                            if (selected_index < command_count) {
                                commands[selected_index].bookmarked = !commands[selected_index].bookmarked;
                                save_commands();
                            }
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