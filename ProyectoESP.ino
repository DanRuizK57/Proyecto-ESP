#define BLYNK_TEMPLATE_ID "TMPL2Dpc1MpJb"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "74ay2OfFVVwx4l8ZEym6yyPVut0Qeo6H"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <math.h>
#include <stdio.h>

// WiFi credentials
char ssid[] = "LoremIpsum";
char pass[] = "woim9701";

BlynkTimer timer;

int val_x = 0, val_y = 0, val_z = 0;
double b;
const int portX = 34;
const int portZ = 35;
const int portY = 32;

// Esta función se ejecuta periódicamente para enviar datos a Blynk
void sendAccelDataToBlynk() {
  // Inicializar valores a cero antes de la suma
  val_x = 0;
  val_y = 0;
  val_z = 0;
  
  // Acumular valores analógicos
  for (int i = 0; i < 10; i++) {
    val_x += analogRead(portX);
    val_y += analogRead(portY);
    val_z += analogRead(portZ);
  }

  // Calcular el promedio de las lecturas
  val_x = val_x / 10;
  val_y = val_y / 10;
  val_z = val_z / 10;

  // Cálculo del ángulo
  b = (double)(abs(val_x - 320)) / (abs(val_z - 320));
  float a = atan(b) / 3.14 * 180;

  Serial.print("X: ");
  Serial.print(val_x);
  Serial.print(" Y: ");
  Serial.print(val_y);
  Serial.print(" Z: ");
  Serial.println(val_z);

  // Enviar los datos a Blynk en pines virtuales
  Blynk.virtualWrite(V0, val_x);
  Blynk.virtualWrite(V1, val_y);
  Blynk.virtualWrite(V2, val_z);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Llamar a la función sendAccelDataToBlynk cada segundo
  timer.setInterval(1000L, sendAccelDataToBlynk);
}

void loop() {
  Blynk.run();
  timer.run();
}