// Shared Navbar Component
class SharedNavbar {
  constructor() {
    this.currentPage = this.getCurrentPage();
    this.init();
  }

  getCurrentPage() {
    const path = window.location.pathname;
    if (path.includes('fan.html')) return 'fan';
    if (path.includes('light.html')) return 'light';
    return 'dashboard';
  }

  init() {
    this.createNavbar();
    this.bindEvents();
  }

  createNavbar() {
    const navbarHTML = `
      <header class="topnav">
        <div class="nav-left">
          <button id="menuToggle" class="hamburger" aria-label="Open navigation" aria-expanded="false">
            <span></span><span></span><span></span>
          </button>
          <div class="brand">
            <div class="logo" aria-hidden="true">
              <svg viewBox="0 0 36 36" width="28" height="28" xmlns="http://www.w3.org/2000/svg">
                <defs>
                  <linearGradient id="g" x1="0" y1="0" x2="1" y2="1">
                    <stop offset="0%" stop-color="#28a745" />
                    <stop offset="100%" stop-color="#1e90ff" />
                  </linearGradient>
                </defs>
                <circle cx="18" cy="18" r="16" fill="url(#g)" opacity="0.15" />
                <path d="M9 22c4-8 14-8 18 0" stroke="#28a745" stroke-width="2" fill="none" stroke-linecap="round" />
                <path d="M12 18c3-5 9-5 12 0" stroke="#1e90ff" stroke-width="2" fill="none" stroke-linecap="round" />
                <circle cx="18" cy="18" r="2" fill="#28a745" />
              </svg>
            </div>
            <h1 class="title">The Smart Room Energy Manager</h1>
          </div>
        </div>
        <nav class="nav-center" id="primaryNav">
          <a href="index.html" class="nav-link ${this.currentPage === 'dashboard' ? 'active' : ''}">Dashboard</a>
          <a href="fan.html" class="nav-link ${this.currentPage === 'fan' ? 'active' : ''}">Fan</a>
          <a href="light.html" class="nav-link ${this.currentPage === 'light' ? 'active' : ''}">Light</a>
        </nav>
        <div class="nav-right">
          <button id="refreshBtn" class="refresh-btn" title="Refresh data" aria-label="Refresh">Refresh</button>
          <button class="icon-btn" title="Search" aria-label="Search">
            <svg viewBox="0 0 24 24" width="20" height="20" fill="none" stroke="#ffffff" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><circle cx="11" cy="11" r="8"></circle><line x1="21" y1="21" x2="16.65" y2="16.65"></line></svg>
          </button>
          <button class="icon-btn" title="Settings" aria-label="Settings">
            <svg viewBox="0 0 24 24" width="20" height="20" fill="none" stroke="#ffffff" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><circle cx="12" cy="12" r="3"></circle><path d="M19.4 15a1.65 1.65 0 0 0 .33 1.82l.06.06a2 2 0 0 1-2.83 2.83l-.06-.06a1.65 1.65 0 0 0-1.82-.33 1.65 1.65 0 0 0-1 1.51V21a2 2 0 0 1-4 0v-.09A1.65 1.65 0 0 0 8 19.4a1.65 1.65 0 0 0-1.82.33l-.06.06a2 2 0 1 1-2.83-2.83l.06-.06A1.65 1.65 0 0 0 3.6 15a1.65 1.65 0 0 0-1.51-1H2a2 2 0 1 1 0-4h.09A1.65 1.65 0 0 0 3.6 8a1.65 1.65 0 0 0-.33-1.82l-.06-.06a2 2 0 1 1 2.83-2.83l.06.06A1.65 1.65 0 0 0 8 3.6a1.65 1.65 0 0 0 1-1.51V2a2 2 0 1 1 4 0v.09A1.65 1.65 0 0 0 15 3.6a1.65 1.65 0 0 0 1.82-.33l.06-.06a2 2 0 1 1 2.83 2.83l-.06.06A1.65 1.65 0 0 0 20.4 8c0 .6.24 1.17.66 1.6.42.43.66 1 .66 1.6s-.24 1.17-.66 1.6A1.65 1.65 0 0 0 19.4 15z"/></svg>
          </button>
          <div class="avatar" title="Profile" aria-label="Profile"></div>
        </div>
      </header>
    `;

    // Insert navbar at the beginning of the body
    document.body.insertAdjacentHTML('afterbegin', navbarHTML);
  }

  bindEvents() {
    // Mobile menu toggle
    const toggle = document.getElementById('menuToggle');
    const nav = document.getElementById('primaryNav');
    if (toggle && nav) {
      toggle.addEventListener('click', () => {
        const open = nav.classList.toggle('open');
        toggle.setAttribute('aria-expanded', open ? 'true' : 'false');
      });
    }

    // Refresh button
    const refreshBtn = document.getElementById('refreshBtn');
    if (refreshBtn) {
      refreshBtn.addEventListener('click', () => {
        // Dispatch custom event for page-specific refresh handling
        window.dispatchEvent(new CustomEvent('navbarRefresh'));
      });
    }
  }
}

// Initialize navbar when DOM is loaded
document.addEventListener('DOMContentLoaded', () => {
  new SharedNavbar();
});
