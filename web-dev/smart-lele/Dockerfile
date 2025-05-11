# Menggunakan image PHP dengan Apache
FROM php:8.2-apache

# Install ekstensi MySQLi dan PDO (opsional)
RUN docker-php-ext-install mysqli pdo pdo_mysql

# Salin file aplikasi (PHP dari `app/` dan aset dari `public/`)
COPY ./app /var/www/html/          

# Aktifkan mod_rewrite untuk Apache (jika perlu)
RUN a2enmod rewrite

# Pastikan apache berjalan di background
CMD ["apache2-foreground"]