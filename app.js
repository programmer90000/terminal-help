// compact-dashboard.js
const term = require('terminal-kit').terminal;

// ============================================================================
// SIMPLE DASHBOARD
// ============================================================================

class CompactDashboard {
  constructor() {
    this.screen = 'main';
    this.selected = 0;
    this.mouseEnabled = false;
    this.buttons = [];
    this.data = {
      cpu: 45,
      memory: 72,
      disk: 33,
      temp: 68,
      network: 120,
      processes: 87
    };
  }

  // Initialize dashboard
  init() {
    term.clear();
    term.hideCursor();
    term.grabInput({ mouse: 'button' });
    
    // Handle mouse events
    term.on('mouse', (name, data) => this.handleMouse(name, data));
    
    // Handle keyboard
    term.on('key', (key) => this.handleKey(key));
    
    // Auto-update data
    setInterval(() => this.updateData(), 2000);
    
    this.render();
  }

  // Handle mouse clicks
  handleMouse(name, data) {
    if (name === 'MOUSE_LEFT_BUTTON_PRESSED') {
      this.buttons.forEach((btn, i) => {
        if (data.x >= btn.x && data.x < btn.x + btn.width &&
            data.y >= btn.y && data.y < btn.y + btn.height) {
          this.selected = i;
          if (btn.action) btn.action();
          this.render();
        }
      });
    }
  }

  // Handle keyboard
  handleKey(key) {
    switch (key) {
      case '1': case '2': case '3': case '4': 
        this.selected = parseInt(key) - 1;
        this.render();
        break;
      case 'm': case 'M':
        this.toggleMouse();
        break;
      case 'q': case 'Q': case 'CTRL_C':
        this.shutdown();
        break;
      case 'UP': this.selected = Math.max(0, this.selected - 1); this.render(); break;
      case 'DOWN': this.selected = Math.min(3, this.selected + 1); this.render(); break;
      case 'ENTER': this.clickButton(this.selected); break;
    }
  }

  // Toggle mouse support
  toggleMouse() {
    this.mouseEnabled = !this.mouseEnabled;
    term.grabInput({ mouse: this.mouseEnabled ? 'button' : false });
    this.render();
  }

  // Update sample data
  updateData() {
    // Simulate changing data
    this.data.cpu = Math.min(100, Math.max(10, this.data.cpu + (Math.random() - 0.5) * 10));
    this.data.memory = Math.min(100, Math.max(20, this.data.memory + (Math.random() - 0.4) * 8));
    this.data.network = Math.min(200, Math.max(50, this.data.network + (Math.random() - 0.5) * 20));
    this.render();
  }

  // Draw a button
  drawButton(x, y, label, index, width = 20) {
    const isSelected = index === this.selected;
    const bgColor = isSelected ? [255, 200, 0] : [60, 60, 80];
    const textColor = isSelected ? [0, 0, 0] : [200, 200, 255];
    
    // Store button for mouse clicks
    this.buttons[index] = { x, y, width, height: 3, action: () => this.clickButton(index) };
    
    // Button background
    for (let dy = 0; dy < 3; dy++) {
      term.moveTo(x, y + dy);
      term.bgColorRgb(...bgColor)(' '.repeat(width));
    }
    
    // Button label
    term.moveTo(x + Math.floor((width - label.length) / 2), y + 1);
    term.bgColorRgb(...bgColor).colorRgb(...textColor).bold(label);
    
    // Hotkey indicator
    term.moveTo(x + 2, y + 1);
    term.bgColorRgb(...bgColor).colorRgb(...textColor)(`${index + 1}`);
  }

  // Button actions
  clickButton(index) {
    const actions = [
      () => { this.screen = 'main'; },
      () => { this.screen = 'details'; },
      () => { this.screen = 'graphs'; },
      () => { this.toggleMouse(); }
    ];
    if (actions[index]) actions[index]();
    this.render();
  }

  // Draw gauge
  drawGauge(x, y, label, value, max = 100, width = 30, color = [0, 200, 255]) {
    const filled = Math.round((value / max) * (width - 2));
    
    term.moveTo(x, y);
    term.colorRgb(220, 220, 220)(label.padEnd(12));
    term.colorRgb(150, 150, 150)('[', '');
    
    // Gauge bar
    for (let i = 0; i < width - 2; i++) {
      if (i < filled) {
        const intensity = Math.floor(150 + (value / max) * 105);
        term.bgColorRgb(
          Math.min(color[0] + intensity, 255),
          Math.min(color[1] + intensity, 255),
          Math.min(color[2] + intensity, 255)
        )(' ');
      } else {
        term.bgColorRgb(40, 40, 40)(' ');
      }
    }
    
    term.colorRgb(150, 150, 150)(']', '');
    term.colorRgb(255, 255, 255)(` ${Math.round(value)}%`);
  }

  // Draw sparkline
  drawSparkline(x, y, data, width = 30, color = [100, 200, 255]) {
    const max = Math.max(...data);
    const chars = ['▁', '▂', '▃', '▄', '▅', '▆', '▇', '█'];
    
    term.moveTo(x, y);
    for (let i = 0; i < Math.min(width, data.length); i++) {
      const ratio = data[i] / max;
      const charIdx = Math.floor(ratio * (chars.length - 1));
      const intensity = Math.floor(100 + ratio * 155);
      term.colorRgb(
        Math.min(color[0] + intensity, 255),
        Math.min(color[1] + intensity, 255),
        Math.min(color[2] + intensity, 255)
      )(chars[charIdx]);
    }
  }

  // Main dashboard screen
  renderMain() {
    // Header
    term.moveTo(2, 1);
    console.log(this.createGradient('SYSTEM DASHBOARD', [255, 100, 100], [100, 100, 255]));
    
    // Status bar
    term.moveTo(2, 3);
    term.colorRgb(150, 150, 150)('Status: ');
    term.colorRgb(100, 255, 100)('● ONLINE ');
    term.colorRgb(150, 150, 150)('| Mouse: ');
    term.colorRgb(this.mouseEnabled ? [100, 255, 100] : [255, 100, 100])(this.mouseEnabled ? 'ENABLED' : 'DISABLED');
    
    // Gauges
    this.drawGauge(2, 5, 'CPU Usage:', this.data.cpu, 100, 40, [255, 100, 100]);
    this.drawGauge(2, 7, 'Memory:', this.data.memory, 100, 40, [100, 255, 100]);
    this.drawGauge(2, 9, 'Disk:', this.data.disk, 100, 40, [100, 100, 255]);
    this.drawGauge(2, 11, 'Network:', this.data.network, 200, 40, [255, 100, 255]);
    
    // Sparklines
    term.moveTo(2, 13);
    term.colorRgb(200, 200, 200)('CPU Trend:');
    this.drawSparkline(14, 13, 
      [30, 45, 55, 65, 60, 50, 45, 55, 70, 75, 65, 55, 45, 50, 60], 40);
    
    // Stats
    term.moveTo(2, 15);
    term.colorRgb(200, 200, 200)('Temperature: ');
    term.colorRgb(255, 150, 100)(`${this.data.temp}°C`);
    
    term.moveTo(2, 16);
    term.colorRgb(200, 200, 200)('Processes: ');
    term.colorRgb(150, 200, 255)(`${this.data.processes}`);
    
    // Buttons
    this.drawButton(2, 18, '↻ REFRESH', 0);
    this.drawButton(25, 18, '📊 DETAILS', 1);
    this.drawButton(48, 18, '📈 GRAPHS', 2);
    this.drawButton(71, 18, this.mouseEnabled ? '🐭 DISABLE MOUSE' : '🖱️ ENABLE MOUSE', 3);
    
    // Help
    term.moveTo(2, 22);
    term.colorRgb(100, 100, 150)('Use ');
    term.colorRgb(255, 255, 100)('1-4/↑↓');
    term.colorRgb(100, 100, 150)(' to select, ');
    term.colorRgb(255, 255, 100)('ENTER');
    term.colorRgb(100, 100, 150)(' to click, ');
    term.colorRgb(255, 100, 100)('Q');
    term.colorRgb(100, 100, 150)(' to quit');
  }

  // Details screen
  renderDetails() {
    term.moveTo(2, 1);
    console.log(this.createGradient('SYSTEM DETAILS', [100, 255, 100], [100, 100, 255]));
    
    // System info
    const details = [
      ['OS:', 'Linux Ubuntu 22.04', [150, 200, 255]],
      ['Kernel:', '5.15.0-91-generic', [150, 255, 200]],
      ['Uptime:', '15 days, 6:42:18', [255, 200, 150]],
      ['Hostname:', 'server-01', [255, 150, 255]],
      ['CPU Model:', 'AMD Ryzen 9 5900X', [200, 255, 255]],
      ['Memory Total:', '32 GB', [150, 255, 150]],
      ['Disk Total:', '1 TB SSD', [255, 255, 150]],
      ['Network IP:', '192.168.1.100', [255, 150, 150]]
    ];
    
    details.forEach(([label, value, color], i) => {
      term.moveTo(2, 3 + i);
      term.colorRgb(180, 180, 180)(label.padEnd(12));
      term.colorRgb(...color)(value);
    });
    
    // Active services
    term.moveTo(2, 12);
    term.colorRgb(220, 220, 220)('Active Services:');
    
    const services = [
      { name: 'nginx', status: '●', color: [100, 255, 100] },
      { name: 'postgresql', status: '●', color: [100, 255, 100] },
      { name: 'redis', status: '●', color: [100, 255, 100] },
      { name: 'docker', status: '○', color: [255, 100, 100] },
      { name: 'ssh', status: '●', color: [100, 255, 100] }
    ];
    
    services.forEach((service, i) => {
      term.moveTo(2, 14 + i);
      term.colorRgb(...service.color)(`${service.status} `);
      term.colorRgb(200, 200, 200)(service.name);
    });
    
    // Back button
    this.drawButton(2, 20, '← BACK TO DASHBOARD', 0, 25);
  }

  // Graphs screen
  renderGraphs() {
    term.moveTo(2, 1);
    console.log(this.createGradient('PERFORMANCE GRAPHS', [255, 100, 255], [100, 255, 255]));
    
    // Generate random graph data
    const cpuHistory = Array.from({length: 40}, () => 20 + Math.random() * 60);
    const memHistory = Array.from({length: 40}, () => 30 + Math.random() * 50);
    const netHistory = Array.from({length: 40}, () => 50 + Math.random() * 100);
    
    // CPU graph
    term.moveTo(2, 3);
    term.colorRgb(255, 150, 150)('CPU Usage History:');
    this.drawSparkGraph(2, 4, cpuHistory, 76, [255, 100, 100]);
    
    // Memory graph
    term.moveTo(2, 10);
    term.colorRgb(150, 255, 150)('Memory Usage History:');
    this.drawSparkGraph(2, 11, memHistory, 76, [100, 255, 100]);
    
    // Network graph
    term.moveTo(2, 17);
    term.colorRgb(150, 150, 255)('Network Activity:');
    this.drawSparkGraph(2, 18, netHistory, 76, [100, 100, 255]);
    
    // Back button
    this.drawButton(2, 22, '← BACK TO DASHBOARD', 0, 25);
  }

  // Draw spark graph
  drawSparkGraph(x, y, data, width, color) {
    const max = Math.max(...data);
    const height = 5;
    
    // Create character matrix
    const matrix = Array(height).fill().map(() => Array(width).fill(' '));
    
    // Fill matrix
    data.forEach((value, i) => {
      if (i >= width) return;
      const barHeight = Math.round((value / max) * height);
      for (let h = 0; h < barHeight; h++) {
        matrix[height - 1 - h][i] = '█';
      }
    });
    
    // Draw matrix
    for (let row = 0; row < height; row++) {
      term.moveTo(x, y + row);
      for (let col = 0; col < width; col++) {
        if (matrix[row][col] === '█') {
          const intensity = Math.floor(100 + (row / height) * 155);
          term.colorRgb(
            Math.min(color[0] + intensity, 255),
            Math.min(color[1] + intensity, 255),
            Math.min(color[2] + intensity, 255)
          )('█');
        } else {
          term.colorRgb(40, 40, 40)('░');
        }
      }
    }
  }

  // Create gradient text
  createGradient(text, startRGB, endRGB) {
    let result = '';
    for (let i = 0; i < text.length; i++) {
      const ratio = i / (text.length - 1);
      const r = Math.round(startRGB[0] + (endRGB[0] - startRGB[0]) * ratio);
      const g = Math.round(startRGB[1] + (endRGB[1] - startRGB[1]) * ratio);
      const b = Math.round(startRGB[2] + (endRGB[2] - startRGB[2]) * ratio);
      result += term.colorRgb(r, g, b)(text[i]);
    }
    return result;
  }

  // Main render
  render() {
    term.clear();
    this.buttons = [];
    
    switch (this.screen) {
      case 'main':
        this.renderMain();
        break;
      case 'details':
        this.renderDetails();
        break;
      case 'graphs':
        this.renderGraphs();
        break;
    }
    
    // Footer
    const footerY = term.height - 2;
    term.moveTo(2, footerY);
    term.colorRgb(80, 80, 100)('┌' + '─'.repeat(term.width - 4) + '┐');
    
    term.moveTo(3, footerY + 1);
    term.colorRgb(100, 100, 150)('Selected: ');
    term.colorRgb(255, 255, 100)(`${this.selected + 1} `);
    term.colorRgb(100, 100, 150)('| Screen: ');
    term.colorRgb(255, 200, 100)(this.screen.toUpperCase());
    term.colorRgb(100, 100, 150)(' | Press ');
    term.colorRgb(255, 100, 100)('Q');
    term.colorRgb(100, 100, 150)(' to quit');
  }

  // Clean shutdown
  shutdown() {
    term.clear();
    term.showCursor();
    term.grabInput(false);
    term.moveTo(1, 1);
    term.colorRgb(100, 255, 100)('Dashboard closed. Goodbye!');
    setTimeout(() => process.exit(0), 1000);
  }
}

// ============================================================================
// START APPLICATION
// ============================================================================

// Handle exit
process.on('SIGINT', () => {
  term.clear();
  term.showCursor();
  term.grabInput(false);
  process.exit(0);
});

// Check terminal size
if (term.width < 80 || term.height < 25) {
  console.log('Terminal too small! Please resize to at least 80x25.');
  process.exit(1);
}

// Start dashboard
console.log('Starting Compact Dashboard...');
setTimeout(() => {
  const dashboard = new CompactDashboard();
  dashboard.init();
}, 500);