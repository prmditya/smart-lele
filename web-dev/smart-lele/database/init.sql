CREATE DATABASE IF NOT EXISTS smartleledb;

USE smartleledb;

CREATE TABLE sensor_data (
  id INT AUTO_INCREMENT PRIMARY KEY,
  ph FLOAT,
  temp FLOAT,
  turbidity FLOAT,
  waterLevel FLOAT,
  waktu TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
