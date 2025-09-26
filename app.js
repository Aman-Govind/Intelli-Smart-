window.addEventListener('load', () => {
  const intro = document.getElementById('intro');
  const dashboard = document.getElementById('dashboard');

  // Fade out splash after 2 seconds
  setTimeout(() => {
    if (!intro || !dashboard) return;
    intro.style.transition = 'opacity 0.5s';
    intro.style.opacity = 0;
    setTimeout(() => {
      intro.style.display = 'none';
      dashboard.style.display = 'block';
    }, 500);
  }, 2000);

  // Simulated data update to demonstrate layout
  const motionCard = document.getElementById('motionCard');
  const tempCard = document.getElementById('tempCard');
  const currentCard = document.getElementById('currentCard');
  setTimeout(() => {
    if (motionCard) motionCard.textContent = 'Motion: OFF';
    if (tempCard) tempCard.textContent = 'Temp/Humidity: 24.6°C / 58%';
    if (currentCard) currentCard.textContent = 'Current: 0.42 A';
  }, 1800);
});

