<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta name="description" content="Smart Lele Monitoring Dashboard">
  <title>Smart Lele Dashboard</title>

  <!-- Favicon -->
  <link rel="icon" href="/public/assets/smartlele-icon.ico" type="image/x-icon">

  <!-- Google Fonts & Icons -->
  <link href="https://fonts.googleapis.com/css2?family=Inter:ital,opsz,wght@0,14..32,100..900;1,14..32,100..900&display=swap" rel="stylesheet">
  <link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons" />

  <!-- Chart.js -->
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>

  <!-- Custom CSS -->
  <link rel="stylesheet" href="/public/style.css">
</head>


<body>
  <div class="app-container">
    <header class="app-header">
      <h1>Smart Lele Monitoring Dashboard</h1>
    </header>

    <main class="app-main">
      <div class="dashboard-grid">
        <!-- Card 1: pH Level -->
        <div class="dashboard-card">
          <div class="card-header">
            <h2>pH Level</h2>
          </div>
          <div class="card-content">
            <canvas id="phChart"></canvas>
            <div class="current-value">
              <span class="value" id="currentPh">7.0</span>
              <span class="unit">pH</span>
            </div>
          </div>
        </div>

        <!-- Card 2: Temperature -->
        <div class="dashboard-card">
          <div class="card-header">
            <h2>Temperature</h2>
          </div>
          <div class="card-content">
            <canvas id="tempChart"></canvas>
            <div class="current-value">
              <span class="value" id="currentTemp">28</span>
              <span class="unit">°C</span>
            </div>
          </div>
        </div>

        <!-- Card 3: Turbidity -->
        <div class="dashboard-card">
          <div class="card-header">
            <h2>Turbidity</h2>
          </div>
          <div class="card-content">
            <canvas id="turbidityChart"></canvas>
            <div class="current-value">
              <span class="value" id="currentTurbidity">5</span>
              <span class="unit">NTU</span>
            </div>
          </div>
        </div>

        <!-- Data Table -->
        <div class="data-table-container">
          <div class="table-header">
            <h2>Historical Data</h2>
            <div class="table-controls">
              <button id="refreshBtn" class="refresh-btn">
                <i class="material-icons">refresh</i>
              </button>
            </div>
          </div>
          <div class="table-wrapper">
            <table id="dataTable">
              <thead>
                <tr>
                  <th>Waktu</th>
                  <th>pH</th>
                  <th>Temp (°C)</th>
                  <th>Turbidity (NTU)</th>
                  <th>Water Level (cm)</th>
                </tr>
              </thead>
              <tbody id="tableBody">
                <!-- Data will be inserted here by JavaScript -->
              </tbody>
            </table>
          </div>
        </div>
      </div>
    </main>

    <footer class="footer">
      <div class="footer-content">
        <div class="footer-section branding">
          <img src="/public/assets/smartlele-icon.png" width="40" alt="Logo">
          <h3>Smart Lele</h3>
        </div>

        <p>Solusi pintar untuk monitoring kualitas air kolam secara real-time dan efisien.</p>

        <hr>

        <div class="footer-bottom">
          <p>Made with ❤️ by <a href="https://github.com/prmditya/smart-lele">@Kelompok 4</a></p>
          <p>Copyright © 2025 All Rights Reserved.</p>
        </div>
    </footer>

  </div>

  <!-- JavaScript -->
  <script src="https://cdnjs.cloudflare.com/ajax/libs/material-ui/5.0.0-beta.5/umd/material-ui.development.min.js"></script>
  <script src="/public/script.js"></script>
</body>

</html>