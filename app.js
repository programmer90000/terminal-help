#!/usr/bin/env node

const blessed = require('blessed');

// Store commands with direct blessed tags
const commands = [
{
    name: 'ls',
    category: 'files',
    description: 'List directory contents',
    usage: 'ls [OPTION]... [FILE]...',
    example: 'ls -la',
    detailed: `{bold}ls - List Directory Contents{/bold}

{green-fg}DESCRIPTION:{/green-fg}
        List information about the FILEs (the current directory by default).
        Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.

{green-fg}COMMON OPTIONS:{/green-fg}
        • -a, --all: Do not ignore entries starting with .
        • -l: Use a long listing format
        • -h, --human-readable: With -l, print sizes in human readable format
        • -t: Sort by modification time, newest first
        • -r, --reverse: Reverse order while sorting

{green-fg}EXAMPLES:{/green-fg}
        1. List all files including hidden ones:

    {green-fg}$ ls -a{/green-fg}

        2. List with human readable sizes:

    {green-fg}$ ls -lh{/green-fg}

        3. List sorted by modification time:

    {green-fg}$ ls -lt{/green-fg}

{green-fg}PRO TIPS:{/green-fg}
        • Use 'ls -la' to see all files including hidden ones with details
        • Combine flags: 'ls -lath' for detailed, all, time-sorted, human-readable output`
},
{
    name: 'grep',
    category: 'text',
    description: 'Print lines matching a pattern',
    usage: 'grep [OPTION]... PATTERN [FILE]...',
    example: 'grep "error" log.txt',
    detailed: `{bold}grep - Global Regular Expression Print{/bold}

{green-fg}DESCRIPTION:{/green-fg}
        Search for PATTERN in each FILE.  A FILE of "-" stands for standard input.
        If no FILE is given, recursive searches assume the current directory.

{green-fg}COMMON OPTIONS:{/green-fg}
        • -i, --ignore-case: Ignore case distinctions
        • -r, --recursive: Read all files under each directory recursively
        • -n, --line-number: Print line numbers with output lines
        • -v, --invert-match: Select non-matching lines
        • -C NUM, --context=NUM: Print NUM lines of output context

{green-fg}EXAMPLES:{/green-fg}
        1. Search for a pattern in a file:

    {green-fg}$ grep "error" app.log{/green-fg}

        2. Case-insensitive search with line numbers:

    {green-fg}$ grep -in "warning" *.log{/green-fg}

        3. Search recursively in directories:

    {green-fg}$ grep -r "TODO" src/{/green-fg}

{green-fg}PRO TIPS:{/green-fg}
        • Use '| grep' to filter command output: 'ps aux | grep python'
        • Combine with regular expressions for powerful pattern matching`
},
{
    name: 'tar',
    category: 'archives',
    description: 'Manipulate tar archives',
    usage: 'tar [OPTION]... [FILE]...',
    example: 'tar -czf archive.tar.gz directory/',
    detailed: `{bold}tar - Tape Archive{/bold}

{green-fg}DESCRIPTION:{/green-fg}
        GNU 'tar' saves many files together into a single tape or disk archive,
        and can restore individual files from the archive.

{green-fg}COMMON OPTIONS:{/green-fg}
        • -c, --create: Create a new archive
        • -x, --extract: Extract files from an archive
        • -f, --file=ARCHIVE: Use archive file or device ARCHIVE
        • -z, --gzip: Filter the archive through gzip
        • -v, --verbose: Verbosely list files processed

{green-fg}EXAMPLES:{/green-fg}
        1. Create a compressed archive:

    {green-fg}$ tar -czf archive.tar.gz folder/{/green-fg}

        2. Extract a compressed archive:

    {green-fg}$ tar -xzf archive.tar.gz{/green-fg}

        3. List contents of an archive:

    {green-fg}$ tar -tzf archive.tar.gz{/green-fg}

{green-fg}PRO TIPS:{/green-fg}
        • Remember the order: tar -c(reate) f(ile) vs tar -x(tract) f(ile)
        • Use '--' to separate options from filenames: tar -xf -- archive.tar.gz`
},
{
    name: 'find',
    category: 'files',
    description: 'Search for files in a directory hierarchy',
    usage: 'find [PATH]... [EXPRESSION]...',
    example: 'find . -name "*.txt"',
    detailed: `{bold}find - Search for Files{/bold}

{green-fg}DESCRIPTION:{/green-fg}
        Search for files in a directory hierarchy.  The expression is made up
        of options, tests, and actions, all combined with operators.

{green-fg}COMMON OPTIONS:{/green-fg}
        • -name PATTERN: Base of file name matches shell pattern PATTERN
        • -type c: File is of type c (d=directory, f=regular file, l=symlink)
        • -mtime n: File's data was last modified n*24 hours ago
        • -exec COMMAND ;: Execute COMMAND on each found file
        • -print: Print the full file name (default if no other action)

{green-fg}EXAMPLES:{/green-fg}
        1. Find all .txt files in current directory:

    {green-fg}$ find . -name "*.txt"{/green-fg}

        2. Find files modified in last 7 days:

    {green-fg}$ find . -type f -mtime -7{/green-fg}

        3. Find and delete temporary files:

    {green-fg}$ find /tmp -name "*.tmp" -delete{/green-fg}

{green-fg}PRO TIPS:{/green-fg}
        • Use '-exec' with '{}' to reference the found file
        • Add '-print0' and use 'xargs -0' for files with special characters`
}];

const categories = ['all', 'files', 'text', 'archives'];

let screen;
let mainLayout;
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

function createMainScreen() {
    currentScreen = 'main';
    
    // Create screen if it doesn't exist
    if (!screen) {
        screen = blessed.screen({ 
            smartCSR: true, 
            terminal: 'xterm',
            title: 'Terminal Help', 
            fullUnicode: true,
            dockBorders: true,
            autoPadding: true,
            warnings: true
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
        top: 0,
        left: 0,
        width: '100%', 
        height: '100%',
        border: 'line'
    });

    // Search section
    const searchBox = blessed.box({
        parent: mainLayout,
        top: 0,
        left: 0,
        width: '70%',
        height: 3,
        style: {
            bg: "green"
        },
        border: { type: 'line', fg: 'cyan' }
    });

    // Search input - use textbox correctly
    searchInput = blessed.textbox({
        parent: searchBox,
        top: 0,
        left: 2,
        width: '100%-4',
        height: 1,
        inputOnFocus: true,
        keys: true,
        mouse: true,
        style: {
            fg: 'white',
            bg: 'black',
            focus: {
                fg: 'black',
                bg: 'white'
            }
        }
    });

    // Set placeholder text
    searchInput.setValue('Type to search commands...');
    
    // Category button
    categoryButton = blessed.button({
        parent: mainLayout,
        top: 0,
        left: '70%',
        width: '30%',
        height: 3,
        content: '{center}Category: all{/center}',
        tags: true,
        padding: { left: 1, right: 1 },
        style: {
            fg: 'white',
            bg: 'blue',
            focus: { 
                bg: 'cyan', 
                fg: 'black',
                bold: true 
            },
            hover: { 
                bg: 'cyan', 
                fg: 'black' 
            }
        },
        border: { type: 'line', fg: 'blue' },
        mouse: true
    });

    // Commands table
    commandsTable = blessed.listtable({
        parent: mainLayout,
        top: 4,
        left: 0,
        width: '50%',
        height: '100%-10',
        tags: true,
        keys: true,
        mouse: true,
        align: 'left',
        noCellBorders: true,
        pad: 2,
        data: [['Command', 'Description']],
        style: {
            header: { 
                fg: 'yellow', 
                bold: true 
            },
            cell: { fg: 'white' },
            selected: { 
                bg: 'yellow', 
                fg: 'black',
                bold: true 
            }
        },
        border: { type: 'line', fg: 'green' }
    });

    // Command details
    commandDetails = blessed.box({
        parent: mainLayout,
        top: 4,
        left: '50%',
        width: '50%',
        height: '100%-10',
        tags: true,
        scrollable: true,
        alwaysScroll: true,
        scrollbar: {
            ch: '█',
            track: { bg: 'gray' },
            style: { inverse: true }
        },
        style: { 
            fg: 'white',
            scrollbar: { bg: 'cyan' }
        },
        border: { type: 'line', fg: 'magenta' },
        padding: { left: 1, right: 1, top: 0, bottom: 0 }
    });

        // Category list (hidden by default)
    categoryList = blessed.list({
        parent: mainLayout,
        top: 3,
        left: '70%',
        width: '30%',
        height: categories.length + 2,
        hidden: true,
        items: categories,
        tags: true,
        keys: true,
        mouse: true,
        style: {
            selected: { 
                bg: 'cyan', 
                fg: 'black',
                bold: true 
            },
            item: { fg: 'white' }
        },
        border: { type: 'line', fg: 'blue' }
    });

    // Help info
    helpInfo = blessed.box({
        parent: mainLayout,
        bottom: 0,
        left: 0,
        width: '100%',
        height: 3,
        content: '{bold}Navigation:{/bold} ↑↓: Select | TAB: Switch focus | ENTER: Details | /: Search | ESC: Back/Exit | c: Category | q: Quit',
        tags: true,
        style: { 
            fg: 'gray', 
            bg: 'black',
            bold: true 
        },
        border: { type: 'line', fg: 'gray' }
    });

    // Update the display
    updateCommandsList();
    commandsTable.focus();
    setupMainScreenEvents();
    screen.render();
}

function updateCommandsList() {
    let filtered = commands;
    
    // Filter by category
    if (currentCategory !== 'all') {
        filtered = commands.filter(cmd => cmd.category === currentCategory);
    }
    
    // Filter by search term
    const searchTerm = searchInput.getValue().toLowerCase().trim();
    if (searchTerm && searchTerm !== 'type to search commands...') {
        filtered = filtered.filter(cmd => 
            cmd.name.toLowerCase().includes(searchTerm) || 
            cmd.description.toLowerCase().includes(searchTerm)
        );
    }
    
    filteredCommands = filtered;
    selectedIndex = Math.min(Math.max(0, selectedIndex), filteredCommands.length - 1);
    
    // Update table data
    const tableData = [['Command', 'Description']];
    filteredCommands.forEach(cmd => {
        tableData.push([cmd.name, cmd.description]);
    });
    
    commandsTable.setData(tableData);
    
    if (filteredCommands.length > 0) {
        commandsTable.select(selectedIndex + 1); // +1 for header row
    }
    
    updateCommandDetails();
}

function updateCommandDetails() {
    if (filteredCommands.length === 0) {
        commandDetails.setContent('{center}No commands found{/center}');
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
    commandDetails.scrollTo(0);
}

function setupMainScreenEvents() {
    // Clear all existing global key handlers
    screen.removeAllListeners('keypress');
    
    // Handle ESC globally - exit application
    screen.key(['escape'], () => {
        if (currentScreen === 'main') {
            if (searchInput.focused) {
                searchInput.setValue('');
                updateCommandsList();
                commandsTable.focus();
                screen.render();
            } else if (categoryList.visible) {
                categoryList.hide();
                commandsTable.focus();
                screen.render();
            } else {
                process.exit(0);
            }
        }
    });
    
    // Handle quit keys
    screen.key(['q', 'C-c'], () => process.exit(0));
    
    // Search shortcut
    screen.key(['/', 's'], () => {
        searchInput.focus();
        screen.render();
    });
    
    // Category shortcut
    screen.key(['c'], () => {
        categoryButton.emit('press');
    });
    
    // TAB navigation
    screen.key(['tab'], () => {
        if (searchInput.focused) {
            commandsTable.focus();
        } else if (commandsTable.focused) {
            if (categoryList.visible) {
                categoryList.focus();
            } else {
                searchInput.focus();
            }
        } else if (categoryList.focused) {
            commandsTable.focus();
        }
        screen.render();
    });
    
    // ENTER key for details
    screen.key(['enter'], () => {
        if (commandsTable.focused && filteredCommands.length > 0) {
            const cmd = filteredCommands[selectedIndex];
            createDetailScreen(cmd);
        }
    });
    
    // Arrow keys for command selection
    commandsTable.on('keypress', (ch, key) => {
        if (key.name === 'up' || key.name === 'down') {
            setTimeout(() => {
                selectedIndex = commandsTable.selected - 1; // -1 for header
                updateCommandDetails();
                screen.render();
            }, 0);
        }
    });
    
    // Search events
    searchInput.key(['enter'], () => {
        updateCommandsList();
        commandsTable.focus();
        screen.render();
    });
    
    searchInput.key(['escape'], () => {
        searchInput.setValue('');
        updateCommandsList();
        commandsTable.focus();
        screen.render();
    });
    
    searchInput.on('focus', () => {
        if (searchInput.getValue() === 'Type to search commands...') {
            searchInput.clearValue();
        }
    });
    
    searchInput.on('blur', () => {
        if (searchInput.getValue() === '') {
            searchInput.setValue('Type to search commands...');
        }
    });
    
    // Real-time search (optional)
    let searchTimeout;
    searchInput.on('change', () => {
        clearTimeout(searchTimeout);
        searchTimeout = setTimeout(() => {
            updateCommandsList();
            screen.render();
        }, 300);
    });
    
    // Category events
    categoryButton.on('press', () => {
        categoryList.show();
        categoryList.focus();
        screen.render();
    });

    categoryButton.on('click', () => {
        categoryList.show();
        categoryList.focus();
        screen.render();
    });
    
    categoryList.key(['enter'], () => {
        categoryList.emit('select');
    });
    
    categoryList.key(['escape'], () => {
        categoryList.hide();
        commandsTable.focus();
        screen.render();
    });
    
    categoryList.on('select', () => {
        const selected = categoryList.selected;
        if (selected >= 0 && selected < categories.length) {
            currentCategory = categories[selected];
            categoryButton.setContent(`{center}Category: ${currentCategory}{/center}`);
            categoryList.hide();
            updateCommandsList();
            commandsTable.focus();
            screen.render();
        }
    });
    
    // Single-click selection for category list
    categoryList.on('element click', function() {
        // Trigger select immediately after click
        setTimeout(() => {
            this.emit('select');
        }, 0);
    });
    
    // Mouse events
    commandsTable.on('click', () => {
        commandsTable.focus();
        screen.render();
    });
    
    commandsTable.on('select', () => {
        selectedIndex = commandsTable.selected - 1;
        updateCommandDetails();
        screen.render();
    });
    
    // Double-click for details
    commandsTable.on('dblclick', () => {
        if (filteredCommands.length > 0) {
            const cmd = filteredCommands[selectedIndex];
            createDetailScreen(cmd);
        }
    });
    
    // Focus handling
    searchInput.on('focus', () => screen.render());
    commandsTable.on('focus', () => screen.render());
    categoryList.on('focus', () => screen.render());
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
        style: { 
            fg: 'white',
            bold: true 
        },
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
        keys: true,
        vi: true,
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
        content: '{bold}Navigation:{/bold} ↑↓/PgUp/PgDn: Scroll | ESC: Back | Home/End: Top/Bottom | q: Exit',
        tags: true,
        style: { 
            fg: 'gray', 
            bg: 'black',
            bold: true 
        },
        border: { type: 'line', fg: 'gray' }
    });

    // Clear all existing key handlers
    screen.removeAllListeners('keypress');
    
    // Setup scroll handlers for mouse
    detailContent.on('wheeldown', () => {
        detailContent.scroll(1);
        screen.render();
    });
    
    detailContent.on('wheelup', () => {
        detailContent.scroll(-1);
        screen.render();
    });

    // Keyboard navigation for detail screen
    const scrollAndRender = (amount) => {
        detailContent.scroll(amount);
        screen.render();
    };

    screen.key(['up', 'k'], () => scrollAndRender(-1));
    screen.key(['down', 'j'], () => scrollAndRender(1));
    screen.key(['pageup'], () => scrollAndRender(-10));
    screen.key(['pagedown'], () => scrollAndRender(10));
    screen.key(['home', 'g'], () => {
        detailContent.scrollTo(0);
        screen.render();
    });
    screen.key(['end', 'G'], () => {
        detailContent.scrollTo(Infinity);
        screen.render();
    });
    
    // Back navigation
    screen.key(['escape', 'b'], () => {
        if (currentScreen === 'detail') {
            screen.remove(detailLayout);
            detailLayout.destroy();
            
            // Use setTimeout to ensure cleanup
            setTimeout(() => {
                createMainScreen();
            }, 0);
        }
    });
    
    // Exit
    screen.key(['q', 'C-c'], () => process.exit(0));

    // Focus the content for scrolling
    detailContent.focus();
    
    // Initial render
    screen.render();
}

// Start the application
try {
    createMainScreen();
} catch (error) {
    console.error('Error starting application:', error);
    process.exit(1);
}