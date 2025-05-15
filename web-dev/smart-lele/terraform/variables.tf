variable "vpc_cidr" {
  default = "10.0.0.0/16"
}

variable "public_subnet_cidr" {
  default = "10.0.1.0/24"
}

variable "private_subnet_1a_cidr" {
  default = "10.0.10.0/24"
}

variable "private_subnet_1b_cidr" {
  default = "10.0.11.0/24"
}

variable "availability_zone_1a" {
  default = "us-east-1a"
}

variable "availability_zone_1b" {
  default = "us-east-1b"
}

variable "db_username" {
  type = string
}

variable "db_password" {
  type      = string
  sensitive = true
}

variable "db_name" {
  type = string
}
