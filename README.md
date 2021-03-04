# Cliente_Estacion_Meteo
 Cliente operativo 2021_02_19
 
 El cliente tiene un sensor **BME280** que mide la temperatura y humedad interior. La calidad de la señal RSSI también la medimos para asegurarnos de la cobertura wifi.
 En principio había pensado usar una pantalla Nextion para poder visualizar todos los datos de los sensores, pero al ser bastante nuevo con Arduino he ido aprendiendo y viendo diferentes posibilidades. Así que esta primera versión carecerá de ella. 
 
 Esta versión es totalmente funcional. Una vez recoge los datos desde la API de [Thinger.io](https://www.thinger.io/)
 Los datos se podrán visualizar desde **Grafana** y desde un **bot de Telegram**.
