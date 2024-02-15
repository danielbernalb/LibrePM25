# LibrePM25
Medidor de Material Particulado básico con sensor de PM2.5 PMSx003, Arduino UNO y Multi-function Shiel.

![Medidor PM25](https://github.com/danielbernalb/LibrePM25/blob/master/img/LibrePM25_640.jpg)

En acción:

![LibrePM25&DustTrackMaterials](https://github.com/danielbernalb/LibrePM25/blob/master/img/Libre%26Dust.jpg)


# LibreCO2
LibreCO2: Medidor de CO2 usando Arduino UNO y un sensor de CO2 comercial (SenseAir S8, Sensirion SCD30, Winsen MH-Z14 o MHZ-19 o Cubic CM1106).

Esta es una versión básica de un medidor de PM2.5 de bajo costo con los materiales más comunes del mercado: Arduino UNO y el sensor más económico y popular: PMSx003. LibrePM25 usa un Arduino UNO, pero puede extenderse al MEGA o nano, por ser muy popular en escuelas y frecuentemente usado en las clases de tecnología o electrónica y la mayoría de escuelas tienen muchos de ellos. 

El código del Arduino es lo más sencillo posible y puede programarse cargando el archivo .hex con el programa Xloader y así no necesitarías instalar el software Arduino para compilar y programar el código. Si buscas un sensor más avanzado y con conectividad por Bluetooth o por Wifi puedes armar un AireCiudadano [AireCiudadano](https://github.com/danielbernalb/AireCiudadano) con conectividad Bluetooth y Wifi. LibrePM25 usa los componentes más populares del mercado, así no sean los más avanzados, y el armado más sencillo posible sin necesitar el uso de cautín y soldadura de estaño.

# 1. Materiales:

Existen dos opciones para el armado de sensor, la más sencilla es usando un Escudo Multifunción (Shield) de Arduino el cual ya incluye el Display de 4 dígitos con lo cual se facilita mucho más el montaje. La segunda es armando las partes por individual.

# 1.1. Opción con Escudo multifunción:

![Materiales](https://github.com/danielbernalb/LibreCO2/blob/main/images/Materiales%20sensor.jpg)

1. Escudo multifunción (Arduino Shield multifunction).

El Escudo tiene un bug o error que puede cortocircuitarlo con el conector USB, corte los pines que se muestran en la foto y agregue un trozo de cinta al conector USB (que también se muestra en el [video explicativo](https://github.com/danielbernalb/LibreCO2/blob/main/INSTRUCCIONES%20en%20Espa%C3%B1ol.md#video-explicativo):

![Cortar pines escudo](https://github.com/danielbernalb/LibreCO2/blob/main/images/Corte%20pines%20escudo_cinta.jpg)

Link compra [Aliexpress](https://es.aliexpress.com/wholesale?SearchText=multifunction-arduino-shield), Link compra [Colombia](https://listado.mercadolibre.com.co/arduino-escudo-multi-funcion#D[A:arduino%20escudo%20multi%20funcion]), Compra Latinoamérica: Mercadolibre o tiendas de electrónica.

2. Arduino UNO cualquier versión. Sirve el original Arduino Italiano o las versiones chinas, la diferencia está en la instalación del driver. El que llaman "Original" a la izquierda y la copia o clone a la derecha:

![Arduino original & clone](https://github.com/danielbernalb/LibreCO2/blob/main/images/arduino-uno-original-clone.jpg)

Link compra [Aliexpress](https://es.aliexpress.com/wholesale?catId=0&initiative_id=SB_20210322194538&SearchText=arduino+uno+r3), Link compra [Colombia](https://listado.mercadolibre.com.co/arduino-uno#D[A:arduino%20uno]), Compra Latinoamérica: Mercadolibre o tiendas de electrónica.

3. 3 cables jumper hembra hembra (sirve cualquier tamaño pero es preferible 10 o 15cm).

Link compra [Aliexpress](https://es.aliexpress.com/wholesale?SearchText=jumper-wires), Link compra [Colombia](https://listado.mercadolibre.com.co/arduino-jumper-hembre-hembra#D[A:arduino%20jumper%20hembre%20hembra]), Compra Latinoamérica: Mercadolibre o tiendas de electrónica.

4. Sensor PMSx003, opciones:

	a. PMS7003 es el que más utilizo por lo delgado y testeado.

	![SenseAir S8](https://github.com/danielbernalb/LibreCO2/blob/main/images/SenseAir_S8.jpg)
	
	Link desde Aliexpress China:
	https://es.aliexpress.com/item/4000884582128.html
	
	Link desde Digikey USA:
	https://www.digikey.com/es/products/detail/senseair-north-america-inc/004-0-0053/10416532
	
	
****************************

**Conexiones para cada sensor:**


**SenseAir S8 sensor**

GND ---> G0 Pin 2 de la regleta de 4 pines

+5 &nbsp; ---> G+ Pin 1 de la regleta de 4 pines

5 &nbsp; &nbsp; ---> Pin 2 de la regleta de 5 pines

6 &nbsp; &nbsp; ---> Pin 3 de la regleta de 5 pines

![SenseAir S8](https://github.com/danielbernalb/LibreCO2/blob/main/images/shield_senseair.jpg)

## Video explicativo (aplica tambien para el LibrePM25 sólo que la conexión de los cables es diferente):

[![](http://img.youtube.com/vi/KYHC06xhUu4/0.jpg)](http://www.youtube.com/watch?v=KYHC06xhUu4 "VideoLibreCO2")

# 1.2. Opción por partes individuales:

1. Arduino UNO original o versión china.
2. Display TM1687.
3. Jumper hembra - macho.
4. Uno o dos Pulsadores o cables (uno para la calibración, otro para el nivel de Beep).
5. Opcional: Buzzer.

![Materiales](https://github.com/danielbernalb/LibreCO2/blob/main/images/Materials%20all%20text.jpg)

6. Sensor, iguales opciones que la opción con Escudo multifunción.

****************************


**Conexiones para todos los sensores:**

Componente electrónico ---> PIN del Arduino

**Display---> PIN Arduino**

CLK    ---> 9

DIO    ---> 8

VCC    ---> IOREF en la versión original o 5V en la copia china

GND    ---> GND


**Buzzer**

"+"    ---> 11

otro  ---> GND


**Pulsador de calibración**

Cualquiera ---> A0

Cualquiera ---> A2


**Pulsador de nivel del Beep**

Cualquiera ---> A3

Cualquiera ---> A5


**Pulsador de altura sobre el nivel del mar**

Cualquiera ---> 2

Cualquiera ---> 4


****************************
**SenseAir S8**

VIN Pin 1 de regleta de 4 pines ---> 5V 

GND Pin 2 de regleta de 4 pines ---> GND

RX Pin 2 de regleta de 5 pines ---> 6

TX Pin 3 de regleta de 5 pines ---> 7 


![SenseAir S8 connection](https://github.com/danielbernalb/LibreCO2/blob/main/images/parts_senseair.jpg)


****************************
# 2. Programar el Firmware (código en el Arduino)

Existen 3 opciones para programar el Arduino: la más sencilla es usar un teléfono Android y un cable USB OTG, la siguiente es usar un PC con el software Xloader y la última instalando Arduino en un PC.

**1. Teléfono Android.**

![USB OTG cable](https://github.com/danielbernalb/LibreCO2/blob/main/images/Cable%20USB%20OTGex.jpg)

 - Conecta el cable USB OTG al teléfono.
 - Instala la app de Android ["Arduino Hex Uploader-Firmware Bin Upload"](https://play.google.com/store/apps/details?id=xyz.vidieukhien.embedded.arduinohexupload&hl=en_US&gl=US).
 - Baja el archivo .hex file de este ["Directorio de Google drive"](https://drive.google.com/drive/folders/1FxXLVhaGF6UCVObQlh8cVLddyWyQqUT0) basado en la versión de tu sensor (Shield y marca de sensor). Encuentra el archivo .hex que vas cargar en el Arduino, cada versión de sensor (Sensirion, Winsen or Cubic) se encuentra disponible el el directorio "hex files". Ejemplo: "LibreCO2_MFShield_SCD30.hex" es el arhivo para el sensor Sensirion con el Shield Multifunción. Nota: No descargues el archivo .hex directamente de la página con la opción "Salvar como", que daña el archivo. Usa solamente el enlace de Google Drive.
 - Busca el archivo .hex en tú teléfono.
 - Sube el código a tu tarjeta Arduino.
 - FIN.

Video de programación de el Firmware:

[![](http://img.youtube.com/vi/_87qzZFMgwg/0.jpg)](http://www.youtube.com/watch?v=_87qzZFMgwg "LibreCO2")

Link compra Cable OTG USB [Aliexpress](https://es.aliexpress.com/wholesale?SearchText=otg+usb+cable&d=y&origin=n&catId=0&initiative_id=SB_20210315194053), Link compra [Colombia](https://listado.mercadolibre.com.co/cable-otg#D[A:cable%20otg]), Compra Latinoamérica: Mercadolibre o tiendas de electrónica.

**2. Usando tu PC con el software Xloader (sólo Windows):**

1. Conecta el Arduino a tu computador y espera a que el driver se instale automáticamente. Si el driver no se instala automáticamente debes identificar si tu Arduino es original o una copia:

1.1. Si el Arduino es original, instala el paquete Arduino con drivers: https://www.arduino.cc/en/Guide/ArduinoUno

1.2. Si el Arduino es copia china sigue las instrucciones de esta página web: https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers

2. Después de instalado el driver, tienes 2 opciones:

2.1. Si lo único que quieres es programar el Arduino desde Windows sin tener que ver el código y compilarlo, usa el software Xloader que se encuentra en la carpeta del mismo nombre:

![Xloader](https://github.com/danielbernalb/LibreCO2/blob/main/images/Xloader1.jpg)

A la izquierda se muestra la ventana del Xloader cuando se inicia.

2.1.1. Explora hasta encontrar el achivo .hex que vas a cargar en el Arduino. Cada versión de sensor (Sensirion, Winsen o Cubic) se encuentra disponible en el directorio "hex files". Ejemplo: "LibreCO2_Shield_SCD30.hex" es el archivo para el sensor Sensirion SCD30 con el uso del Escudo Multifunción (Shield). No lo descargues directamente de la página con la opción "Guardar como", eso arruina el archivo.  Usa el siguiente enlace de Google Drive para bajar el archivo .hex buscando tu versión de Sensor (SCD30, MHZ14_9 o CM1106) y construcción (con Shield o por Partes):
 
https://drive.google.com/drive/folders/1FxXLVhaGF6UCVObQlh8cVLddyWyQqUT0

2.1.2. Selecciona la tarjeta Arduino que estas usando (Uno/ATmega328).

2.1.3. Selecciona el puerto de comunicaciones COM al que está conectado el Arduino, si no lo sabes buscalo en el Admnistrador de dispositivos "Puertos COM y LPT".

2.1.4. Selecciona la velocidad Baud rate a 115200.

2.1.5. Presiona el botón “Upload”.

2.1.6. Cuando el archivo .hex file se carga en el Arduino, foto a la derecha, sale el mensaje de "xxxxx bytes uploaded", si falla te saldrá el mensaje de "upload fails".

**3. Si quieres editar y compilar el código instala el software Arduino en Windows, Mac o Linux:**
  
  https://www.arduino.cc/en/software
  
  La siguiente guía explica como instalar Arduino en Windows, Mac o Linux y es muy completa:
  https://learn.sparkfun.com/tutorials/installing-arduino-ide/all  
  
  En Youtube existen cientos de tutoriales para instalar Arduino en diferentes sistemas operativos y aprender su programación, además puedes colaborar mejorando este código o crear tu propia versión.  
  
 # 3. Caja para el sensor.
 
Opciones iniciando por la más sencilla y económica:

3.1. Caja comercial de bajo costo.

Busca una caja plástica con un ancho similar al del Arduino y un largo mayor para que en el espacio sobrante ubiques el sensor. En el espacio sobrante perfora varios huecos por dónde entre aire para el mismo, en mi caso los hice con destornillador de 4mm. Haz otro hueco para el Buzzer, para el cable USB y el adaptador y listo. Ejemplo:

![Caja1](https://github.com/danielbernalb/LibreCO2/blob/main/images/ImagesX4.jpg)

Cuando quieras usar el teclado para la calibración o la programación del BEEP, abre la caja y accede al teclado para luego volver a cerrala.
Puedes acomodar cajas plásticas de diferentes tamaños, en el siguiente caso se usa una espuma debajo porque la caja es más alta, además se hacen 3 huecos de un tamaño mediano (7mm) para los 3 botones y asó poder acceder desde afuera a los botones sin necesidad de abrir la caja:

![Caja2](https://github.com/danielbernalb/LibreCO2/blob/main/images/Images4_2.jpg)

3.2. Caja en madera MDF usando corte láser. En desarrollo.

3.3. Caja en PLA con impresora 3D. En desarrollo.
  
 # 4. Funcionamiento del sensor.
 
 Sólo es encenderlo y el sensor muestra el material particulado actual y lo refresca cada segundo.
  
****************************
### Contacto

Si tienes alguna duda, bug, aporte o comentario escríbeme al correo electrónico danielbernalb@gmail.com o la cuenta de twitter [@danielbernalb](https://twitter.com/danielbernalb) 
Más información en la página web: ["Aire ciudadano"](https://aireciudadano.com/)
