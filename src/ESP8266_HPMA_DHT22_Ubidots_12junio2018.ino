#include <ESP8266WiFi.h>

#include "DHT.h"

#include <TM1637Display.h>

#define DHTPIN D3     // what digital pin we're connected to

#define errorPin 16

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

String txtMsg = "";                         // a string for incoming text
String txtMsgwhite="";

unsigned int PM25 = 0;
unsigned int PM10 = 0;
float PM25seg = 0;
float PM10seg = 0;
int   PM25int = 0;
int   PM10int = 0;

unsigned int PM25nova = 0;
unsigned int PM10nova = 0;
float PM25segnova = 0;
float PM10segnova = 0;
int   PM25intnova = 0;
int   PM10intnova = 0;

unsigned int PM25old = 0;
unsigned int PM10old = 0;
unsigned int PM25novaold = 0;
unsigned int PM10novaold = 0;


int   muestra = 0;
int modus = 0;
unsigned int segundos = 0;
int contador = 0;


const int CLK = D5; //Set the CLK pin connection to the display
const int DIO = D6; //Set the DIO pin connection to the display
 
TM1637Display display(CLK, DIO); //set up the 4-Digit Display.

DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

String variable_id1 = "5a502b1fc03f971bb0f247fc"; 
String variable_id2 = "5a502b1ac03f971b6841edd8"; 
String variable_id3 = "5a6ba7d5c03f97684622dfa9";
String variable_id4 = "5a6ba816c03f9767c5d4bdc6";

String token = "A1E-bHMABjkDnD0U32L405HNVM1oiIaBXK";
const char* ssid = "BelkinTX";
const char* password = "apt413sago16";




//////////////////////////////////////////////////////////////////////////////////
// Function Prototypes
void ubiSave_value1(String, String);
void ubiSave_value2(String, String);

void setup() {
  // initialize both serial ports:

 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  pinMode(D1, OUTPUT);

  display.setBrightness(0x0a); //set the diplay to maximum brightness
  
  dht.begin();
  
  delay(2000);
  
  Serial.println();

  Serial.print("SINC");
  Serial.println(""); 

while (segundos <=14) {
 while (Serial.available() > 0) {
    char inChar = Serial.read();
    txtMsg += inChar;
  }


 if (txtMsg.length() > 31) {
    contador = 0;
    
 while (contador < 32) {
 if (txtMsg[contador]=66){
    contador = contador +1;
    if (txtMsg[contador]=77){
    PM25 = txtMsg[contador+5]*256 + txtMsg[contador+6];
    PM10 = txtMsg[contador+7]*256 + txtMsg[contador+8];
    break;      
    }
 }
 }
    txtMsg = txtMsgwhite;
    segundos = segundos +1;
    Serial.println (String (segundos));
    display.showNumberDec(segundos);
       
}
}

    segundos = 0;
    PM10seg= 0;
    PM25seg= 0;



// Debug messsages to indicate we're about to connect to the network

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Use the scanNetworks method inside the Wi-Fi class to scan for any available Wi-Fi networks
  // nearby. If none are found, go to sleep
  int n = WiFi.scanNetworks();

  Serial.println("scan done"); 
  if (n == 0)
  {
    Serial.println("no networks found");
    }

  // If networks are found, attempt to connect to our Wi-Fi network
  WiFi.begin(ssid, password);

  // While the connection is not established, IDLE inside this while loop
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // Once the connection to our Wi-Fi netowrk is successful, print some debug messages
  Serial.println("");
  Serial.println("Wi-Fi connected");
  Serial.println();

}

///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// loop


void loop() {

while (segundos < 2) {
 
 while (txtMsg.length() < 32) {

 while (Serial.available() > 0) {
    char inChar = Serial.read();
    txtMsg += inChar;
  }
 }
     
    digitalWrite(D1, HIGH); 
    Serial.println(""); 
    Serial.println ("Trama: " + String(txtMsg[0],DEC)+ "," + String(txtMsg[1],DEC)+ "," + String(txtMsg[2],DEC)+ "," + String(txtMsg[3],DEC)+ "," + String(txtMsg[4],DEC)+ ","
    + String(txtMsg[5],DEC)+ "," + String(txtMsg[6],DEC) + "," + String(txtMsg[7],DEC)+ ";"+ String(txtMsg[8],DEC)+ "," + String(txtMsg[9],DEC)+ ";");

 PM25 = PM25old;
 PM10 = PM10old;
  
  if (txtMsg[0] == 66) {
    if (txtMsg[1] == 77) {
    PM25 = txtMsg[6]*256 + txtMsg[7];
    PM10 = txtMsg[8]*256 + txtMsg[9];
    Serial.println("ok PMhoney"); 
    }
  }
 PM25old = PM25;
 PM10old = PM10;

    Serial.println ("PM 2.5 honey: " + String(PM25) + " ug/m3");
    Serial.println ("PM  10 honey: " + String(PM10) + " ug/m3");
    txtMsg = txtMsgwhite;

    display.showNumberDec(PM25);

    PM25seg = PM25seg + PM25;
    PM10seg = PM10seg + PM10;
    digitalWrite(D1, LOW);
    segundos = segundos +1;

}
/////////////////////////////

    Serial.println (PM25seg);
    Serial.println (PM10seg);
    PM25int = round (PM25seg/2);
    PM10int = round (PM10seg/2);

      
    segundos = 0;
    PM25seg = 0;
    PM10seg = 0;
    PM25segnova = 0;
    PM10segnova = 0;    

    muestra = muestra +1;
    
  Serial.println("");
  Serial.println("Muestra " + String(muestra));

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.println("");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C ");
  Serial.println("");

  Serial.println("Ubidots data:");
  Serial.println ("PM 2.5 30seg HONEY: " + String(PM25int) + " ug/m3");
  Serial.println ("PM 10  30seg HONEY: " + String(PM10int) + " ug/m3");
 
//  ubiSave_value1(String(variable_id1), String(PM25int));
//  ubiSave_value2(String(variable_id2), String(PM10int));
  ubiSave_value2(String(variable_id2), String(PM25int));
  
  
  Serial.println("Disconnecting from Ubidots");
  Serial.println();
}
///
////////////////////////////////////////////////////////////////////////////////
// User-defined functions
// We encapsulate the grunt work for publishing temperature and humidty values to Ubidots
// inside the function ubiSave_value

/*
void ubiSave_value1(String variable_id, String value)
{
  String var = "{\"value\": " + value +"}"; // We'll pass the data in JSON format
  String length = String(var.length());

  if (client.connect("things.ubidots.com", 80))
  {
    Serial.println("Connected");
    Serial.println("Sending to Ubidots PM2.5 HONEY");
    delay(100);

    // Construct the POST request that we'd like to issue
    client.println("POST /api/v1.6/variables/"+variable_id+"/values HTTP/1.1");
    client.println("Content-Type: application/json");
    client.println("Content-Length: "+ length);
    client.println("X-Auth-Token: "+ token);
    client.println("Host: things.ubidots.com\n");
    client.print(var);
  }
  else
  {
    // If we can't establish a connection to the server:
    Serial.println("Ubidots connection failed...");
  }
  while (client.available())
  {
    char c = client.read();
  }
}

//////////////
*/

void ubiSave_value2(String variable_id, String value)
{
  String var = "{\"value\": " + value +"}"; // We'll pass the data in JSON format
  String length = String(var.length());

  if (client.connect("things.ubidots.com", 80))
  {
    Serial.println("Connected");
    Serial.println("Sending to Ubidots PM25 HONEY");
    delay(100);

    // Construct the POST request that we'd like to issue
    client.println("POST /api/v1.6/variables/"+variable_id+"/values HTTP/1.1");
    client.println("Content-Type: application/json");
    client.println("Content-Length: "+ length);
    client.println("X-Auth-Token: "+ token);
    client.println("Host: things.ubidots.com\n");
    client.print(var);
  }
  else
  {
    // If we can't establish a connection to the server:
    Serial.println("Ubidots connection failed...");
  }
  while (client.available())
  {
    char c = client.read();
  }
}
//////////////
//////////////
/*
void ubiSave_value3(String variable_id, String value)
{
  String var = "{\"value\": " + value +"}"; // We'll pass the data in JSON format
  String length = String(var.length());

  if (client.connect("things.ubidots.com", 80))
  {
    Serial.println("Connected");
    Serial.println("Sending to Ubidots PM2.5 NOVA");
    delay(100);

    // Construct the POST request that we'd like to issue
    client.println("POST /api/v1.6/variables/"+variable_id+"/values HTTP/1.1");
    client.println("Content-Type: application/json");
    client.println("Content-Length: "+ length);
    client.println("X-Auth-Token: "+ token);
    client.println("Host: things.ubidots.com\n");
    client.print(var);
  }
  else
  {
    // If we can't establish a connection to the server:
    Serial.println("Ubidots connection failed...");
  }
  while (client.available())
  {
    char c = client.read();
  }
}
//////////////

void ubiSave_value4(String variable_id, String value)
{
  String var = "{\"value\": " + value +"}"; // We'll pass the data in JSON format
  String length = String(var.length());

  if (client.connect("things.ubidots.com", 80))
  {
    Serial.println("Connected");
    Serial.println("Sending to Ubidots PM10 NOVA");
    delay(100);

    // Construct the POST request that we'd like to issue
    client.println("POST /api/v1.6/variables/"+variable_id+"/values HTTP/1.1");
    client.println("Content-Type: application/json");
    client.println("Content-Length: "+ length);
    client.println("X-Auth-Token: "+ token);
    client.println("Host: things.ubidots.com\n");
    client.print(var);
  }
  else
  {
    // If we can't establish a connection to the server:
    Serial.println("Ubidots connection failed...");
  }
  while (client.available())
  {
    char c = client.read();
  }
  if (client.connected())
  {
  //  Serial.println("Disconnecting from Ubidots...");
    client.stop();
  }

}
*/
