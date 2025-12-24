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
#define MAX_CATEGORIES 50
#define MAX_CAT_NAME_LEN 50

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

// Category filtering variables
char categories[MAX_CATEGORIES][MAX_CAT_NAME_LEN];
int category_count = 0;
int category_filter = -1;  // -1 means no filter, otherwise index in categories array
int show_bookmarks_only = 0;  // New: bookmark-only filter

// Helper: Filtered command indices
int filtered_indices[MAX_COMMANDS];
int filtered_count = 0;

// Function prototypes
void init_ncurses();
void cleanup_ncurses();
void handle_signal(int sig);
void load_commands();
void save_commands();
void update_filtered_indices();  // New function
void draw_main_screen();
void draw_detail_screen();
void show_category_menu();
void show_status_message(const char *msg, int color_pair);
void show_error(const char *msg);
int matches_search(Command *cmd, const char *search_lower);
int find_first_filtered_command();  // New function
int find_prev_filtered_command(int current_index);  // New function
int find_next_filtered_command(int current_index);  // New function
int find_last_filtered_command();  // New function

// Signal handler and cleanup function
void handle_signal(int sig) {
    cleanup_ncurses();
    exit(0);
}

void cleanup_ncurses() {
    endwin();  // CRITICAL: Restores terminal to original state
}

// Update the filtered_indices array based on current filters
void update_filtered_indices() {
    filtered_count = 0;
    char search_lower[MAX_SEARCH_LEN] = "";
    
    // Convert search text to lowercase if it exists
    if (search_text[0] != '\0') {
        strcpy(search_lower, search_text);
        for (int j = 0; search_lower[j]; j++) search_lower[j] = tolower(search_lower[j]);
    }
    
    for (int i = 0; i < command_count; i++) {
        // Apply bookmark filter first
        if (show_bookmarks_only && !commands[i].bookmarked) {
            continue;
        }
        
        // Apply category filter
        if (category_filter != -1 && 
            strcmp(commands[i].category, categories[category_filter]) != 0) {
            continue;
        }
        
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
                    continue;  // Skip non-matching commands
                }
            } else {
                // Use the matches_search function for selected modes
                if (!matches_search(&commands[i], search_lower)) {
                    continue;  // Skip non-matching commands
                }
            }
        }
        filtered_indices[filtered_count++] = i;
    }
}

// Find the first command that passes current filters
int find_first_filtered_command() {
    update_filtered_indices();
    if (filtered_count > 0) {
        return filtered_indices[0];
    }
    return 0;  // Fallback
}

// Find the previous filtered command relative to current_index
int find_prev_filtered_command(int current_index) {
    update_filtered_indices();
    
    if (filtered_count == 0) return current_index;
    
    // Find current position in filtered array
    int current_filtered_pos = -1;
    for (int i = 0; i < filtered_count; i++) {
        if (filtered_indices[i] == current_index) {
            current_filtered_pos = i;
            break;
        }
    }
    
    // If not found, return first filtered
    if (current_filtered_pos == -1) {
        return filtered_indices[0];
    }
    
    // If at first position, wrap to last
    if (current_filtered_pos == 0) {
        return filtered_indices[0];  // Stay at first
    }
    
    return filtered_indices[current_filtered_pos - 1];
}

// Find the next filtered command relative to current_index
int find_next_filtered_command(int current_index) {
    update_filtered_indices();
    
    if (filtered_count == 0) return current_index;
    
    // Find current position in filtered array
    int current_filtered_pos = -1;
    for (int i = 0; i < filtered_count; i++) {
        if (filtered_indices[i] == current_index) {
            current_filtered_pos = i;
            break;
        }
    }
    
    // If not found, return first filtered
    if (current_filtered_pos == -1) {
        return filtered_indices[0];
    }
    
    // If at last position, stay there
    if (current_filtered_pos == filtered_count - 1) {
        return filtered_indices[filtered_count - 1];
    }
    
    return filtered_indices[current_filtered_pos + 1];
}

// Find the last command that passes current filters
int find_last_filtered_command() {
    update_filtered_indices();
    if (filtered_count > 0) {
        return filtered_indices[filtered_count - 1];
    }
    return 0;  // Fallback
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
    category_count = 0;
    category_filter = -1;  // Reset filter
    
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
        if (category) {
            strncpy(cmd->category, json_string_value(category), MAX_CATEGORY_LEN-1);
            
            // Add to unique categories list
            int found = 0;
            for (int i = 0; i < category_count; i++) {
                if (strcmp(categories[i], cmd->category) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found && category_count < MAX_CATEGORIES) {
                strncpy(categories[category_count], cmd->category, MAX_CAT_NAME_LEN-1);
                category_count++;
            }
        }
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
    
    // Initialize filtered indices after loading
    update_filtered_indices();
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

void show_status_message(const char *msg, int color_pair) {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Save area under message
    char saved[max_x - 30];
    for (int i = 0; i < max_x - 30; i++) {
        saved[i] = mvinch(max_y - 1, 2 + i) & A_CHARTEXT;
    }
    
    // Show message
    attron(COLOR_PAIR(color_pair) | A_BOLD);
    mvprintw(max_y - 1, 2, "%-*s", max_x - 4, msg);
    attroff(COLOR_PAIR(color_pair) | A_BOLD);
    
    refresh();
    napms(1500);  // Show for 1.5 seconds
    
    // Restore area
    attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    for (int i = 0; i < max_x - 30; i++) {
        mvaddch(max_y - 1, 2 + i, saved[i]);
    }
    attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    
    refresh();
}

void show_category_menu() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Create a centered window for category selection
    int win_height = category_count + 8;
    if (win_height > max_y - 4) win_height = max_y - 4;
    int win_width = 50;
    int start_y = (max_y - win_height) / 2;
    int start_x = (max_x - win_width) / 2;
    
    WINDOW *cat_win = newwin(win_height, win_width, start_y, start_x);
    wbkgd(cat_win, COLOR_PAIR(COLOR_PAIR_DEFAULT));
    box(cat_win, 0, 0);
    
    // Title
    wattron(cat_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
    mvwprintw(cat_win, 1, (win_width - 20) / 2, "Select Category");
    wattroff(cat_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
    
    // Draw categories
    wattron(cat_win, COLOR_PAIR(COLOR_PAIR_DEFAULT));
    
    int cat_selection = (category_filter == -1) ? category_count : category_filter;
    int scroll_offset_cat = 0;
    int visible_items = win_height - 6;
    
    // Handle scrolling if too many categories
    if (category_count + 1 > visible_items) {
        if (cat_selection >= scroll_offset_cat + visible_items) {
            scroll_offset_cat = cat_selection - visible_items + 1;
        }
        if (cat_selection < scroll_offset_cat) {
            scroll_offset_cat = cat_selection;
        }
    }
    
    // Display visible categories
    for (int i = 0; i < visible_items; i++) {
        int cat_idx = scroll_offset_cat + i;
        
        if (cat_idx > category_count) break;
        
        int line = i + 3;
        
        if (cat_idx == category_count) {
            // "All Categories" option
            if (cat_idx == cat_selection) {
                wattron(cat_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
                mvwprintw(cat_win, line, 2, "> All Categories");
                wattroff(cat_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
            } else {
                mvwprintw(cat_win, line, 4, "All Categories");
            }
        } else if (cat_idx < category_count) {
            // Count commands in this category
            int count = 0;
            for (int j = 0; j < command_count; j++) {
                if (strcmp(commands[j].category, categories[cat_idx]) == 0) {
                    count++;
                }
            }
            
            if (cat_idx == cat_selection) {
                wattron(cat_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
                mvwprintw(cat_win, line, 2, "> %s (%d)", categories[cat_idx], count);
                wattroff(cat_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
            } else {
                mvwprintw(cat_win, line, 4, "%s (%d)", categories[cat_idx], count);
            }
        }
    }
    
    // Scroll indicators
    if (scroll_offset_cat > 0) {
        mvwprintw(cat_win, 3, win_width - 2, "↑");
    }
    if (category_count + 1 > visible_items && 
        (scroll_offset_cat + visible_items) < category_count + 1) {
        mvwprintw(cat_win, win_height - 4, win_width - 2, "↓");
    }
    
    // Instructions (updated for Ctrl+C)
    mvwprintw(cat_win, win_height - 3, 2, "↑/↓: Navigate  Enter: Select");
    mvwprintw(cat_win, win_height - 2, 2, "Ctrl+C: Cancel  Ctrl+A: Select All");
    
    wrefresh(cat_win);
    
    // Handle input
    int ch;
    
    while ((ch = getch()) != 3) {  // Ctrl+C to cancel (ASCII 3)
        switch (ch) {
            case KEY_UP:
                if (cat_selection > 0) {
                    cat_selection--;
                    if (cat_selection < scroll_offset_cat) {
                        scroll_offset_cat = cat_selection;
                    }
                }
                break;
                
            case KEY_DOWN:
                if (cat_selection < category_count) {
                    cat_selection++;
                    if (cat_selection >= scroll_offset_cat + visible_items) {
                        scroll_offset_cat = cat_selection - visible_items + 1;
                    }
                }
                break;
                
            case 1:  // Ctrl+A (ASCII 1)
                category_filter = -1;  // All categories
                werase(cat_win);
                wrefresh(cat_win);
                delwin(cat_win);
                return;
                
            case 10:  // Enter
                if (cat_selection == category_count) {
                    category_filter = -1;  // All categories
                } else {
                    category_filter = cat_selection;
                }
                werase(cat_win);
                wrefresh(cat_win);
                delwin(cat_win);
                return;
                
            case KEY_PPAGE:  // Page Up
                cat_selection -= visible_items;
                if (cat_selection < 0) cat_selection = 0;
                if (cat_selection < scroll_offset_cat) {
                    scroll_offset_cat = cat_selection;
                }
                break;
                
            case KEY_NPAGE:  // Page Down
                cat_selection += visible_items;
                if (cat_selection > category_count) cat_selection = category_count;
                if (cat_selection >= scroll_offset_cat + visible_items) {
                    scroll_offset_cat = cat_selection - visible_items + 1;
                }
                break;
                
            case 27:  // ESC - also allow ESC for backward compatibility
                werase(cat_win);
                wrefresh(cat_win);
                delwin(cat_win);
                return;
        }
        
        // Redraw with new selection
        werase(cat_win);
        box(cat_win, 0, 0);
        
        wattron(cat_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
        mvwprintw(cat_win, 1, (win_width - 20) / 2, "Select Category");
        wattroff(cat_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
        
        wattron(cat_win, COLOR_PAIR(COLOR_PAIR_DEFAULT));
        
        // Display visible categories
        for (int i = 0; i < visible_items; i++) {
            int cat_idx = scroll_offset_cat + i;
            
            if (cat_idx > category_count) break;
            
            int line = i + 3;
            
            if (cat_idx == category_count) {
                // "All Categories" option
                if (cat_idx == cat_selection) {
                    wattron(cat_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
                    mvwprintw(cat_win, line, 2, "> All Categories");
                    wattroff(cat_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
                } else {
                    mvwprintw(cat_win, line, 4, "All Categories");
                }
            } else if (cat_idx < category_count) {
                // Count commands in this category
                int count = 0;
                for (int j = 0; j < command_count; j++) {
                    if (strcmp(commands[j].category, categories[cat_idx]) == 0) {
                        count++;
                    }
                }
                
                if (cat_idx == cat_selection) {
                    wattron(cat_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
                    mvwprintw(cat_win, line, 2, "> %s (%d)", categories[cat_idx], count);
                    wattroff(cat_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
                } else {
                    mvwprintw(cat_win, line, 4, "%s (%d)", categories[cat_idx], count);
                }
            }
        }
        
        // Scroll indicators
        if (scroll_offset_cat > 0) {
            mvwprintw(cat_win, 3, win_width - 2, "↑");
        }
        if (category_count + 1 > visible_items && 
            (scroll_offset_cat + visible_items) < category_count + 1) {
            mvwprintw(cat_win, win_height - 4, win_width - 2, "↓");
        }
        
        mvwprintw(cat_win, win_height - 3, 2, "↑/↓: Navigate  Enter: Select");
        mvwprintw(cat_win, win_height - 2, 2, "Ctrl+C: Cancel  Ctrl+A: Select All");
        
        wrefresh(cat_win);
    }
    
    werase(cat_win);
    wrefresh(cat_win);
    delwin(cat_win);
}

void draw_main_screen() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Clear screen
    erase();
    
    // Draw border with default color
    attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    border(0, 0, 0, 0, 0, 0, 0, 0);
    
    // Draw title with filter indicators
    attron(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
    
    // Build title with filter info
    char title[100];
    strcpy(title, "Cheat Sheet");
    
    if (category_filter != -1 || show_bookmarks_only || search_text[0] != '\0') {
        strcat(title, " [");
        
        if (show_bookmarks_only) {
            strcat(title, "★");
        }
        
        if (category_filter != -1) {
            if (title[strlen(title)-1] != '[') strcat(title, ", ");
            strcat(title, categories[category_filter]);
        }
        
        if (search_text[0] != '\0') {
            if (title[strlen(title)-1] != '[') strcat(title, ", ");
            strcat(title, "\"");
            strcat(title, search_text);
            strcat(title, "\"");
        }
        
        strcat(title, "]");
    }
    
    mvprintw(0, (max_x - strlen(title)) / 2, "%s", title);
    attroff(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
    
    // Draw search bar with mode indicator (updated to show more info)
    attron(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
    
    // Build mode string
    char mode_str[50] = "";
    if (search_mode == 0 && !show_bookmarks_only && category_filter == -1) {
        strcpy(mode_str, "ALL");
    } else {
        if (show_bookmarks_only) strcat(mode_str, "★");
        if (category_filter != -1) {
            if (mode_str[0]) strcat(mode_str, "+");
            // Show first few chars of category
            char cat_display[20];
            strncpy(cat_display, categories[category_filter], 10);
            if (strlen(categories[category_filter]) > 10) strcat(cat_display, "...");
            strcat(mode_str, cat_display);
        }
        if (search_mode & SEARCH_NAMES) {
            if (mode_str[0]) strcat(mode_str, "+");
            strcat(mode_str, "N");
        }
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
    
    mvprintw(1, 2, "Filters [%s]: [", mode_str);
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
    int spacing = 2;

    // Category filter (highlight if active)
    if (category_filter != -1) {
        attron(COLOR_PAIR(COLOR_PAIR_GREEN) | A_BOLD);
    } else {
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT) | A_BOLD);
    }
    mvprintw(max_y - 3, start_x, "Ctrl+C:Category");
    attroff(A_BOLD);
    start_x += 15 + spacing;

    // Bookmark filter (highlight if active)
    if (show_bookmarks_only) {
        attron(COLOR_PAIR(COLOR_PAIR_GREEN) | A_BOLD);
    } else {
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT) | A_BOLD);
    }
    mvprintw(max_y - 3, start_x, "Ctrl+S:Stars");
    attroff(A_BOLD);
    start_x += 13 + spacing;

    // Clear filters (highlight if any filter active)
    if (category_filter != -1 || show_bookmarks_only || search_text[0] != '\0' || search_mode != 0) {
        attron(COLOR_PAIR(COLOR_PAIR_MAGENTA) | A_BOLD);
    } else {
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT) | A_BOLD);
    }
    mvprintw(max_y - 3, start_x, "Ctrl+X:Clear");
    attroff(A_BOLD);
    start_x += 12 + spacing;

    // Ctrl+N:Names
    if (search_mode & SEARCH_NAMES) {
        attron(COLOR_PAIR(COLOR_PAIR_GREEN) | A_BOLD);
    } else {
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT) | A_BOLD);
    }
    mvprintw(max_y - 3, start_x, "Ctrl+N:Names");
    attroff(A_BOLD);
    start_x += 13 + spacing;

    // Ctrl+D:Desc
    if (search_mode & SEARCH_DESCS) {
        attron(COLOR_PAIR(COLOR_PAIR_GREEN) | A_BOLD);
    } else {
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT) | A_BOLD);
    }
    mvprintw(max_y - 3, start_x, "Ctrl+D:Desc");
    attroff(A_BOLD);
    start_x += 11 + spacing;

    // Ctrl+F:Flags
    if (search_mode & SEARCH_FLAGS) {
        attron(COLOR_PAIR(COLOR_PAIR_GREEN) | A_BOLD);
    } else {
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT) | A_BOLD);
    }
    mvprintw(max_y - 3, start_x, "Ctrl+F:Flags");
    attroff(A_BOLD);
    start_x += 12 + spacing;

    // Ctrl+E:Examples
    if (search_mode & SEARCH_EXAMPLES) {
        attron(COLOR_PAIR(COLOR_PAIR_GREEN) | A_BOLD);
    } else {
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT) | A_BOLD);
    }
    mvprintw(max_y - 3, start_x, "Ctrl+E:Examples");
    attroff(A_BOLD);
    
    // Second line of shortcuts
    start_x = 2;
    mvprintw(max_y - 2, start_x, "Enter:Details  Ctrl+B:Bookmark  Ctrl+H:Help  F1:Exit");
    attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    
    // Draw command list with scrolling
    int visible_items = max_y - 9;  // Available rows for commands
    
    // Update filtered indices
    update_filtered_indices();
    
    // Clamp scroll_offset to valid range
    if (scroll_offset > filtered_count - visible_items) {
        scroll_offset = filtered_count - visible_items;
    }
    if (scroll_offset < 0) {
        scroll_offset = 0;
    }
    
    // Display visible commands from filtered list
    for (int display_count = 0; display_count < visible_items && 
         (scroll_offset + display_count) < filtered_count; display_count++) {
        
        int cmd_index = filtered_indices[scroll_offset + display_count];
        int list_y = 4 + display_count;
        
        // Highlight selected command
        if (cmd_index == selected_index) {
            attron(A_REVERSE);
        }
        
        // Draw bookmark indicator with magenta color
        if (commands[cmd_index].bookmarked) {
            attron(COLOR_PAIR(COLOR_PAIR_MAGENTA));
            mvprintw(list_y, 2, "[*] %s", commands[cmd_index].name);
            attroff(COLOR_PAIR(COLOR_PAIR_MAGENTA));
        } else {
            attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
            mvprintw(list_y, 2, "[ ] %s", commands[cmd_index].name);
            attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
        }
        
        if (cmd_index == selected_index) {
            attroff(A_REVERSE);
        }
    }
    
    // Show scroll indicators if needed
    if (scroll_offset > 0) {
        attron(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
        mvprintw(4, max_x/4, "↑ %d", scroll_offset);
        attroff(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
    }
    
    if (filtered_count > visible_items && 
        (scroll_offset + visible_items) < filtered_count) {
        attron(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
        mvprintw(max_y - 6, max_x/4, "↓ %d more", 
                filtered_count - (scroll_offset + visible_items));
        attroff(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
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
        mvprintw(7, preview_start_x + 2, "Category: %s", cmd->category);
        
        // Draw flags (first few only)
        mvprintw(8, preview_start_x + 2, "Flags: ");
        int x_pos = preview_start_x + 9;
        for (int i = 0; i < cmd->flag_count && i < 4; i++) {
            int flag_len = (int)strlen(cmd->flag_names[i]);
            if (x_pos + flag_len + 2 < max_x - 1) {
                mvprintw(8, x_pos, "%s", cmd->flag_names[i]);
                x_pos += flag_len + 2;
            }
        }
        
        // Draw basic example with cyan color
        mvprintw(10, preview_start_x + 2, "Example:");
        attron(COLOR_PAIR(COLOR_PAIR_CYAN));
        mvprintw(11, preview_start_x + 4, "%s", cmd->basic_example);
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
    mvprintw(1, max_x - 30, "(press Ctrl+B to bookmark)");
    attroff(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
    
    // Draw separator
    mvhline(2, 1, ACS_HLINE, max_x - 2);
    
    // Calculate content height to limit scrolling
    int estimated_content_height = 5 + // base lines
                                  cmd->flag_count * 2 +
                                  cmd->flag_example_count * 4 +
                                  10; // extra padding
    int max_scroll = estimated_content_height - (max_y - 5);
    if (max_scroll < 0) max_scroll = 0;
    
    // Clamp detail_scroll to valid range
    if (detail_scroll > max_scroll) {
        detail_scroll = max_scroll;
    }
    if (detail_scroll < 0) {
        detail_scroll = 0;
    }
    
    int y_pos = 3 - detail_scroll;  // Start position adjusted by scroll
    
    // Draw description with default color
    attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
    if (y_pos >= 3) {
        mvprintw(y_pos, 2, "Description: %s", cmd->description);
    }
    y_pos++; // Move to next line
    
    if (y_pos >= 3) {
        // Only increment y_pos if we're in visible area
        y_pos++; // Blank line
    } else {
        y_pos++; // Still increment for tracking
    }
    
    // Draw category
    if (y_pos >= 3) {
        mvprintw(y_pos, 2, "Category: %s", cmd->category);
    }
    y_pos++; // Move to next line
    
    if (y_pos >= 3) {
        y_pos++; // Blank line
    } else {
        y_pos++;
    }
    
    // Draw flags section
    if (y_pos >= 3) {
        mvprintw(y_pos, 2, "Flags:");
    }
    y_pos++;
    
    for (int i = 0; i < cmd->flag_count; i++) {
        if (y_pos >= 3 && y_pos < max_y - 1) {
            mvprintw(y_pos, 4, "%s: %s", 
                    cmd->flag_names[i], cmd->flag_descs[i]);
        }
        y_pos++;
    }
    
    if (y_pos >= 3) {
        y_pos++; // Blank line
    } else {
        y_pos++;
    }
    
    // Draw examples section
    if (y_pos >= 3) {
        mvprintw(y_pos, 2, "Examples:");
    }
    y_pos++;
    
    // Basic example
    if (y_pos >= 3) {
        mvprintw(y_pos, 4, "Basic:");
    }
    y_pos++;
    
    if (y_pos >= 3 && y_pos < max_y - 1) {
        attron(COLOR_PAIR(COLOR_PAIR_CYAN));
        mvprintw(y_pos, 6, "%s", cmd->basic_example);
        attroff(COLOR_PAIR(COLOR_PAIR_CYAN));
    }
    y_pos++;
    
    if (strlen(cmd->basic_output) > 0 && y_pos >= 3 && y_pos < max_y - 1) {
        attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
        mvprintw(y_pos, 6, "Output: %s", cmd->basic_output);
        attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
        y_pos++;
    }
    
    if (y_pos >= 3) {
        y_pos++; // Blank line
    } else {
        y_pos++;
    }
    
    // Flag-specific examples
    if (cmd->flag_example_count > 0) {
        if (y_pos >= 3) {
            mvprintw(y_pos, 4, "With flags:");
        }
        y_pos++;
        
        for (int i = 0; i < cmd->flag_example_count; i++) {
            if (y_pos >= 3 && y_pos < max_y - 1) {
                attron(COLOR_PAIR(COLOR_PAIR_CYAN));
                mvprintw(y_pos, 6, "%s", cmd->flag_examples[i]);
                attroff(COLOR_PAIR(COLOR_PAIR_CYAN));
            }
            y_pos++;
            
            if (strlen(cmd->flag_example_purposes[i]) > 0 && y_pos >= 3 && y_pos < max_y - 1) {
                attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
                mvprintw(y_pos, 8, "Purpose: %s", 
                        cmd->flag_example_purposes[i]);
                attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
                y_pos++;
            }
            
            if (strlen(cmd->flag_example_outputs[i]) > 0 && y_pos >= 3 && y_pos < max_y - 1) {
                attron(COLOR_PAIR(COLOR_PAIR_DEFAULT));
                mvprintw(y_pos, 8, "Output: %s", 
                        cmd->flag_example_outputs[i]);
                attroff(COLOR_PAIR(COLOR_PAIR_DEFAULT));
                y_pos++;
            }
            
            if (y_pos >= 3) {
                y_pos++; // Blank line between examples
            } else {
                y_pos++;
            }
        }
    }
    
    // Draw scroll indicators if needed
    if (detail_scroll > 0) {
        attron(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
        mvprintw(max_y - 1, max_x - 20, "↑ Scroll: %d", detail_scroll);
        attroff(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
    }
    
    // Check if content exceeds screen height and show down indicator
    if (estimated_content_height > max_y - 3 && detail_scroll < max_scroll) {
        attron(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
        mvprintw(max_y - 1, max_x - 35, "↓ More content");
        attroff(COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
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
                            if (filtered_count > 0) {
                                int new_selected = find_prev_filtered_command(selected_index);
                                if (new_selected != selected_index) {
                                    selected_index = new_selected;
                                    
                                    // Update scroll position
                                    int filtered_pos = -1;
                                    for (int i = 0; i < filtered_count; i++) {
                                        if (filtered_indices[i] == selected_index) {
                                            filtered_pos = i;
                                            break;
                                        }
                                    }
                                    
                                    if (filtered_pos != -1 && filtered_pos < scroll_offset) {
                                        scroll_offset = filtered_pos;
                                    }
                                }
                            }
                            break;
                            
                        case KEY_DOWN:
                            if (filtered_count > 0) {
                                int new_selected = find_next_filtered_command(selected_index);
                                if (new_selected != selected_index) {
                                    selected_index = new_selected;
                                    
                                    // Update scroll position
                                    int filtered_pos = -1;
                                    for (int i = 0; i < filtered_count; i++) {
                                        if (filtered_indices[i] == selected_index) {
                                            filtered_pos = i;
                                            break;
                                        }
                                    }
                                    
                                    if (filtered_pos != -1 && filtered_pos >= scroll_offset + visible_items) {
                                        scroll_offset = filtered_pos - visible_items + 1;
                                    }
                                }
                            }
                            break;
                            
                        case KEY_HOME:
                            if (filtered_count > 0) {
                                selected_index = find_first_filtered_command();
                                scroll_offset = 0;
                            }
                            break;
                            
                        case KEY_END:
                            if (filtered_count > 0) {
                                selected_index = find_last_filtered_command();
                                scroll_offset = filtered_count - visible_items;
                                if (scroll_offset < 0) scroll_offset = 0;
                            }
                            break;
                            
                        case KEY_PPAGE:  // Page Up
                            if (filtered_count > 0) {
                                // Find current position in filtered array
                                int current_filtered_pos = -1;
                                for (int i = 0; i < filtered_count; i++) {
                                    if (filtered_indices[i] == selected_index) {
                                        current_filtered_pos = i;
                                        break;
                                    }
                                }
                                
                                if (current_filtered_pos == -1) {
                                    selected_index = filtered_indices[0];
                                    scroll_offset = 0;
                                } else {
                                    int new_filtered_pos = current_filtered_pos - visible_items;
                                    if (new_filtered_pos < 0) new_filtered_pos = 0;
                                    
                                    selected_index = filtered_indices[new_filtered_pos];
                                    scroll_offset = new_filtered_pos;
                                }
                            }
                            break;
                            
                        case KEY_NPAGE:  // Page Down
                            if (filtered_count > 0) {
                                // Find current position in filtered array
                                int current_filtered_pos = -1;
                                for (int i = 0; i < filtered_count; i++) {
                                    if (filtered_indices[i] == selected_index) {
                                        current_filtered_pos = i;
                                        break;
                                    }
                                }
                                
                                if (current_filtered_pos == -1) {
                                    selected_index = filtered_indices[0];
                                    scroll_offset = 0;
                                } else {
                                    int new_filtered_pos = current_filtered_pos + visible_items;
                                    if (new_filtered_pos >= filtered_count) {
                                        new_filtered_pos = filtered_count - 1;
                                    }
                                    
                                    selected_index = filtered_indices[new_filtered_pos];
                                    scroll_offset = new_filtered_pos - visible_items + 1;
                                    if (scroll_offset < 0) scroll_offset = 0;
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
                                selected_index = find_first_filtered_command();
                                scroll_offset = 0;
                            }
                            break;
                            
                        case 2:  // Ctrl+B (ASCII 2)
                            // Toggle bookmark
                            if (selected_index < command_count) {
                                commands[selected_index].bookmarked = !commands[selected_index].bookmarked;
                                save_commands();
                                update_filtered_indices();  // Update filtered list
                                show_status_message("Bookmark toggled", COLOR_PAIR_SUCCESS);
                            }
                            break;
                            
                        case 3:  // Ctrl+C (ASCII 3) - Category filter
                            if (category_count > 0) {
                                show_category_menu();
                                selected_index = find_first_filtered_command();
                                scroll_offset = 0;
                                draw_main_screen();
                                continue;
                            }
                            break;
                            
                        case 19:  // Ctrl+S (ASCII 19) - Stars/Bookmarks filter
                            show_bookmarks_only = !show_bookmarks_only;
                            selected_index = find_first_filtered_command();
                            scroll_offset = 0;
                            if (show_bookmarks_only) {
                                show_status_message("Showing bookmarked commands only", COLOR_PAIR_SUCCESS);
                            } else {
                                show_status_message("Showing all commands", COLOR_PAIR_DEFAULT);
                            }
                            break;
                            
                        case 24:  // Ctrl+X (ASCII 24) - Clear filters
                            search_text[0] = '\0';
                            search_mode = 0;
                            category_filter = -1;
                            show_bookmarks_only = 0;
                            selected_index = find_first_filtered_command();
                            scroll_offset = 0;
                            show_status_message("All filters cleared", COLOR_PAIR_SUCCESS);
                            break;
                            
                        case 8:   // Ctrl+H (ASCII 8) - Help
                            {
                                // Show help overlay
                                WINDOW *help_win = newwin(max_y - 4, max_x - 8, 2, 4);
                                wbkgd(help_win, COLOR_PAIR(COLOR_PAIR_DEFAULT));
                                box(help_win, 0, 0);
                                
                                wattron(help_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
                                mvwprintw(help_win, 1, (max_x - 16) / 2 - 4, "Keyboard Shortcuts");
                                wattroff(help_win, COLOR_PAIR(COLOR_PAIR_HIGHLIGHT) | A_BOLD);
                                
                                // List shortcuts
                                mvwprintw(help_win, 3, 4, "Navigation:");
                                mvwprintw(help_win, 4, 6, "↑/↓/PgUp/PgDn/Home/End - Navigate list");
                                mvwprintw(help_win, 5, 6, "Enter                     - View details");
                                mvwprintw(help_win, 6, 6, "Backspace                 - Go back/clear search");
                                
                                mvwprintw(help_win, 8, 4, "Filtering:");
                                mvwprintw(help_win, 9, 6, "Ctrl+C                    - Select category");
                                mvwprintw(help_win, 10, 6, "Ctrl+S                    - Toggle bookmarks only");
                                mvwprintw(help_win, 11, 6, "Ctrl+X                    - Clear all filters");
                                mvwprintw(help_win, 12, 6, "Ctrl+N/D/F/E              - Toggle search modes");
                                
                                mvwprintw(help_win, 14, 4, "Actions:");
                                mvwprintw(help_win, 15, 6, "Ctrl+B                    - Toggle bookmark");
                                mvwprintw(help_win, 16, 6, "Ctrl+H                    - This help screen");
                                mvwprintw(help_win, 17, 6, "F1                        - Exit");
                                
                                mvwprintw(help_win, max_y - 8, (max_x - 16) / 2 - 4, "Press any key to continue...");
                                
                                wrefresh(help_win);
                                getch();
                                delwin(help_win);
                            }
                            break;
                            
                        // Handle Ctrl+key combinations
                        case 14:  // Ctrl+N (ASCII 14)
                            // Toggle search in names
                            search_mode ^= SEARCH_NAMES;
                            selected_index = find_first_filtered_command();
                            scroll_offset = 0;
                            break;
                            
                        case 4:   // Ctrl+D (ASCII 4)
                            // Toggle search in descriptions
                            search_mode ^= SEARCH_DESCS;
                            selected_index = find_first_filtered_command();
                            scroll_offset = 0;
                            break;
                            
                        case 6:   // Ctrl+F (ASCII 6)
                            // Toggle search in flags
                            search_mode ^= SEARCH_FLAGS;
                            selected_index = find_first_filtered_command();
                            scroll_offset = 0;
                            break;
                            
                        case 5:   // Ctrl+E (ASCII 5)
                            // Toggle search in examples
                            search_mode ^= SEARCH_EXAMPLES;
                            selected_index = find_first_filtered_command();
                            scroll_offset = 0;
                            break;
                            
                        default:
                            // Handle text input for search
                            if (isprint(ch) && strlen(search_text) < MAX_SEARCH_LEN - 1) {
                                strncat(search_text, (char*)&ch, 1);
                                selected_index = find_first_filtered_command();
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
                        detail_scroll = 0;
                        draw_main_screen();
                        break;
                        
                    case 2:  // Ctrl+B (ASCII 2)
                        // Toggle bookmark
                        if (selected_index < command_count) {
                            commands[selected_index].bookmarked = !commands[selected_index].bookmarked;
                            save_commands();
                            update_filtered_indices();  // Update filtered list
                            draw_detail_screen();
                        }
                        break;
                        
                    case KEY_UP:
                        if (detail_scroll > 0) {
                            detail_scroll--;
                        }
                        break;
                        
                    case KEY_DOWN:
                        // Calculate reasonable maximum scroll
                        Command *cmd = &commands[selected_index];
                        int estimated_content_height = 5 + // base lines
                                                      cmd->flag_count * 2 +
                                                      cmd->flag_example_count * 4+3; // extra padding
                        
                        int max_y, max_x;
                        getmaxyx(stdscr, max_y, max_x);
                        int max_scroll = estimated_content_height - (max_y - 5);
                        if (max_scroll < 0) max_scroll = 0;
                        
                        if (detail_scroll < max_scroll) {
                            detail_scroll++;
                        }
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