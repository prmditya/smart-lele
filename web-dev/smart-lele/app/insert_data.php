<?php
$servername = getenv('DB_HOST');
$username = getenv('DB_USERNAME');
$password = getenv('DB_PASSWORD');
$dbname = getenv('DB_NAME');

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// Debug POST
file_put_contents("log.txt", print_r($_POST, true), FILE_APPEND);

// Check if all expected POST values exist
if (!isset($_POST['ph']) || !isset($_POST['temp']) || !isset($_POST['waterLevel']) || !isset($_POST['turbidity']) || !isset($_POST['crc'])) {
  die("Missing POST data");
}

$ph = $_POST['ph'];
$temp = $_POST['temp'];
$waterLevel = $_POST['waterLevel'];
$turbidity = $_POST['turbidity'];
$receivedCRC = $_POST['crc'];

// Recalculate CRC
$data = "ph=$ph&temp=$temp&turbidity=$turbidity&waterLevel=$waterLevel";
$calculatedCRC = hash('crc32b', $data);

// Check CRC
if ((string)$receivedCRC === (string)$calculatedCRC) {
  $sql = "INSERT INTO sensor_data (ph, temp, turbidity, waterLevel, waktu) VALUES (?, ?, ?, ?, NOW())";
  $stmt = $conn->prepare($sql);
  $stmt->bind_param("dddd", $ph, $temp, $turbidity, $waterLevel);


  if ($stmt->execute()) {
    echo "Data inserted successfully";
  } else {
    echo "Insert error: " . $stmt->error;
  }
} else {
  echo "CRC mismatch! Received: $receivedCRC, Calculated: $calculatedCRC";
}

$conn->close();
