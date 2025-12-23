# Terminal Commands Application Development

## Objective
Create a production-ready terminal application in C that displays Linux terminal commands with an interactive text-based UI. The application should read command data from a JSON file and allow users to browse, search, and view detailed information about commands with syntax highlighting.

## How to answer

- Write a heading for each development phase or component
- Under each heading, provide specific implementation instructions
- First explain what the code does, then write the code and then explain how the code completes it's objective
- Explain how I can test the code for data leaks or any other potential problems caused by C programming

## Information
- **Target Platform**: Linux with Bash terminal
- **UI Approach**: Text-based UI using ncursesw with mouse and keyboard support
- **Visual Design**: Boxes with borders separating sections (command list, preview, search)
- **Data Source**: JSON file containing categorized commands with names, descriptions, flags, and examples. Bookmarks should be written to the JSON file. Flags should be added to the JSON file as a nested object.
- **Navigation**: Main screen with category filtering and search → Detail screen with full command info, flags and examples
- **Navigation Button**: Arrow keys to move up and down. Enter to select an option. Backspace to go back to the main screen. Single click with mouse to focus on command in list. Single click after option is focused to select. Arrow keys and mouse scroll button to scroll. Only the command buttons and back button should be clickable. Only the command list and information in each command page should be scrollable if necessary.
- **Command Details**: Display name, description, ALL flags, examples for plain command and EACH individual flag
- **Display Features**: Syntax highlighting for examples, multi-line example display, multiple colors
- **External Libraries**: ncursesw for UI, jansson for JSON parsing (no other external libraries)
- **Project Structure**: 1 C file (app.c), 1 JSON file (commands.json), 1 Makefile
- **Experience Level**: I have no prior C experience
- **Use Case**: Production use
- **Performance**: Minimal memory usage, fast execution
- **Extensibility**: Users add commands ONLY via JSON file, no C file modification needed
- **Bookmarks**: I should be able to bookmark specific commands which will appear at the top of the list. These bookmarks should be saved to the JSON file. Bookmarked commands should appear at top of list with [*] prefix. Unbookmarked commands appear with [ ] prefix. Press 'b' on selected command to toggle bookmark. Bookmarks saved to JSON file when exiting
Visual distinction: bookmarked commands in magenta

## Constraints
- Maximum of 2 files: app.c and commands.json
- Must use ncursesw and jansson libraries only
- Must support both keyboard and mouse input
- Must have syntax highlighting for command examples
- Must handle JSON parsing errors gracefully
- Must be memory efficient with no leaks
- Must work in standard Linux terminals
- Must allow returning from detail screen to main screen
- Must support category filtering and text search
- Must display all flags and individual examples for each flag
- There should be no minimum terminal screen size. The app should adapt to fill the terminal size. If the terminal is TOO small, the information should overflow.
- Search should search across command names,  descriptions, flags and examples. It should use fuzzy search and should be case insensitive. There should be a search bar at the top of the screen
- There should be no pagination. Only 1 list
- Colour should be added using ANSI Escape Sequences
- If JSON missing/corrupted: show error and exit gracefully
- If the terminal too small: allow overflow with scrollbars

## To do this, I want to:
- Start with the JSON file structure and example data
- Then create the basic C program structure with includes and dependencies
- Implement JSON loading and parsing functionality
- Build the main screen UI with boxes and borders
- Add keyboard and mouse input handling
- Implement search and category filtering
- Create the detail screen with syntax highlighting
- Add color scheme and visual polish
- Implement comprehensive testing procedures
- Provide build instructions and debugging methods

## JSON structure
```
{
  "commands": [
    {
      "name": "command 1",
      "description": "Command 1 description",
      "category": "category 1",
      "flags": {
        "-l": "Flag 1",
        "-a": "Flag 2",
        "-h": "Flag 3",
      },
      "examples": {
        "basic": {
            "commandRun: "command",
            "output": "Command output"
        }
        "with_flags": {
          "command flag-1" {
              "purpose": "Flag purpose"
              "exampleOutput": "Example of output using Flag 1"
          },
          "command flag-2" {
              "purpose": "Flag purpose"
              "exampleOutput": "Example of output using Flag 2"
          },
          "command flag-3" {
              "purpose": "Flag purpose"
              "exampleOutput": "Example of output using Flag 3"
          },
      }
    },
  },
    {
      "name": "command 2",
      "description": "Command 2 description",
      "category": "category 2",
      "flags": {
        "-g": "Flag 1",
        "-j": "Flag 2",
        "-k": "Flag 3",
      },
      "examples": {
        "basic": {
            "commandRun: "command",
            "output": "Command output"
        }
        "with_flags": {
          "command flag-1" {
              "purpose": "Flag purpose"
              "exampleOutput": "Example of output using Flag 1"
          },
          "command flag-2" {
              "purpose": "Flag purpose"
              "exampleOutput": "Example of output using Flag 2"
          },
          "command flag-3" {
              "purpose": "Flag purpose"
              "exampleOutput": "Example of output using Flag 3"
          },
      }
    },
  },
    {
      "name": "command 3",
      "description": "Command 3 description",
      "category": "category 3",
      "flags": {
        "-l": "Flag 3",
        "-a": "Flag 3",
        "-h": "Flag 3",
      },
      "examples": {
        "basic": {
            "commandRun: "command",
            "output": "Command output"
        }
        "with_flags": {
          "command flag-1" {
              "purpose": "Flag purpose"
              "exampleOutput": "Example of output using Flag 1"
          },
          "command flag-2" {
              "purpose": "Flag purpose"
              "exampleOutput": "Example of output using Flag 2"
          },
          "command flag-3" {
              "purpose": "Flag purpose"
              "exampleOutput": "Example of output using Flag 3"
          },
      }
    },
  },
  ],
  "bookmarks": ["ls", "grep"],
}
```

## UI Layout

### Main Screen

```
┌─────────────────────────────────────────────────────────────────────┐
│ Search: [_________________________________________________________] │
├──────────────────────────────────────┬──────────────────────────────┤
│ Commands                             │ Selected Command Preview     │
│                                      │                              │
│  [*] ls                              │ ┌──────────────────────────┐ │
│  [*] grep                            │ │ Name: ls                 │ │
│  [ ] find                            │ │ Desc: List directory     │ │
│  [ ] cp                              │ │ contents                 │ │
│  [ ] mv                              │ │ Flags: -l, -a, -h, -R    │ │
│  ...                                 │ │                          │ │
│                                      │ │ Example: ls -la          │ │
│                                      │ └──────────────────────────┘ │
│                                      │                              │
└──────────────────────────────────────┴──────────────────────────────┘
│ Ctrl+N:Names  Ctrl+D:Desc  Ctrl+F:Flags  Ctrl+E:Examples  Ctrl+A:All│
└─────────────────────────────────────────────────────────────────────┘
```

### Detailled Screen

```
┌─────────────────────────────────────────────────────────────────────┐
│ Command: ls                                 (press 'b' to bookmark) │
├─────────────────────────────────────────────────────────────────────┤
│ Description: List directory contents                                 │
│                                                                     │
│ Category: file_management                                           │
│                                                                     │
│ ┌─────────────────────────────────────────────────────────────────┐ │
│ │ Flags:                                                          │ │
│ │   -l: Use a long listing format                                 │ │
│ │   -a: Do not ignore entries starting with .                     │ │
│ │   -h: With -l, print human readable sizes                       │ │
│ │   -R: List subdirectories recursively                           │ │
│ └─────────────────────────────────────────────────────────────────┘ │
│                                                                     │
│ ┌─────────────────────────────────────────────────────────────────┐ │
│ │ Examples:                                                       │ │
│ │   Basic: ls                                                     │ │
│ │                                                                 │ │
│ │   With flags:                                                   │ │
│ │     ls -l                                                       │ │
│ │     ls -la                                                      │ │
│ │     ls -lh /home/user                                           │ │
│ │                                                                 │ │
│ │   Flag-specific examples:                                       │ │
│ │     -l: ls -l /var/log                                          │ │
│ │     -a: ls -a                                                   │ │
│ │     -h: ls -lh                                                  │ │
│ │     -R: ls -R /etc                                              │ │
│ └─────────────────────────────────────────────────────────────────┘ │
│                                                                     │
│ (press Backspace to return)                                         │
└─────────────────────────────────────────────────────────────────────┘
```
Do NOT answer this prompt. ONLY tell me what other information I could provide to help you answer it
