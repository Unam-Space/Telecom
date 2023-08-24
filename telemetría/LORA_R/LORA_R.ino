#include "Arduino.h"
#include "LoRa_E220.h"

LoRa_E220 e220ttl(2, 3); // Arduino RX --> e220 TX - Arduino TX --> e220 RX

/*struct Datos {
  short dato1;
  short dato2;
  short dato3;
  short dato4;
  short dato5;
  short dato6;
};*/

struct Telemetria{
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
}; 

void setup() {
  Serial.begin(9600);
  //delay(500);

  Serial.println("Hi, I'm the receiver!");

  // Startup all pins and UART
  e220ttl.begin();
}

void loop() {
    // If something available
    //Datos datos; 
  if (e220ttl.available() > 1) {
    // read the String message
    //ResponseContainer rc = e220ttl.receiveMessage();
    // Is something goes wrong, print error

    ResponseStructContainer rsc = e220ttl.receiveMessage(sizeof(Telemetria));
    if (rsc.status.code != 1) {
      Serial.print("Error: ");
      Serial.println(rsc.status.getResponseDescription());
    } else {
      // Print the data received
      //char data = rc.data[0];
      struct Telemetria datos = *(Telemetria*) rsc.data;
      Serial.print("Dato 1: ");
      Serial.println(datos.dato1);
      Serial.print("Dato 2: ");
      Serial.println(datos.dato2);
      Serial.print("Dato 3: ");
      Serial.println(datos.dato3);
      Serial.print("Dato 4: ");
      Serial.println(datos.dato4);
      Serial.print("Dato 5: ");
      Serial.println(datos.dato5);
      Serial.print("Dato 6: ");
      Serial.println(datos.dato6);
      Serial.print("Dato 7: ");
      Serial.println(datos.dato7);
      Serial.print("Dato 8: ");
      Serial.println(datos.dato8);
      Serial.print("Dato 9: ");
      Serial.println(datos.dato9);
      Serial.print("Dato 10: ");
      Serial.println(datos.dato10);
      Serial.print("Dato 11: ");
      Serial.println(datos.dato11);
      Serial.print("Dato 12: ");
      Serial.println(datos.dato12);
      Serial.print("Dato 13: ");
      Serial.println(datos.dato13);
      Serial.print("Dato 14: ");
      Serial.println(datos.dato14);
      Serial.print("Dato 15: ");
      Serial.println(datos.dato15);
      Serial.print("Dato 16: ");
      Serial.println(datos.dato16);
      Serial.print("Dato 17: ");
      Serial.println(datos.dato17);
      Serial.print("Dato 18: ");
      Serial.println(datos.dato18);
    
      rsc.close();
    }
  }else{
    //Serial.println("Ningún LORA disponible");
    //delay(1000);
  }

}
