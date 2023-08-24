/*
UNAM SPACE - Sistema de Telecomonicaciones
Integrantes: Pablo (líder), Johusa, Alejandra, Eder, Homero

FUNCION DEL CÓDIGO: Controlar el giro y dirección de motores con el uso de un joystick

*/

//LIBRERÍAS PARA EL USO DE LOS NRF24
#include <SPI.h> //Protocolo de comunicacion para comunicarse bidireccionalmente usando relojs y seleccion de Master Slave
#include <RF24.h> //lIBRERIA DE nrf24

//CONFIGURACIÓN PARA TRANSMISIÓN
RF24 radio(9, 10); // Configura los pines CE y CSN
const byte direccion_receptor[6] = "00001"; // Dirección del receptor

//VARIABLES DE LECTURA DE JOYSTICK
const int joystickPinX = A0; // Pin analógico del eje X del joystick
const int joystickPinY = A1; // Pin analógico del eje Y del joystick
const int SW = 2; // Pin digital del SW
int valorX = 0; // Variable para almacenar el valor de X
int valorY = 0; // Variable para almacenar el valor de Y
bool boton = false; // Variable para validar el estado del botón

//Creamos una estructura de datos para transmitir los datos a tarvés del Payload
//Tamaño máximo del Payload = 32 bytes

struct Datos{
  //Variables para motores
  int dato1; //+ 2 bytes,   Almacena el dato del eje X del joystick
  int dato2; //+ 2 bytes,   Almacena el dato del eje Y del joystick
  bool dato3;//+ 1 byte,    ALmacena el dato del boton del joystick
  //           = 5 bytes **LÍMITE DE 32, CUIDAR QUE NO SE EXCEDA **
  };

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(direccion_receptor);
}

void loop() {
  //lECTRA DE VALORES DEL JOYSTICK
  valorX = analogRead(joystickPinX); // Lee el valor del eje X (0-1023)
  valorY = analogRead(joystickPinY); // Lee el valor del eje Y (0-1023)
  boton = digitalRead(SW); // Lee el estados del botón: activado o no activado

  //punto de prueba
  Serial.print("Valor en X: ");
  Serial.println(valorX);
  Serial.print("Valor en Y: ");
  Serial.println(valorY);
  
  Datos datos;
  datos.dato1 = valorX;
  datos.dato2 = valorY;
  datos.dato3 = boton;
  
  // Envía los datos
  radio.write(&datos, sizeof(datos));

  Serial.println("Datos enviados");

  delay(1000); // Espera un segundo antes de enviar los datos nuevamente
}
