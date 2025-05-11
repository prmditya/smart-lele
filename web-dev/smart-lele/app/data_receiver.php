<?php
header('Content-Type: application/json');

// Koneksi ke database MySQL
$servername = getenv('DB_HOST');
$username = getenv('DB_USERNAME');
$password = getenv('DB_PASSWORD');
$dbname = getenv('DB_NAME');

// Membuat koneksi
$conn = new mysqli($servername, $username, $password, $dbname);

// Cek koneksi
if ($conn->connect_error) {
  die(json_encode(['error' => "Connection failed: " . $conn->connect_error]));
}

// Jika bukan POST request, ambil data untuk dashboard
// Mengambil 20 data terakhir untuk grafik dan tabel
$sql = "SELECT 
            DATE_FORMAT(waktu, '%H:%i') as waktu_short,
            DATE_FORMAT(waktu, '%d %b %Y, %H:%i') as waktu_long,
            ph, 
            temp, 
            turbidity, 
            waterLevel 
        FROM sensor_data 
        ORDER BY waktu DESC 
        LIMIT 20";

$result = $conn->query($sql);

$data = [];
if ($result->num_rows > 0) {
  while ($row = $result->fetch_assoc()) {
    $data[] = $row;
  }
  // Tidak perlu array_reverse karena kita pakai ORDER BY DESC
} else {
  // Jika tidak ada data, kembalikan array kosong
  $data = [];
}

echo json_encode($data);
$conn->close();
