# **BOT DE TELEGRAM**

Cuando descubrí los bots de Telegram pensé que sería buena idea añadir uno a este proyecto. Ver los datos mediante gráficas está muy bien, pero te requiere un 
tiempo que a veces no tenemos o simplemente buscamos inmediatez. Gracias al bot de Telegram y al uso de una sola palabra podemos disponer de todos los datos en menos
de 5 segundos, a veces en 1.

La manera rápida y sencilla de crearlo es usando [Botfather](https://t.me/botfather)

## **CREAR EL BOT**

Abrimos un char con BotFather y escribimos lo siguiente:

``` 
/newbot 
```

Recibiremos algo así como esto:

```
Alright, a new bot. How are we going to call it? Please choose a name for your bot.
```
Elegimos el nombre de nuestro bot  y pulsamos intro.

```TITUTLO_NUESTRO_BOT```

Nos saldrá un mensaje infomándonos que vamos a darle un nobre a nuestro bot.

```Good. Now let's choose a username for your bot. It must end in `bot`. Like this, for example: TetrisBot or tetris_bot.```

El nombre ha de terminar con la palabra bot al final.

```NUESTRO_BOT```

```Done! Congratulations on your new bot. You will find it at t.me/NOMBRE_BOT. You can now add a description, about section and 
profile picture for your bot, see /help for a list of commands. By the way, when you've finished creating your cool bot, ping 
our Bot Support if you want a better username for it. Just make sure the bot is fully operational before you do this.

Use this token to access the HTTP API:
[TOKEN]
Keep your token secure and store it safely, it can be used by anyone to control your bot.

For a description of the Bot API, see this page: https://core.telegram.org/bots/api
```

Ya tenemos creado nuestro bot y si nos fijamos ese String tan largo es nuestro Token que usaremos en nuestro código para poder contactar con él.

Si en el mismo chat escribimos 
```/mybots```
Obtendremos una lista con todos nuestros bots. Elejimos el que acabamos de crear y tenemos más opciones de edición.

<p align="center">
  <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/Telegram/opciones.jpg" width="450" title="hover text">
</p>
<br>

Pulsando en _Edit Bot_ podemos editar el nombre, la descripción y los comandos entre otras cosas.

<p align="center">
  <img src="https://github.com/NewbieMakerLearning/Cliente_Estacion_Meteo/blob/master/Telegram/descripcion.png" width="450" title="hover text">
</p>
<br>

En la imagen podéis ver que tenía hasta 10 comandos.  Tuve que borrarlos casi todos porque tenía problemas de _panic kernel_ supongo que por trabajar con demasiadas
String, no estoy seguro, si alguien lo lee y me puede hacer una crítica al respecto, le estaré agradecido. Dejé dos comandos que son **_Datos_** y **_Link_**

