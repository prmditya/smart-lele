// Initialize charts
let phChart, tempChart, turbidityChart;

document.addEventListener("DOMContentLoaded", function () {
  // Initialize charts
  initializeCharts();

  // Load initial data
  fetchData();

  // Set up refresh button
  document.getElementById("refreshBtn").addEventListener("click", fetchData);

  // Set up auto-refresh every 30 seconds
  setInterval(fetchData, 30000);
});

function initializeCharts() {
  const chartOptions = {
    responsive: true,
    maintainAspectRatio: false,
    plugins: {
      legend: {
        display: false,
      },
      tooltip: {
        mode: "index",
        intersect: false,
        callbacks: {
          title: function (context) {
            // Menampilkan format panjang di tooltip
            const dataIndex = context[0].dataIndex;
            const fullData = phChart.data.fullLabels;
            return fullData ? fullData[dataIndex] : context[0].label;
          },
        },
      },
    },
    scales: {
      x: {
        display: true,
        title: {
          display: true,
          text: "Waktu",
        },
      },
      y: {
        display: true,
        title: {
          display: true,
        },
      },
    },
    interaction: {
      mode: "nearest",
      axis: "x",
      intersect: false,
    },
  };

  // pH Chart
  const phCtx = document.getElementById("phChart").getContext("2d");
  phChart = new Chart(phCtx, {
    type: "line",
    data: {
      labels: [],
      fullLabels: [], // Untuk menyimpan label lengkap
      datasets: [
        {
          label: "pH Level",
          data: [],
          borderColor: "rgba(25, 118, 210, 1)",
          backgroundColor: "rgba(25, 118, 210, 0.1)",
          borderWidth: 2,
          tension: 0.1,
          fill: true,
        },
      ],
    },
    options: {
      ...chartOptions,
      scales: {
        ...chartOptions.scales,
        y: {
          ...chartOptions.scales.y,
          title: {
            display: true,
            text: "pH Level",
          },
          min: 0,
          max: 14,
        },
      },
    },
  });

  // Temperature Chart
  const tempCtx = document.getElementById("tempChart").getContext("2d");
  tempChart = new Chart(tempCtx, {
    type: "line",
    data: {
      labels: [],
      fullLabels: [],
      datasets: [
        {
          label: "Temperature",
          data: [],
          borderColor: "rgba(244, 67, 54, 1)",
          backgroundColor: "rgba(244, 67, 54, 0.1)",
          borderWidth: 2,
          tension: 0.1,
          fill: true,
        },
      ],
    },
    options: {
      ...chartOptions,
      scales: {
        ...chartOptions.scales,
        y: {
          ...chartOptions.scales.y,
          title: {
            display: true,
            text: "Temperature (°C)",
          },
        },
      },
    },
  });

  // Turbidity Chart
  const turbidityCtx = document
    .getElementById("turbidityChart")
    .getContext("2d");
  turbidityChart = new Chart(turbidityCtx, {
    type: "line",
    data: {
      labels: [],
      fullLabels: [],
      datasets: [
        {
          label: "Turbidity",
          data: [],
          borderColor: "rgba(76, 175, 80, 1)",
          backgroundColor: "rgba(76, 175, 80, 0.1)",
          borderWidth: 2,
          tension: 0.1,
          fill: true,
        },
      ],
    },
    options: {
      ...chartOptions,
      scales: {
        ...chartOptions.scales,
        y: {
          ...chartOptions.scales.y,
          title: {
            display: true,
            text: "Turbidity (NTU)",
          },
        },
      },
    },
  });
}

async function fetchData() {
  try {
    const response = await fetch("data_receiver.php");

    // Periksa jika response OK
    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`);
    }

    const data = await response.json();

    // Pastikan data adalah array
    if (!Array.isArray(data)) {
      console.error("Data received is not an array:", data);
      return;
    }

    updateCharts(data);
    updateTable(data);
    updateCurrentValues(data);
  } catch (error) {
    console.error("Error fetching data:", error);
  }
}

function updateCharts(data) {
  // Pastikan data ada dan tidak kosong
  if (!data || data.length === 0) {
    console.warn("No data available for charts");
    return;
  }

  // Ambil 10 data terakhir (karena sudah diurut DESC)
  const chartData = data.slice(0, 10).reverse(); // Reverse untuk urutan waktu yang benar

  // Update pH Chart
  phChart.data.labels = chartData.map((item) => item.waktu_short);
  phChart.data.fullLabels = chartData.map((item) => item.waktu_long);
  phChart.data.datasets[0].data = chartData.map((item) => parseFloat(item.ph));
  phChart.update();

  // Update Temperature Chart
  tempChart.data.labels = chartData.map((item) => item.waktu_short);
  tempChart.data.fullLabels = chartData.map((item) => item.waktu_long);
  tempChart.data.datasets[0].data = chartData.map((item) =>
    parseFloat(item.temp)
  );
  tempChart.update();

  // Update Turbidity Chart
  turbidityChart.data.labels = chartData.map((item) => item.waktu_short);
  turbidityChart.data.fullLabels = chartData.map((item) => item.waktu_long);
  turbidityChart.data.datasets[0].data = chartData.map((item) =>
    parseFloat(item.turbidity)
  );
  turbidityChart.update();
}

function updateTable(data) {
  const tableBody = document.getElementById("tableBody");
  tableBody.innerHTML = "";

  // Pastikan data ada
  if (!data || data.length === 0) {
    tableBody.innerHTML = '<tr><td colspan="5">No data available</td></tr>';
    return;
  }

  // Tampilkan 20 data terbaru (tidak perlu reverse karena sudah DESC)
  data.slice(0, 20).forEach((item) => {
    const row = document.createElement("tr");
    row.innerHTML = `
            <td>${item.waktu_long}</td>
            <td>${parseFloat(item.ph).toFixed(1)}</td>
            <td>${parseFloat(item.temp).toFixed(1)}</td>
            <td>${parseFloat(item.turbidity).toFixed(1)}</td>
            <td>${item.waterLevel}</td>
        `;
    tableBody.appendChild(row);
  });
}

function updateCurrentValues(data) {
  if (data.length > 0) {
    const latest = data[0]; // Data terbaru ada di index 0 karena sudah DESC
    document.getElementById("currentPh").textContent = parseFloat(
      latest.ph
    ).toFixed(1);
    document.getElementById("currentTemp").textContent = parseFloat(
      latest.temp
    ).toFixed(1);
    document.getElementById("currentTurbidity").textContent = parseFloat(
      latest.turbidity
    ).toFixed(1);
  }
}
