/*
  Reading PM25 from the PMSx003 sensor.
  By: Daniel Bernal
  Date: August 23, 2021
  Hardware Connections:
  Please see the instructions in github (https://github.com/danielbernalb/LibrePM25) or aireciudadano (https://aireciudadano.com/guia-de-construccion-medidor-librepm25/)
  Library used: https://github.com/fu-hsi/PMS

  Leyendo PM25 desde el sensor PMSx003.
  Por: Daniel Bernal
  Fecha: Agosto 23, 2021
  Conección de Hardware:
  Favor revisar las instrucciones en github (https://github.com/danielbernalb/LibrePM25) o aireciudadano (https://aireciudadano.com/guia-de-construccion-medidor-librepm25/)
  Libraria usada: https://github.com/fu-hsi/PMS
  Rev 007
*/

// ***************************************************************************
// ***************************************************************************

#include <SoftwareSerial.h>
#include <TimerOne.h>
#include <MultiFuncShield.h>
#include "PMS.h"

#define PMS_TX 5 // PMS TX pin
#define PMS_RX 3 // PMS RX pin
#define LED4 10

#define RevVersion 1 // Firmware version 26 oct 2023

SoftwareSerial pmsSerial(PMS_TX, PMS_RX);

PMS pms(pmsSerial);
PMS::DATA data;

int PM25_value = 0;
int PM25_value_ori = 0;
boolean toggle = false;

void setup()
{
  Timer1.initialize();
  MFS.initialize(&Timer1); // initialize multi-function shield library
  Serial.begin(115200);

  pinMode(LED4, OUTPUT);

  Serial.print(F("Firmware version: "));
  Serial.println(RevVersion);

  MFS.write("Pm25");
  Serial.println(F("Start LibrePM25 sensor"));

  pmsSerial.begin(9600); // Software serial begin for PMS sensor
  delay(100);

  if (pms.readUntil(data))
    Serial.println(F("Test Plantower sensor found!"));
  else
    Serial.println(F("Could not find Plantower sensor!"));
}

void loop()
{
  if (pms.readUntil(data))
  {
    PM25_value_ori = data.PM_AE_UG_2_5;
    PM25_value = ((630 * PM25_value_ori) / 1000) + 1.56; // Ajuste resultado de comparaciones con 4 estaciones método referencia en Bogotá y 1 Lima
    Serial.print(F("PMS PM2.5: "));
    Serial.print(PM25_value);
    Serial.println(F(" ug/m3"));
    MFS.write(PM25_value);
    toggle = !toggle;
    digitalWrite(LED4, toggle);
  }
  else
    Serial.println(F("No data by Plantower sensor!"));
  delay(1000);
}
