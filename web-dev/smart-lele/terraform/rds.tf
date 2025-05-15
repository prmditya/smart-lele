resource "aws_db_parameter_group" "smartlele_rds_parameter" {
  name        = "smartlele-mysql-params"
  family      = "mysql8.0"
  description = "RDS MySQL timezone Asia/Jakarta"

  parameter {
    name  = "time_zone"
    value = "Asia/Bangkok"
  }

  tags = {
    Name = "smartlele-mysql-params"
  }
}

resource "aws_security_group" "rds_sg" {
  name        = "smart-lele-rds-sg"
  description = "Allow DB access from EC2"
  vpc_id      = aws_vpc.main.id

  ingress {
    from_port       = 3306
    to_port         = 3306
    protocol        = "tcp"
    security_groups = [aws_security_group.ec2_sg.id] # only from EC2
  }

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

resource "aws_db_instance" "smart_lele_db" {
  allocated_storage      = 20
  engine                 = "mysql"
  engine_version         = "8.0.36"
  instance_class         = "db.t3.micro"
  db_name                = var.db_name
  username               = var.db_username
  password               = var.db_password
  skip_final_snapshot    = true
  publicly_accessible    = false
  db_subnet_group_name   = aws_db_subnet_group.smartlele_db_subnet_group.name
  vpc_security_group_ids = [aws_security_group.rds_sg.id]
  parameter_group_name   = aws_db_parameter_group.smartlele_rds_parameter.name
}

resource "aws_db_subnet_group" "smartlele_db_subnet_group" {
  name       = "smartlele-db-subnet-group"
  subnet_ids = [aws_subnet.private_1a.id, aws_subnet.private_1b.id]
  tags = {
    Name = "smartlele-db-subnet-group"
  }
}
