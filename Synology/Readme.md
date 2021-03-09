Para crear la base de datos en nuestro NAS Synology realicé los siguientes pasos.

Instalamos los siguientes paquetes:

- Servidor -  **_Apache HTTP Server 2.4_**
- Extensión - **_PHP 7.4_**
- Gestor BBDD - **_MariaDB10_**
- Consola de administración - **_phpMyAdmin_**
- **_Web station_**

Como crear un usuario de la base de datos os lo dejo a vosotros, no es difícil, si yo he podido, vosotros también, ;)

En _MariaDB_ **habilitamos la conexión TCP/IP** y el puerto **3307** es por defecto.

<p align="center">
  <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/MariaDb_activar_TCP_IP.JPG" width="450" title="hover text">
</p>
<br>

En _Web station_ podemos ver todos los paquetes instalados. No todos los que veis aquí son necesarios.

<p align="center">
  <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/Web_Station_1.JPG" width="550" title="hover text">
</p>
<br>

Elejimos _Apache_ y la versión de _PHP_ que hayamos instalado. Habilitamos el sitio web personal. 

<p align="center">
  <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/Habilitar_Web_personal.JPG" width="550" title="hover text">
</p>

<br>

En la sección de _host virtual_ creamos uno nuevo y lo hacemos basado en el puerto, tanto **HTTP como HTTPS**. 

<p align="center">
  <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/host_Virtual_1.JPG" width="550" title="hover text">
</p>
<br>

**En la raiz del documento** elegimos la ruta de la carpeta que nos ha creado **Web Station**. Suele estar por defecto en [IP_SERVIDOR]/web/ que es donde está alojado el archivo **_index.php_**. El encargado de pasar las mediciones a la base de datos.

**ejemplo**

http://192.168.1.50/web/base_de_datos

**Servidor back-end HTTP** elegimos nuestro servidor instalado anteriormente, _Apache_.

**En PHP**, elegimos nuestro perfil de PHP, el mismo paquete que hemos instalado.

Le damos a ok.

<p align="center">
  <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/host_Virtual_2.JPG" width="450" title="hover text">
</p>
<br>

**Es importante darle permisos de escritura y lectura al usuario que accederá a la carpeta donde esté nuestro archivo _index.php_.**

La web de [Naseros](http://www.naseros.com) es muy útil para configurar el NAS

Con esto ya tendríamos nuestra servidor listo para crear la base de datos.