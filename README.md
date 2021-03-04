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
  - Link - envía un enlace hacia el __dashboard__ de Grafana.
