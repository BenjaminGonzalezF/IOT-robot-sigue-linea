#include "KnightRoboticsLibs_Iroh.h"
#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define distanciaObstaculo 10
#define umbralLinea 150
#define velocidad 70

void setup() {
  Serial.begin(9600);

  inicializarMovimientoRobot();
  inicializarPantallaRobot();
  inicializarCabezaRobot();
  inicializarGolpeRobot();
  inicializarSensores();
  inicializarPantalla();

  // Se endereza
  moverServoPitch(0);
}

void quitarObstaculo() {
  moverServoGolpe(-1); // Mueve a la izquierda
  delay(250);          
  moverServoGolpe(0);  // Centra el servo
  delay(250);          
  moverServoGolpe(1);  // Mueve a la derecha
  delay(250);
}

void seguirLinea() {
  int valorCentral = leerSensorLineaCentral();
  int valorIzquierdo = leerSensorLineaIzquierdo();
  int valorDerecho = leerSensorLineaDerecho();

  if (valorCentral < umbralLinea) {
    avanzar(velocidad);
  } 

  if (valorIzquierdo < umbralLinea) {
    girarIzquierda(velocidad);
    delay(10);

  } else if (valorDerecho < umbralLinea) {
    girarDerecha(velocidad);
    delay(10);
    }
  }


void comprobarSeguimiento(int DistSonar){
  if (DistSonar > distanciaObstaculo) {
    seguirLinea();
  } 
  else {
    if (DistSonar !=0){
      quitarObstaculo();
    }
  }
}

void buscarObstaculos() {
  
  int DistSonar;

  for (int i = 45; i <= 120; i++) {
    DistSonar = leerDistanciaSonar();
    Serial.println(DistSonar);
    mostrarPantallaDist(DistSonar);
    moverServoYaw(i);
    comprobarSeguimiento(DistSonar);
  }

  for (int i = 120; i > 45; i--) {
    DistSonar = leerDistanciaSonar();
    Serial.println(DistSonar);
    mostrarPantallaDist(DistSonar);
    moverServoYaw(i);
    comprobarSeguimiento(DistSonar);
  }
}
void mostrarPantallaDist(int DistSonar){
    // IMPRIMIR RESULTADO POR SERIAL
  
  Serial.print("SONAR =" );    
  Serial.print(DistSonar);
  Serial.print("\t");
  
  // MOSTRAR INFORMACION EN PANTALLA LCD
  if (DistSonar>99){
      escribirPantalla(6, 1, DistSonar);
  }
  else if (DistSonar<=99 && DistSonar>=10){
    
      escribirPantalla(6, 1, 0);
      escribirPantalla(7, 1, DistSonar);
  }
  else{
      escribirPantalla(6, 1, "00");
      escribirPantalla(8, 1, DistSonar);
  }
  
  // Espera 
  delay(100);    
}
void loop() {
  buscarObstaculos();
}
