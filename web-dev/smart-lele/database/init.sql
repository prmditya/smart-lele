CREATE DATABASE IF NOT EXISTS smartlele;

USE smartlele;

CREATE TABLE sensor_data (
  id INT AUTO_INCREMENT PRIMARY KEY,
  ph FLOAT,
  temperature FLOAT,
  turbidity FLOAT,
  water_level FLOAT,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
