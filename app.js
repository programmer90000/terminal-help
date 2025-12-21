#!/usr/bin/env node

const blessed = require('blessed');

// Store commands with direct blessed tags
const commands = [
{
    name: '[Command Name]',
    category: '[Category]',
    description: '[Brief description]',
    usage: '[Command usage syntax]',
    example: '[Example command]',
    detailed: `{bold}[Command Name] - Full Command Title{/bold}

{green-fg}DESCRIPTION:{/green-fg}
        [Detailed description paragraph]

{green-fg}COMMON OPTIONS:{/green-fg}
        • [Option 1 description]

{green-fg}EXAMPLES:{/green-fg}
        1. [Example 1 description]:

    2. List with human readable sizes:
    {green-fg}$ ls -lh{/green-fg}

{green-fg}PRO TIPS:{/green-fg}
        • [Tip 1 description]`
},
{
    name: '[Command Name]',
    category: '[Category]',
    description: '[Brief description]',
    usage: '[Command usage syntax]',
    example: '[Example command]',
    detailed: `{bold}[Command Name] - Full Command Title{/bold}

{green-fg}DESCRIPTION:{/green-fg}
        [Detailed description paragraph]

{green-fg}COMMON OPTIONS:{/green-fg}
        • [Option 1 description]

{green-fg}EXAMPLES:{/green-fg}
        1. [Example 1 description]:

    2. List with human readable sizes:
    {green-fg}$ ls -lh{/green-fg}

{green-fg}PRO TIPS:{/green-fg}
        • [Tip 1 description]`
},
{
    name: '[Command Name]',
    category: '[Category]',
    description: '[Brief description]',
    usage: '[Command usage syntax]',
    example: '[Example command]',
    detailed: `{bold}[Command Name] - Full Command Title{/bold}

{green-fg}DESCRIPTION:{/green-fg}
        [Detailed description paragraph]

{green-fg}COMMON OPTIONS:{/green-fg}
        • [Option 1 description]

{green-fg}EXAMPLES:{/green-fg}
        1. [Example 1 description]:

    2. List with human readable sizes:
    {green-fg}$ ls -lh{/green-fg}

{green-fg}PRO TIPS:{/green-fg}
        • [Tip 1 description]`
},
{
    name: '[Command Name]',
    category: '[Category]',
    description: '[Brief description]',
    usage: '[Command usage syntax]',
    example: '[Example command]',
    detailed: `{bold}[Command Name] - Full Command Title{/bold}

{green-fg}DESCRIPTION:{/green-fg}
        [Detailed description paragraph]

{green-fg}COMMON OPTIONS:{/green-fg}
        • [Option 1 description]

{green-fg}EXAMPLES:{/green-fg}
        1. [Example 1 description]:

    2. List with human readable sizes:
    {green-fg}$ ls -lh{/green-fg}

{green-fg}PRO TIPS:{/green-fg}
        • [Tip 1 description]`
}];

const categories = ['all', 'text', 'files', 'archives'];

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
let currentScreen = 'main'; // Track current screen

function createMainScreen() {
    currentScreen = 'main';
    
    // Create screen if it doesn't exist
    if (!screen) {
        screen = blessed.screen({ 
            smartCSR: true, 
            title: 'Terminal Help', 
            fullUnicode: true, 
            dockBorders: true,
            cursor: {
                artificial: true,
                shape: 'line',
                blink: true
            }
        });
    }

    // Clear any existing layout
    if (mainLayout) {
        screen.remove(mainLayout);
        mainLayout.destroy();
    }

    // Main layout container
    mainLayout = blessed.box({ 
        parent: screen, 
        width: '100%', 
        height: '100%', 
        padding: 1 
    });

    const searchWidth = '100%-15';
    const buttonWidth = 14;
    const helpWidth = 40;

    searchBox = blessed.box({
        parent: mainLayout,
        top: 0,
        left: 0,
        width: searchWidth,
        height: 3,
        border: { type: 'line', fg: 'cyan' },
        style: {
            fg: 'white',
            border: { fg: 'cyan' }
        }
    });

    // Search input
    searchInput = blessed.textbox({
        parent: searchBox,
        top: 0,
        left: 1,
        width: '100%-2',
        height: 1,
        inputOnFocus: true,
        style: {
            fg: 'white',
            bg: 'red',
            focus: { fg: 'white', bg: 'red' }
        }
    });

    searchInput.setValue('Type to search commands...');

    // Category button
    categoryButton = blessed.button({
        parent: mainLayout,
        top: 0,
        left: searchWidth,
        width: buttonWidth,
        height: 3,
        content: 'Category: all',
        padding: { left: 1, right: 1 },
        style: {
            fg: 'white',
            bg: 'blue',
            focus: { bg: 'cyan', fg: 'black' },
            hover: { bg: 'cyan', fg: 'black' }
        },
        border: { type: 'line', fg: 'blue' }
    });

    // Category list
    categoryList = blessed.list({
        parent: mainLayout,
        top: 3,
        left: searchWidth,
        width: buttonWidth,
        height: categories.length + 2,
        hidden: true,
        items: categories,
        tags: true,
        keys: true,
        mouse: true,
        style: {
            selected: { bg: 'cyan', fg: 'black' },
            item: { fg: 'white' }
        },
        border: { type: 'line', fg: 'blue' }
    });

    // Commands table
    commandsTable = blessed.list({
        parent: mainLayout,
        top: 4,
        left: 0,
        width: `100%-${helpWidth}`,
        height: '100%-10',
        tags: true,
        keys: true,
        mouse: true,
        style: {
            selected: { bg: 'yellow', fg: 'black', bold: true },
            item: { fg: 'white' }
        },
        border: { type: 'line', fg: 'green' }
    });

    // Command details
    commandDetails = blessed.box({
        parent: mainLayout,
        top: 4,
        left: `100%-${helpWidth}`,
        width: helpWidth - 2,
        height: '100%-10',
        tags: true,
        scrollable: true,
        alwaysScroll: true,
        scrollbar: {
            ch: ' ',
            track: { bg: 'gray' },
            style: { inverse: true }
        },
        style: { fg: 'white' },
        border: { type: 'line', fg: 'magenta' }
    });

    // Help info
    helpInfo = blessed.box({
        parent: mainLayout,
        bottom: 0,
        left: 0,
        width: '100%',
        height: 3,
        content: '{bold}Navigation:{/bold} ↑↓: Select command | TAB: Switch focus | ENTER: View details | /: Search | ESC: Exit | c: Change category',
        tags: true,
        style: { fg: 'gray', bg: 'black' },
        border: { type: 'line', fg: 'gray' }
    });

    // Update the display
    updateCommandsList();
    commandsTable.focus();
    setupMainScreenEvents();
    screen.render();
}

function createDetailScreen(command) {
    currentScreen = 'detail';
    
    // Clear main screen
    screen.remove(mainLayout);
    mainLayout.destroy();

    const detailLayout = blessed.box({ 
        parent: screen, 
        width: '100%', 
        height: '100%', 
        padding: 1 
    });

    const header = blessed.box({
        parent: detailLayout,
        top: 0,
        left: 0,
        width: '100%',
        height: 3,
        content: `{bold}${command.name}{/bold} - ${command.description}`,
        tags: true,
        style: { fg: 'white' },
        border: { type: 'line', fg: 'blue' }
    });

    const usageBox = blessed.box({
        parent: detailLayout,
        top: 4,
        left: 0,
        width: '100%',
        height: 3,
        content: `{bold}Usage:{/bold} {green-fg}${command.usage}{/green-fg}`,
        tags: true,
        style: { fg: 'yellow' },
        border: { type: 'line', fg: 'green' }
    });

    const exampleBox = blessed.box({
        parent: detailLayout,
        top: 8,
        left: 0,
        width: '100%',
        height: 3,
        content: `{bold}Example:{/bold} $ {yellow-fg}${command.example}{/yellow-fg}`,
        tags: true,
        style: { fg: 'white' },
        border: { type: 'line', fg: 'yellow' }
    });

    const detailContent = blessed.box({
        parent: detailLayout,
        top: 12,
        left: 0,
        width: '100%',
        height: '100%-16',
        content: command.detailed,
        tags: true,
        scrollable: true,
        alwaysScroll: true,
        mouse: true,
        scrollbar: {
            ch: '█',
            track: { bg: 'gray' },
            style: { inverse: true }
        },
        style: { fg: 'white' },
        border: { type: 'line', fg: 'magenta' },
        padding: { left: 1, right: 1, top: 1, bottom: 1 }
    });

    const detailHelp = blessed.box({
        parent: detailLayout,
        bottom: 0,
        left: 0,
        width: '100%',
        height: 3,
        content: '{bold}Navigation:{/bold} ↑↓: Scroll | ESC: Back to main screen | q: Exit',
        tags: true,
        style: { fg: 'gray', bg: 'black' },
        border: { type: 'line', fg: 'gray' }
    });

    // Clear all existing key handlers
    screen.removeAllListeners('keypress');

    // Setup scroll handlers
    const scrollAndRender = (amount) => {
        detailContent.scroll(amount);
        screen.render();
    };

    detailContent.on('wheeldown', () => scrollAndRender(1));
    detailContent.on('wheelup', () => scrollAndRender(-1));

    // Setup keyboard handlers
    screen.key(['up', 'pageup'], () => scrollAndRender(-1));
    screen.key(['down', 'pagedown'], () => scrollAndRender(1));
    screen.key(['home', 'g'], () => {
        detailContent.scrollTo(0);
        screen.render();
    });
    screen.key(['end', 'G'], () => {
        detailContent.scrollTo(Infinity);
        screen.render();
    });
    
    // Handle escape - check current screen
    screen.key(['escape'], () => {
        if (currentScreen === 'detail') {
            // Remove the detail layout
            screen.remove(detailLayout);
            detailLayout.destroy();
            
            // Use setTimeout to ensure cleanup happens before creating new screen
            setTimeout(() => {
                createMainScreen();
            }, 50);
        }
    });
    
    // 'b' for back
    screen.key(['b'], () => {
        // Remove the detail layout
        screen.remove(detailLayout);
        detailLayout.destroy();
        
        // Use setTimeout to ensure cleanup happens before creating new screen
        setTimeout(() => {
            createMainScreen();
        }, 50);
    });
    
    screen.key(['q', 'C-c'], () => process.exit(0));

    // Initial render
    screen.render();
}

function updateCommandDetails() {
    if (filteredCommands.length === 0) {
        commandDetails.setContent('No commands found');
        return;
    }

    const cmd = filteredCommands[selectedIndex];
    const details = [
        `{bold}${cmd.name}{/bold}`,
        '',
        '{cyan-fg}Description:{/cyan-fg}',
        `  ${cmd.description}`,
        '',
        '{cyan-fg}Category:{/cyan-fg}',
        `  ${cmd.category}`,
        '',
        '{cyan-fg}Usage:{/cyan-fg}',
        `  {green-fg}${cmd.usage}{/green-fg}`,
        '',
        '{cyan-fg}Example:{/cyan-fg}',
        `  $ {yellow-fg}${cmd.example}{/yellow-fg}`,
        '',
        '{cyan-fg}Press ENTER for detailed guide{/cyan-fg}',
        `  Includes: options, examples, pro tips`
    ].join('\n');

    commandDetails.setContent(details);
    screen.render();
}

function updateCommandsList() {
    let filtered = commands;
    
    if (currentCategory !== 'all') {
        filtered = commands.filter(cmd => cmd.category === currentCategory);
    }
    
    const searchTerm = searchInput.getValue().toLowerCase().trim();
    if (searchTerm && searchTerm !== 'type to search commands...') {
        filtered = filtered.filter(cmd => 
            cmd.name.toLowerCase().includes(searchTerm) || 
            cmd.description.toLowerCase().includes(searchTerm) || 
            cmd.usage.toLowerCase().includes(searchTerm)
        );
    }
    
    filteredCommands = filtered;
    selectedIndex = Math.min(selectedIndex, filteredCommands.length - 1);
    
    commandsTable.setItems(
        filteredCommands.map(cmd => `{bold}${cmd.name}{/bold} - ${cmd.description}`)
    );
    
    if (filteredCommands.length > 0) {
        commandsTable.select(selectedIndex);
    }
    
    updateCommandDetails();
}

function setupMainScreenEvents() {
    // Remove existing listeners to avoid duplicates
    screen.removeAllListeners('keypress');
    
    // Search events
    searchInput.on('submit', () => {
        updateCommandsList();
        commandsTable.focus();
        screen.render();
    });

    searchInput.on('cancel', () => {
        searchInput.setValue('');
        updateCommandsList();
        commandsTable.focus();
        screen.render();
    });

    // Category events
    categoryButton.on('press', () => {
        categoryList.show();
        categoryList.focus();
        screen.render();
    });

    categoryList.on('select', (item, index) => {
        currentCategory = categories[index];
        categoryButton.setContent(`Category: ${currentCategory}`);
        categoryList.hide();
        updateCommandsList();
        commandsTable.focus();
        screen.render();
    });

    categoryList.on('cancel', () => {
        categoryList.hide();
        commandsTable.focus();
        screen.render();
    });

    // Commands table events
    commandsTable.on('select', (item, index) => {
        selectedIndex = index;
        updateCommandDetails();
    });

    commandsTable.on('keypress', (ch, key) => {
        if (key.name === 'up' || key.name === 'down') {
            setTimeout(() => {
                selectedIndex = commandsTable.selected;
                updateCommandDetails();
            }, 0);
        }
    });

    // Global keyboard shortcuts - check currentScreen for ESC
    screen.key(['escape'], () => {
        if (currentScreen === 'main') {
            process.exit(0);
        }
    });
    
    screen.key(['q', 'C-c'], () => process.exit(0));
    
    screen.key(['/', 's'], () => {
        searchInput.focus();
        screen.render();
    });
    
    screen.key(['c'], () => categoryButton.emit('press'));
    
    screen.key(['tab'], () => {
        if (searchInput.focused) {
            commandsTable.focus();
        } else if (commandsTable.focused) {
            searchInput.focus();
        } else if (categoryList.focused) {
            commandsTable.focus();
        }
        screen.render();
    });
    
    screen.key(['enter'], () => {
        if (commandsTable.focused && filteredCommands.length > 0) {
            const cmd = filteredCommands[selectedIndex];
            createDetailScreen(cmd);
        }
    });

    // Mouse events
    commandsTable.on('click', () => {
        commandsTable.focus();
        screen.render();
    });

    searchBox.on('click', () => {
        searchInput.focus();
        screen.render();
    });

    categoryButton.on('click', () => {
        categoryButton.emit('press');
    });

    commandsTable.on('dblclick', () => {
        if (filteredCommands.length > 0) {
            const cmd = filteredCommands[selectedIndex];
            createDetailScreen(cmd);
        }
    });
}

// Start the application
createMainScreen();