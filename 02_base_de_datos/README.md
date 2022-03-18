# Base de datos

## Requisitos

- Raspberry pi
- Si es en línea servidor que soporte maria DB
- Para servicio local, Maria DB


## Pasos para la implementación

### Instalación de Maria DB

Actualización de los paquetes de la Raspberry, esto se hace a través de los siguiente comandos:

```sh
sudo apt update
sudo apt upgrade
```
instalar MariaDB con el siguiente comando:

```sh
sudo apt install mariadb-server
```
### Creación de bases de datos y tablas

Entrar a la terminal e iniciar maria db

```sh
sudo mariadb
```

Entrar con las credenciales

```sh
mysql -u nombreusuario -p 
```
Ejecutar el script 01_Base_de_Datos.sql

```sh
source 01_Base_de_Datos.sql;
```

Con esto nos genera la base de datos y las tablas usadas en el proyecto.