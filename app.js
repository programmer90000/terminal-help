#!/usr/bin/env node

const blessed = require('blessed');
const colors = {
    bold: (text) =>
        `\x1b[1m${text}\x1b[0m`,
    cyan: (text) =>
        `\x1b[36m${text}\x1b[0m`,
    green: (text) =>
        `\x1b[32m${text}\x1b[0m`,
    yellow: (text) =>
        `\x1b[33m${text}\x1b[0m`
};

const commands = [
{
    name: '[Command Name]',
    category: '[Category]',
    description: '[Brief description]',
    usage: '[Command usage syntax]',
    example: '[Example command]',
    detailed: `${colors.bold('[Command Name] - Full Command Title')}

${colors.green('DESCRIPTION:')}
    [Detailed description paragraph]

${colors.cyan('COMMON OPTIONS:')}
    • [Option 1 description]

${colors.cyan('EXAMPLES:')}
    1. [Example 1 description]:
       {green}$ [Example 1 command]{/green}

${colors.cyan('PRO TIPS:')}
    • [Tip 1 description]`
},
{
    name: '[Command Name]',
    category: '[Category]',
    description: '[Brief description]',
    usage: '[Command usage syntax]',
    example: '[Example command]',
    detailed: `{bold}[Command Name] - Full Command Title{/bold}

{cyan}DESCRIPTION:{/cyan}
    [Detailed description paragraph]

{cyan}COMMON OPTIONS:{/cyan}
    • [Option 1 description]

{cyan}EXAMPLES:{/cyan}
    1. [Example 1 description]:
       {green}$ [Example 1 command]{/green}

{cyan}PRO TIPS:{/cyan}
    • [Tip 1 description]`
},
{
    name: '[Command Name]',
    category: '[Category]',
    description: '[Brief description]',
    usage: '[Command usage syntax]',
    example: '[Example command]',
    detailed: `{bold}[Command Name] - Full Command Title{/bold}

{cyan}DESCRIPTION:{/cyan}
    [Detailed description paragraph]

{cyan}COMMON OPTIONS:{/cyan}
    • [Option 1 description]

{cyan}EXAMPLES:{/cyan}
    1. [Example 1 description]:
       {green}$ [Example 1 command]{/green}

{cyan}PRO TIPS:{/cyan}
    • [Tip 1 description]`
},
{
    name: '[Command Name]',
    category: '[Category]',
    description: '[Brief description]',
    usage: '[Command usage syntax]',
    example: '[Example command]',
    detailed: `{bold}[Command Name] - Full Command Title{/bold}

{cyan}DESCRIPTION:{/cyan}
    [Detailed description paragraph]

{cyan}COMMON OPTIONS:{/cyan}
    • [Option 1 description]

{cyan}EXAMPLES:{/cyan}
    1. [Example 1 description]:
       {green}$ [Example 1 command]{/green}

{cyan}PRO TIPS:{/cyan}
    • [Tip 1 description]`
},
{
    name: '[Command Name]',
    category: '[Category]',
    description: '[Brief description]',
    usage: '[Command usage syntax]',
    example: '[Example command]',
    detailed: `{bold}[Command Name] - Full Command Title{/bold}

{cyan}DESCRIPTION:{/cyan}
    [Detailed description paragraph]

{cyan}COMMON OPTIONS:{/cyan}
    • [Option 1 description]

{cyan}EXAMPLES:{/cyan}
    1. [Example 1 description]:
       {green}$ [Example 1 command]{/green}

{cyan}PRO TIPS:{/cyan}
    • [Tip 1 description]`
}];

const categories = ['all', 'text',
    'files', 'archives'
];

let screen;
let mainLayout;
let searchBox;
let searchInput;
let categoryButton;
let categoryList;
let commandsTable;
let commandDetails;
let helpInfo;
let currentCategory = 'all';
let filteredCommands = [...commands];
let selectedIndex = 0;
let currentScreen = 'main';

function createMainScreen()
{
    screen = blessed.screen(
    {
        smartCSR: true,
        title: 'Terminal Help',
        fullUnicode: true,
        dockBorders: true
    });

    // Clear previous screen if exists
    if (mainLayout)
    {
        mainLayout.destroy();
    }

    // Main layout container
    mainLayout = blessed.box(
    {
        parent: screen,
        width: '100%',
        height: '100%',
        padding: 1
    });

    const searchWidth = '100%-15';
    const buttonWidth = 14;
    const helpWidth = 40;

    searchBox = blessed.box(
    {
        parent: mainLayout,
        top: 0,
        left: 0,
        width: searchWidth,
        height: 3,
        border:
        {
            type: 'line',
            fg: 'cyan'
        },
        style:
        {
            fg: 'white',
            border:
            {
                fg: 'cyan'
            }
        }
    });

    // Search input (inside search box)
    searchInput = blessed.textbox(
    {
        parent: searchBox,
        top: 0,
        left: 1,
        width: '100%-2',
        height: 1,
        inputOnFocus: true,
        style:
        { // Normal state
            fg: 'white',
            bg: '#ff5555',
            focus:
            {
                fg: 'white',
                bg: '#ff5555'
            }
        }
    });

    // Initial placeholder text
    searchInput.setContent(
        'Type to search commands...'
    );

    // Category selection button
    categoryButton = blessed.button(
    {
        parent: mainLayout,
        top: 0,
        left: searchWidth,
        width: buttonWidth,
        height: 3,
        content: 'Category: all',
        padding:
        {
            left: 1,
            right: 1
        },
        style:
        {
            fg: 'white',
            bg: 'blue',
            focus:
            {
                bg: 'cyan',
                fg: 'black'
            },
            hover:
            {
                bg: 'cyan',
                fg: 'black'
            }
        },
        border:
        {
            type: 'line',
            fg: 'blue'
        }
    });

    // Category selection list (hidden by default)
    categoryList = blessed.list(
    {
        parent: mainLayout,
        top: 3,
        left: searchWidth,
        width: buttonWidth,
        height: categories
            .length + 2,
        hidden: true,
        items: categories,
        tags: true,
        keys: true,
        mouse: true,
        style:
        {
            selected:
            {
                bg: 'cyan',
                fg: 'black'
            },
            item:
            {
                fg: 'white'
            }
        },
        border:
        {
            type: 'line',
            fg: 'blue'
        }
    });

    // Commands table
    commandsTable = blessed.list(
    {
        parent: mainLayout,
        top: 4,
        left: 0,
        width: `100%-${helpWidth}`,
        height: '100%-10',
        tags: true,
        keys: true,
        mouse: true,
        style:
        {
            selected:
            {
                bg: 'yellow',
                fg: 'black',
                bold: true
            },
            item:
            {
                fg: 'white'
            }
        },
        border:
        {
            type: 'line',
            fg: 'green'
        }
    });

    // Command details panel
    commandDetails = blessed.box(
    {
        parent: mainLayout,
        top: 4,
        left: `100%-${helpWidth}`,
        width: helpWidth - 2,
        height: '100%-10',
        tags: true,
        scrollable: true,
        alwaysScroll: true,
        scrollbar:
        {
            ch: ' ',
            track:
            {
                bg: 'gray'
            },
            style:
            {
                inverse: true
            }
        },
        style:
        {
            fg: 'white'
        },
        border:
        {
            type: 'line',
            fg: 'magenta'
        }
    });

    // Help information
    helpInfo = blessed.box(
    {
        parent: mainLayout,
        bottom: 0,
        left: 0,
        width: '100%',
        height: 3,
        content: '{bold}Navigation:{/bold} ↑↓: Select command | TAB: Switch focus | ENTER: View details | /: Search | ESC: Back/Exit | c: Change category',
        tags: true,
        style:
        {
            fg: 'gray',
            bg: 'black'
        },
        border:
        {
            type: 'line',
            fg: 'gray'
        }
    });

    // Update commands list based on search and category
    updateCommandsList();
    commandsTable.focus();
    setupMainScreenEvents();
    screen.render();
}

// Create command screen
function createDetailScreen(command)
{
    currentScreen = 'detail';
    // Clear main screen
    mainLayout.destroy();

    const detailLayout = blessed.box(
    {
        parent: screen,
        width: '100%',
        height: '100%',
        padding: 1
    });

    const header = blessed.box(
    {
        parent: detailLayout,
        top: 0,
        left: 0,
        width: '100%',
        height: 3,
        content: `{bold}${command.name}{/bold} - ${command.description}`,
        tags: true,
        style:
        {
            fg: 'white',
            bold: true,
            bg: 'blue'
        },
        border:
        {
            type: 'line',
            fg: 'cyan'
        }
    });

    const usageBox = blessed.box(
    {
        parent: detailLayout,
        top: 4,
        left: 0,
        width: '100%',
        height: 3,
        content: `{bold}Usage:{/bold} {green}${command.usage}{/green}`,
        tags: true,
        style:
        {
            fg: 'yellow'
        },
        border:
        {
            type: 'line',
            fg: 'green'
        }
    });

    const exampleBox = blessed.box(
    {
        parent: detailLayout,
        top: 8,
        left: 0,
        width: '100%',
        height: 3,
        content: `{bold}Example:{/bold} $ {yellow}${command.example}{/yellow}`,
        tags: true,
        style:
        {
            fg: 'white'
        },
        border:
        {
            type: 'line',
            fg: 'yellow'
        }
    });

    const detailContent = blessed.box(
    {
        parent: detailLayout,
        top: 12,
        left: 0,
        width: '100%',
        height: '100%-16',
        content: command
            .detailed,
        tags: true,
        scrollable: true,
        alwaysScroll: true,
        scrollbar:
        {
            ch: '█',
            track:
            {
                bg: 'gray'
            },
            style:
            {
                inverse: true
            }
        },
        style:
        {
            fg: 'white'
        },
        border:
        {
            type: 'line',
            fg: 'magenta'
        },
        padding:
        {
            left: 1,
            right: 1,
            top: 1,
            bottom: 1
        }
    });

    const detailHelp = blessed.box(
    {
        parent: detailLayout,
        bottom: 0,
        left: 0,
        width: '100%',
        height: 3,
        content: '{bold}Navigation:{/bold} ↑↓: Scroll | ESC: Back to main screen | q: Exit',
        tags: true,
        style:
        {
            fg: 'gray',
            bg: 'black'
        },
        border:
        {
            type: 'line',
            fg: 'gray'
        }
    });

    detailContent.on('wheeldown',
        () =>
        {
            detailContent.scroll(1);
            screen.render();
        });

    detailContent.on('wheelup', () =>
    {
        detailContent.scroll(-
        1);
        screen.render();
    });

    screen.key(['up', 'down', 'pageup',
        'pagedown'
    ], (ch, key) =>
    {
        if (key.name === 'up' ||
            key.name ===
            'pageup')
        {
            detailContent
                .scroll(-1);
        }
        else if (key.name ===
            'down' || key
            .name === 'pagedown'
            )
        {
            detailContent
                .scroll(1);
        }
        screen.render();
    });

    screen.key(['escape', 'b'], () =>
    {
        detailLayout.destroy();
        createMainScreen();
    });

    screen.key(['q', 'C-c'], () =>
    {
        process.exit(0);
    });

    screen.key(['home'], () =>
    {
        detailContent.scrollTo(
            0);
        screen.render();
    });

    screen.key(['end'], () =>
    {
        detailContent.scrollTo(
            Infinity);
        screen.render();
    });

    screen.key(['g'], () =>
    {
        detailContent.scrollTo(
            0);
        screen.render();
    });

    screen.key(['G'], () =>
    {
        detailContent.scrollTo(
            Infinity);
        screen.render();
    });

    screen.render();
}
// Update command details when selection changes
function updateCommandDetails()
{
    if (filteredCommands.length === 0)
    {
        commandDetails.setContent(
            'No commands found');
        return;
    }
    const cmd = filteredCommands[
        selectedIndex];
    const details = [
        `{bold}${cmd.name}{/bold}`,
        '',
        `{cyan}Description:{/cyan}`,
        `  ${cmd.description}`, '',
        `{cyan}Category:{/cyan}`,
        `  ${cmd.category}`, '',
        `{cyan}Usage:{/cyan}`,
        `  {green}${cmd.usage}{/green}`,
        '', `{cyan}Example:{/cyan}`,
        `  $ {yellow}${cmd.example}{/yellow}`,
        '',
        `{cyan}Press ENTER for detailed guide{/cyan}`,
        `  Includes: options, examples, pro tips`
    ].join('\n');
    commandDetails.setContent(details);
    screen.render();
}

// Update commands list based on search and category
function updateCommandsList()
{
    // Filter by category
    let filtered = commands;

    if (currentCategory !== 'all')
    {
        filtered = commands.filter(
            cmd => cmd.category ===
            currentCategory);
    }

    // Filter by search term
    const searchTerm = searchInput.getValue().toLowerCase().trim();

    if (searchTerm && searchTerm !==
        'type to search commands...')
    {
        filtered = filtered.filter(
            cmd => cmd.name
            .toLowerCase().includes(
                searchTerm) || cmd
            .description
            .toLowerCase().includes(
                searchTerm) || cmd
            .usage.toLowerCase()
            .includes(searchTerm));
    }

    filteredCommands = filtered;
    selectedIndex = Math.min(selectedIndex, filteredCommands.length - 1);

    // Update list items
    commandsTable.setItems(
        filteredCommands.map(cmd =>
            `{bold}${cmd.name}{/bold} - ${cmd.description}`
    ));

    // Update selection
    if (filteredCommands.length > 0)
    {
        commandsTable.select(
            selectedIndex);
    }
    updateCommandDetails();
}

// Setup event handlers for main screen
function setupMainScreenEvents()
{
    // Search input events
    searchInput.on('submit', () =>
    {
        updateCommandsList();
        commandsTable.focus();
        screen.render();
    });

    searchInput.on('cancel', () =>
    {
        searchInput.setValue(
        '');
        updateCommandsList();
        commandsTable.focus();
        screen.render();
    });

    // Category button events
    categoryButton.on('press', () =>
    {
        categoryList.show();
        categoryList.focus();
        screen.render();
    });

    categoryList.on('select', (item,
        index) =>
    {
        currentCategory =
            categories[index];
        categoryButton
            .setContent(
                `Category: ${currentCategory}`
                );
        categoryList.hide();
        updateCommandsList();
        commandsTable.focus();
        screen.render();
    });

    categoryList.on('cancel', () =>
    {
        categoryList.hide();
        commandsTable.focus();
        screen.render();
    });

    // Commands table events
    commandsTable.on('select', (item,
        index) =>
    {
        selectedIndex = index;
        updateCommandDetails();
    });

    commandsTable.on('keypress', (ch,
        key) =>
    {
        if (key.name === 'up' ||
            key.name === 'down')
        {
            setTimeout(() =>
            {
                selectedIndex
                    =
                    commandsTable
                    .selected;
                updateCommandDetails
                    ();
            }, 0);
        }
    });

    // Global keyboard shortcuts
    screen.key(['escape'], () =>
    {
        if (currentScreen ===
            'main')
        {
            process.exit(0);
        }
    });

    screen.key(['q', 'C-c'], () =>
    {
        process.exit(0);
    });

    screen.key(['/', 's'], () =>
    {
        searchInput.focus();
        screen.render();
    });

    screen.key(['c'], () =>
    {
        categoryButton.emit(
            'press');
    });

    screen.key(['tab'], () =>
    {
        if (searchInput.focused) {
            commandsTable.focus();
        }
        else if (commandsTable
            .focused)
        {
            searchInput.focus();
        }
        else if (categoryList
            .focused)
        {
            commandsTable
            .focus();
        }
        screen.render();
    });
    screen.key(['enter'], () =>
    {
        if (commandsTable
            .focused &&
            filteredCommands
            .length > 0)
        {
            const cmd =
                filteredCommands[
                    selectedIndex
                    ];
            createDetailScreen(
                cmd);
        }
    });
    commandsTable.on('click', () =>
    {
        commandsTable.focus();
        screen.render();
    });
    searchBox.on('click', () =>
    {
        searchInput.focus();
        screen.render();
    });
    categoryButton.on('click', () =>
    {
        categoryButton.emit(
            'press');
    });
    commandsTable.on('dblclick', () =>
    {
        if (filteredCommands
            .length > 0)
        {
            const cmd =
                filteredCommands[
                    selectedIndex
                    ];
            createDetailScreen(
                cmd);
        }
    });
}
createMainScreen();
