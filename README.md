# Cliente_Estacion_Meteo
 Cliente operativo 2021_02_19
 
 La idea original era mucho más sencilla de lo que ha quedado finalmente. Al ir viendo posibilidades fui añadiendo utilidades. Como fue una base de datos para tener un histórico de consulta en las mediciones. Un bot de Telegram para darle inmediatez a la consulta. Un __dashboard__, a parte del de Thinger.io, con los datos locales y con una visualización más agradable.
 
 El cliente tiene un sensor **BME280** que mide la temperatura y humedad interior. La calidad de la señal RSSI también la medimos para asegurarnos de la cobertura wifi.
 En principio había pensado usar una pantalla Nextion para poder visualizar todos los datos de los sensores, pero al ser bastante nuevo con Arduino he ido aprendiendo y viendo diferentes posibilidades. Así que esta primera versión carecerá de ella. 
 
 Esta versión es totalmente funcional. Una vez recoge los datos desde la API de [Thinger.io](https://www.thinger.io/) añade las lecturas locales y la envía a una base de datos creada en un NAS Synology mediante un archivo PHP.
 
 Los datos se podrán visualizar desde **Grafana** y desde un **bot de Telegram**.
 
 **BOT DE TELEGRAM**
 Como he escrito anteriormente, con el bot de Telegram podemos usar dos comandos.
  - Datos - muestra las últimas lecturas de los sensores.
  ![alt text](https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/Telegram_Datos.jpg)
  - Link - envía un enlace hacia el __dashboard__ de Grafana.
  ![alt text](https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/Telegram_link%20(1).jpg)
  
  **GRAFANA**
  Las opciones que tiene Grafana son abrumadoras. Como no soy ningún experto he pensado que es mejor que si tenéis dudas, busquéis por internet que hay verdaderos profesionales que lo explican perfectamente.
  Durante este proyecto pensé en realizar una página web y alojarla en mi servidor para poder hacer consultas de las mediciones deseadas en un periodo de tiempo en concreto. Al ver webs de aficionados a la meteorología pensé que era una muy buena opción. Al descubrir Grafana y conseguir hacerlo funcionar he ahorrado mucho tiempo.
  ![Alt text](https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/dashboard_GRAFANA1.JPG)
  __Las líneas rectas que hay en algunas gráficas se deben a un corte de luz__
  Puedes ver las mediciones en periodos de tiempo como 5', 15', 30', 1h, 3h, 6h, 12h, 24h etc. Puedes mostrar la máxima, la mínima, un promedio y la actual, todo ello con unos simples clicks y sin nada de edición. Mientras que si hubiera realizado la página web, todo esto hubiera sido más laborioso, sobre todo, porque no tengo conocimientos suficientes para llevarlo a cabo.
  ![Alt text](https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/dashboard_GRAFANA2.JPG)
  ![Alt text](https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/pictures/dashboard_GRAFANA3.JPG)
  __Histórico de la última semana__
