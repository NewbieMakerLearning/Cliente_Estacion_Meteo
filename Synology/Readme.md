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

Abrimos la consola de administración phpMyAdmin y le damos a **_Nueva_** para crear nuestra DB.

<p align="center">
  <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/DB1.JPG" width="650" title="hover text">
</p>
<br>


Le ponemos el nombre que usaremos después. Apuntarlo o recordar donde encontrarlo.

Ahora creamos una tabla para poder mostrar esos datos. Importante elegir el número de columnas necesario para que quepan todas nuestras métricas.

<p align="center">
  <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/DB2.JPG" width="650" title="hover text">
</p>
<br>
imagen

En la tabla que hemos creado tenemos que detallar el nombre, el tipo de variable a mostrar y yo he puesto en comentarios la unidad de medición del sensor.

<p align="center">
  <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/DB3.JPG" width="650" title="hover text">
</p>
<br>

Tras rellenar lo necesario nos debería quedar algo así.

<p align="center">
  <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/DB4.JPG" width="650" title="hover text">
</p>
<br>

Es extremadamente importante que el tipo de variable coincida con la nuestra medición, si no sucede así, no conseguiremos registrar ningún dato en la DB.

Con esto ya tendríamos nuestra tabla operativa.

Si queréis hacer pruebas escribiendo en la base de datos manualmente podéis usar la dirección que está en el código arduino.

http://IP_SERVIDOR/NUESTRA_DB/index.php?tempint=7&humeint=9&tempout=1&humeout=70&presion=1025.15&lumi=160

En este ejemplo solo hay 6 variables para pasarlas a la base de datos. Según lo explicado anteriormente, respecto a las tablas, ¿Podríamos usarla así? 

...

...

Pues dependerá del número de columnas que tengamos en nuestra tabla y de las variables elegidas.

Para usar este ejemplo podemos cambiar los números por los que queramos. La primera medición, tempint=7 podemos poner tempint=10...

Ponemos esa dirección que acabamos de crear en el navegador usado, después de darle a intro volvemos a phpMyAdmin y en la tabla deberíamos ver nuestros datos. Este sistema me sirvió de mucha ayuda hasta que comprendí un poco la base de datos.

Recordar tener el archivo .php en el lugar adecuado antes de intentar hacer funcionar este método.