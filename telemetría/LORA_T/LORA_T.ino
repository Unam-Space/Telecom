#include "Arduino.h"
#include "LoRa_E220.h"

LoRa_E220 e220ttl(2, 3); // Arduino RX --> e220 TX - Arduino TX --> e220 RX

struct telemetria {
  float dato1;
  float dato2;
  float dato3;
  float dato4;
  float dato5;
  float dato6;
  float dato7;
  float dato8;
  float dato9;
  float dato10;
  float dato11;
  float dato12;
  float dato13;
  float dato14;
  float dato15;
  byte dato16;
  byte dato17;
  byte dato18;
  byte dato19;
};


void setup() {
  Serial.begin(9600);
  delay(500);

  Serial.println("Prueba");
  
  // Startup all pins and UART
  e220ttl.begin();
  // Check If there is some problem of successfully send
}
int i = 0;
void loop() {
  telemetria tele;
  tele.dato1 = 95.12;
  tele.dato2 = 0.25;
  tele.dato3 = -6.25;
  tele.dato4 = 3.25;
  tele.dato5 = -0.25;
  tele.dato6 = 25.36;
  tele.dato7 = 25.3654;
  tele.dato8 = -0.35;
  tele.dato9 = 2.54;
  tele.dato10 = -9.58;
  tele.dato11 = 0.98;
  tele.dato12 = -0.25;
  tele.dato13 = 6.68;
  tele.dato14 = 4.59;
  tele.dato15 = -4.59;
  tele.dato16 = 1;
  tele.dato17 = 4;
  tele.dato18 = 9;
  tele.dato19 = 10;
  //if (Serial.available()) {
  Serial.println(i);
  i++;
  ResponseStatus rs = e220ttl.sendMessage(&tele, sizeof(telemetria));
  Serial.println(rs.getResponseDescription()); // Agregar un pequeño retraso después de enviar el mensaje
  //}
}
