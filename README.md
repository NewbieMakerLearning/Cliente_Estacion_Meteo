# Cliente_Estacion_Meteo
**IMPORTANTE**
Para hacer funcionar el código hay que editar los siguientes archivos.

Renombrar:

 - Cliente_DB_Telegram_DEMO.cpp a **Cliente_DB_Telegram.cpp**
 - config_DEMO.h a **config.h**
 - index_DEMO.php a **index.php**
 
Moverlos a la carpeta src
 
 La idea original era mucho más sencilla de lo que ha quedado finalmente. Al ir viendo posibilidades fui añadiendo utilidades, por ejemplo una base de datos para consulta del histórico de mediciones. Un bot de Telegram para darle inmediatez a la consulta. Un __dashboard__, a parte del de Thinger.io, con los datos locales y con una visualización más agradable realizado con Grafana.
 
 El cliente tiene un sensor **BME280** que mide la temperatura y humedad interior. La calidad de la señal RSSI también la medimos para asegurarnos de la cobertura wifi.
 
 En principio había pensado usar una pantalla Nextion para poder visualizar todos los datos de los sensores, pero al ser bastante nuevo con Arduino he ido aprendiendo y viendo diferentes posibilidades. Así que esta primera versión carecerá de ella y será la versión 2 donde añadiré la pantalla. Esta versión es totalmente funcional.
 
 Una vez recoge los datos desde la API de [Thinger.io](https://www.thinger.io/) añade las lecturas locales y la envía a una base de datos creada en un NAS Synology mediante un archivo PHP. La base de datos está creada con MariaDB y gestionada con phpMyAdmin.
 
 Se pueden hacer peticiones con dos comandos al bot de Telegram.
 
 **API DE THINGER.IO**
 
 Para poder obtener las mediciones del servidor usé la API de Thinger.io. Al ser bastante novato y no estar acostumbrado a desembolverme en este ámbito, me costó encontrar la API y hacerla funcionar, jajaja. Ahora, gracias a la horas que le he dedicado a InfluxDB y a su documentación, he aprendido un poco más y me manejo mejor, no mucho, jajaja.
 
 La API tiene este formato:
 
 http://api.thinger.io/v1/users/NUESTRA_ID/buckets/NUESTRO_BUCKET/data?items=1&max_ts=[NUESTRO_TOKEN]
 
 Cuando tengamos nuestra dirección http completa podemos usar [POSTMAN](https://www.postman.com/) para desparsear nuestro JSON y de esa manera poder sacar las mediciones y guardarlas en variables dentro del sketch.
 
 ![](https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/Postman1.JPG)
 
 **__Una breve explicación de esta función.__**
 
 Para poder tener las mediciones en variables usé una función que un usuario de Thinger.io community me enseñó. Después de cada "," viene el siguiente valor que queremos recuperar, excepto la última que acaba con "}".
 
 Los datos a buscar son el nombre. Por ejemplo, "Altitud aproximada" y después un valor. La función buscará esa String que le hemos indicado y el valor que termina con una ","
  
 **BOT DE TELEGRAM**
 
 Como he escrito anteriormente, con el bot de Telegram podemos usar dos comandos.
  - Datos - muestra las últimas lecturas de los sensores. (El sensor de radiación se rompió, la lectura es errónea.)

<p align="center">
  <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/Telegram_Datos.jpg" width="450" title="hover text">
  </p>
  - Link - envía un enlace hacia el __dashboard__ de Grafana.
  <p align="center">
 <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/Telegram_link%20(1).jpg" width="450">
  </p>
  
  **GRAFANA**
  
  Las opciones que tiene Grafana son abrumadoras. Como no soy ningún experto he pensado que es mejor que si tenéis dudas, busquéis por internet que hay verdaderos profesionales que lo explican perfectamente.
  
  Durante este proyecto pensé en realizar una página web y alojarla en mi servidor para poder hacer consultas de las mediciones deseadas en un periodo de tiempo en concreto. Al ver webs de aficionados a la meteorología pensé que era una buena opción. Con Grafana conseguir esto es realmente rápido y sencillo.
  
  ![Alt text](https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/dashboard_GRAFANA1.JPG)
  
  <p align="center">
 
  __Las líneas rectas que hay en algunas gráficas se deben a un corte de luz__
  
  Puedes ver las mediciones en periodos de tiempo como 5', 15', 1h, 6h, 24h, 1 semana, 1 año, etc. Puedes mostrar la máxima, la mínima, un promedio y la actual, todo ello con unos simples clicks y sin nada de edición. 
  
  <p align="center">
  <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/dashboard_GRAFANA2.JPG" width="450" title="hover text">
 <br>
 <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/dashboard_GRAFANA3.JPG" width="650" title="hover text">
  </p>
   
   <p align="center">
 
  _Histórico de la última semana_

