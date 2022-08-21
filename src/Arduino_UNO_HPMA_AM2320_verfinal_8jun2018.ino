/*
  Multiple Serial test

  Receives from the main serial port, sends to the others.
  Receives from serial port 1, sends to the main serial (Serial 0).

  This example works only with boards with more than one serial like Arduino Mega, Due, Zero etc.

  The circuit:
  - any serial device attached to Serial port 1
  - Serial Monitor open on Serial port 0

  created 30 Dec 2008
  modified 20 May 2012
  by Tom Igoe & Jed Roach
  modified 27 Nov 2015
  by Arturo Guadalupi

  This example code is in the public domain.
*/
int incomingByte = 0;   // for incoming serial data
unsigned int PM10 = 0;
unsigned int PM25 = 0;
unsigned int contador = 0;
byte contador1=0;
unsigned long PMtotal = 0;
float PMdiv = 0;
float h=0;
byte hbyte=0;
String txtMsg = "";                         // a string for incoming text
String txtMsgwhite = "";

// include the SevenSegmentTM1637 library
#include "SevenSegmentTM1637.h"
#include <SoftwareSerial.h>
//#include "Adafruit_Sensor.h"
//#include "Adafruit_AM2320.h"
#include "DHT.h"

const byte PIN_CLK = A2;   // define CLK pin (any digital pin)
const byte PIN_DIO = A0;   // define DIO pin (any digital pin)
const byte unouno=1;
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);
SoftwareSerial mySerial(2,3); //rx,tx

#define DHTPIN 6     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // initialize both serial ports:
  pinMode(12, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

  digitalWrite(7, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);

  mySerial.begin(9600);
  Serial.begin(9600);

  Serial.println("DHTxx test!");
  dht.begin();
 
  display.begin();            // initializes the display
  display.setBacklight(100);  // set the brightness to 100 %
  display.print("ESP");      // display INIT on the display
  delay(3000);                // wait 1000 ms
  display.setCursor(0, 3);
  display.print("5");
  delay(1000);                // wait 1000 ms
  display.print("4");
  delay(1000);                // wait 1000 ms
  display.print("3");
  delay(1000);                // wait 1000 ms
  display.print("2");
  delay(1000);                // wait 1000 ms
  display.print("1");
  delay(1000);                // wait 1000 ms
  display.print("0");
  delay(1000);                // wait 1000 ms
}

void loop() {

  while (txtMsg.length() < 32) {

    while (mySerial.available() > 0) {
      char inChar = mySerial.read();
      txtMsg += inChar;
    }
  }

  Serial.println("");
  //Serial.println ("Trama: " + String(txtMsg[0], DEC) + "," + String(txtMsg[1], DEC) + "," + String(txtMsg[2], DEC) + "," + String(txtMsg[3], DEC) + "," + String(txtMsg[4], DEC) + ","
  //                + String(txtMsg[5], DEC)  + "," + String(txtMsg[6], DEC)  + "," + String(txtMsg[6], BIN) + "," + String(txtMsg[7], DEC) + "," + String(txtMsg[7], BIN )+ "," + String(txtMsg[8], DEC) + "," + String(txtMsg[8], BIN)+ "," + String(txtMsg[9], DEC) + "," + String(txtMsg[9], BIN) + "," + String(txtMsg[10], DEC) + "," + String(txtMsg[11], DEC) + "," + String(txtMsg[12], DEC) + ","
  //                + String(txtMsg[13], DEC) + "," + String(txtMsg[14], DEC) + "," + String(txtMsg[15], DEC) + "," + String(txtMsg[16], DEC) + "," + String(txtMsg[17], DEC) + "," + String(txtMsg[18], DEC) + "," + String(txtMsg[19], DEC) + "," + String(txtMsg[20], DEC) + "," + String(txtMsg[21], DEC) + "," + String(txtMsg[22], DEC) + ","
  //                + String(txtMsg[23], DEC) + "," + String(txtMsg[24], DEC) + "," + String(txtMsg[25], DEC) + "," + String(txtMsg[26], DEC) + "," + String(txtMsg[27], DEC) + ","
  //                + String(txtMsg[28], DEC) + "," + String(txtMsg[29], DEC) + "," + String(txtMsg[30], DEC) + "," + String(txtMsg[31], DEC)+ ";");



  if (txtMsg[0] == 66) {
    if (txtMsg[1] == 77) {
      PM25 = txtMsg[6] * 256 + byte(txtMsg[7]);
      PM10 = txtMsg[8] * 256 + byte(txtMsg[9]);
      Serial.println("ok PMhoney");
      Serial.println ("PM 2.5 honey: " + String(PM25) + " ug/m3");
      Serial.println ("PM  10 honey: " + String(PM10) + " ug/m3");
if (contador1<20) {
   contador1 = contador1 + 1;  
}
else {      
      contador = contador+1;
      PMtotal = PMtotal+PM25;
      Serial.println ("Contador: " + String(contador));
      Serial.println ("PMtotal: " + String(PMtotal));
      txtMsg = txtMsgwhite;
}
     
if (contador%2==0)
  {
        h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  
  Serial.print("AM2320  Hum: ");
  Serial.print(h);
  Serial.print("     Tem: ");
  Serial.print(t);
  Serial.print(" *C ");

  display.clear();                      // clear the display
    if (h<94){
  display.print(PM25);                   // display loop counter  
  }
  else
  {
  display.print("Hu95");                   // display loop counter    
  }
  }
 else
 {
  display.clear();                      // clear the display
    if (h<94){  
  display.print(PM25);                   // display loop counter
  display.setCursor(0, 3);
  display.print("_");
 }
  else
  {
  display.print("Hu95");                   // display loop counter    
  }
  } 
  } 
    else {
      Serial.println("MAL dato PMhoney");
      display.clear();                      // clear the display
      display.print("MAL");                   // display loop counter
  
    }
  }
    else {
      Serial.println("MAL dato PMhoney");
      display.clear();                      // clear the display
      display.print("MAL");                   // display loop counter
  
  }    
    
   if (digitalRead(12) == LOW) {
   delay (10);
   if (digitalRead(12) == LOW) {
   delay (10);
   if (digitalRead(12) == LOW) { 

   hbyte = (int) h;
   display.clear();                      // clear the display
   display.print ("H_"+ String(hbyte));
   delay (1000); 
      }
    }
  }

   if (digitalRead(12) == LOW) {
   delay (2000);
   if (digitalRead(12) == LOW) {
   delay (2000);
   if (digitalRead(12) == LOW) { 

   PMdiv = PMtotal/contador;
   round (PMdiv);
   PMtotal = (int) PMdiv; 
   
 while (unouno==1){
   display.clear();                      // clear the display
   display.print(PMtotal);                   // display loop counter
   Serial.println (String(PMdiv));
   delay (1000);
   display.clear();                      // clear the display
   display.print(contador);                   // display loop counter
   Serial.println (String(contador));
   delay (1000);
   
 }

      }
    }
  }
  delay (800);

}


