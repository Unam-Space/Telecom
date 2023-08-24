/*
UNAM SPACE - Sistema de Telecomonicaciones
Integrantes: Pablo (líder), Johusa, Alejandra, Eder, Homero
FUNCION DEL CÓDIGO: Recibir datos con los NRF24 usando un payload completo
*/

//________________________________________________________________________________________________________________________
//LIBRERIAS PARA EL USO DEL NRF24
#include <SPI.h> //Protocolo de comunicacion para comunicarse bidireccionalmente usando relojs y seleccion de Master Slave
#include <RF24.h> //lIBRERIA DE nrf24

//CONFIGURACIÓN PARA RECEPCIÓN
RF24 radio(9, 10); // Configura los pines CE y CSN
const byte direccion_transmisor[6] = "00001"; // Dirección del receptor
//________________________________________________________________________________________________________________________

//VARIABLES PARA LOS VALORES LEÍDOS EN EL JOYSTICK
int valorX = 0; // Variable para almacenar el valor de X
int valorY = 0; // Variable para almacenar el valor de Y
bool boton = false; // Variable para validar el estado del botón

//PINES PWN
int RPWM_I = 5;
int LPWM_I = 6;
//int RPWM_D = 5;
//int LPWM_D= 6;

/*
//VARIABLES PARA PUENTE H y Motores
int MotorIzquierdoAdelante  = 3; //pin Digital
int MotorIzquierdoAtras     = 4; //pin Digital
int MotorDerechoAdelante    = 7; //pin Digital
int MotorDerechoAtras       = 8; //pin Digital
int pinVelocidadDerecha     = 6; //pin PWM
int pinVelocidadIzquierda   = 5; //pin PWM
int velocidad = 125;//velocidad motores(0-255)
*/
//________________________________________________________________________________________________________________________

//Creamos una estructura de datos para transmitir los datos a tarvés del Payload
//Tamaño máximo del Payload = 32 bytes
struct Datos{
  int dato1;
  int dato2;
  bool dato3;
  };

int i = 0; //CONTADOR DE INTERACCIONES

//------------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  //activar señales del puente h
  /*
  pinMode(MotorIzquierdoAdelante,OUTPUT);
  pinMode(MotorDerechoAdelante,OUTPUT);
  pinMode(MotorIzquierdoAtras,OUTPUT);
  pinMode(MotorDerechoAtras,OUTPUT);
  */

  pinMode(RPWM_I,OUTPUT);
  pinMode(LPWM_I,OUTPUT);
  //pinMode(RPWM_D,OUTPUT);
  //pinMode(LPWM_D,OUTPUT);
  
  Serial.println("Esta es una prueba para el control del puente H");
  radio.begin();
  radio.openReadingPipe(1, direccion_transmisor);
  radio.startListening();
}

//------------------------------------------------------------------------------------------------------------------------
void loop() {
  if (radio.available()) {
    Datos datos;
    // Lee los datos recibidos
    radio.read(&datos, sizeof(datos));
    //Extraemos los valores de la estructura y los asignamos a cada variable reservada
    valorX = datos.dato1;
    valorY = datos.dato2;
    boton = datos.dato3;

    //Punto de Prueba 1
    Serial.print("Valor en X: ");
    Serial.println(valorX);
    Serial.print("Valor en Y: ");
    Serial.println(valorY);

    // Mapea los valores leídos  para acomodarlos en el intervalo [-100, 100]
    float mappedX = map(valorX, 0, 1023, -100, 100);
    float mappedY = map(valorY, 0, 1023, 100, -100);

    //Punto de Prueba 2
    Serial.print("Valor en X mapeado: ");
    Serial.println(mappedX);
    Serial.print("Valor en Y mapeado: ");
    Serial.println(mappedY);

    // Calcula el ángulo utilizando la función atan2()
    float ang = atan2(mappedY, mappedX) * (180.0 / PI); // Convierte el ángulo a grados
    float magnitud = sqrt(pow(mappedY,2)+pow(mappedX,2));

    //Punto de Prueba 3
    Serial.print("Valor del angulo: ");
    Serial.println(ang);
    Serial.print("Valor de la magnitud: ");
    Serial.println(magnitud);
    
    // Envía las coordenadas del joystick en el formato [a, b]

    /*
    Serial.print("La úbicación del Joystick es: [");
    Serial.print(mappedX);
    Serial.print(",");
    Serial.print(mappedY);
    Serial.println("]");
    Serial.print("El ánngulo del Joystick es: ");
    Serial.println(ang);
    Serial.print("La magnitud del vector es: ");
    Serial.println(magnitud);
    Serial.print("El estado del botón es: ");
    Serial.println(boton);
    Serial.println("----------------");
    //delay(1000);
    */

    if(mappedX > 0 && mappedX < 31 && mappedY > -30 && mappedY < 0){
      carroDetenido();
    }else if(mappedX > 0 && mappedY > 1){
      carroAvanzaAdelante();
    }else if(mappedX > 0 && mappedY < -30){
      carroAvanzaAtras();
    }


    /*
    if (ang == 0 && mappedX == 1 && mappedY == 0) {
      carroDetenido();
    } else if (ang == 0 && mappedX == 100 && mappedY == 0) {
      carroGiraDerecha();
    } else if (ang > 0 && mappedX == -100 && mappedY == 0) {
      carroGiraIzquierda();
    } else if (ang > 0 && ang < 180) {
      carroAvanzaAdelante();
    } else if (ang < 0) {
      carroAvanzaAtras();
    }
    */

    /*
    Serial.print("Interacción #");
    Serial.println(i);
    Serial.print("Valor en X: ");
    Serial.println(valorX);
    Serial.print("Valor en Y: ");
    Serial.println(valorY);
    Serial.print("Valor Botón: ");
    Serial.println(boton);
    i = i + 1;
    */
  } 
}

//--------------- FUNCIONES PARA EL CONTROL DE MOTORESV ---------------------------------------

void carroAvanzaAdelante(){

    Serial.println("Avanzando hacia adelante");
    analogWrite(RPWM_I, 127);
    analogWrite(LPWM_I, 0);
    //analogWrite(RPWM_D, 127);
    //analogWrite(LPWM_D, 0);
    
    /*
    Serial.println("avanzando hacia adelante");
    digitalWrite(MotorDerechoAdelante,HIGH);
    digitalWrite(MotorIzquierdoAdelante,HIGH);
    digitalWrite(MotorDerechoAtras,LOW);
    digitalWrite(MotorIzquierdoAtras,LOW);
    //delay(1000);
    */
  }
  
void carroAvanzaAtras(){

    Serial.println("Avanzando hacia atrás");
    analogWrite(RPWM_I, 0);
    analogWrite(LPWM_I, 127);
    //analogWrite(RPWM_D, 0);
    //analogWrite(LPWM_D, 127);
    
    /*
    Serial.println("avanzando hacia atras");
    digitalWrite(MotorDerechoAdelante,LOW);
    digitalWrite(MotorIzquierdoAdelante,LOW);
    digitalWrite(MotorDerechoAtras,HIGH);
    digitalWrite(MotorIzquierdoAtras,HIGH);
    //delay(1000);
    */
  }

void carroDetenido(){
  
    Serial.println("Rover Detenido");
    analogWrite(RPWM_I, 0);
    analogWrite(LPWM_I, 0);
    //analogWrite(RPWM_D, 0);
    //analogWrite(LPWM_D, 0);
  }
  
/*   
void carroGiraDerecha(){
    Serial.println("girando a la derecha");
    digitalWrite(MotorDerechoAdelante,LOW);
    digitalWrite(MotorIzquierdoAdelante,HIGH);
    digitalWrite(MotorDerechoAtras,HIGH);
    digitalWrite(MotorIzquierdoAtras,LOW);
    digitalWrite(13,HIGH);
  }
  
 
void carroGiraIzquierda(){
    Serial.println("girando a la izquierda");
    digitalWrite(MotorDerechoAdelante,HIGH);
    digitalWrite(MotorIzquierdoAdelante,LOW);
    digitalWrite(MotorDerechoAtras,LOW);
    digitalWrite(MotorIzquierdoAtras,HIGH);
    digitalWrite(13,LOW);
  }
  
void carroDetenido(){
    Serial.println("automovil detenido");
    digitalWrite(MotorDerechoAdelante,LOW);
    digitalWrite(MotorIzquierdoAdelante,LOW);
    digitalWrite(MotorDerechoAtras,LOW);
    digitalWrite(MotorIzquierdoAtras,LOW);
  }


void pruebaMotores(){
    Serial.println("automovil detenido");
    digitalWrite(MotorDerechoAdelante,HIGH);
    digitalWrite(MotorIzquierdoAdelante,LOW);
    digitalWrite(MotorDerechoAtras,HIGH);
    digitalWrite(MotorIzquierdoAtras,LOW);
    delay(200);
    velocidad = velocidad+1;
    if (velocidad == 250){
      velocidad = 0;
      }
  }*/
