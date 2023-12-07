#include "KnightRoboticsLibs_Iroh.h"
#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define distanciaObstaculo 10
#define umbralLinea 500

//Servo Golpe;

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
    avanzar(255);
  } else {
    if (valorIzquierdo < umbralLinea) {
      girarIzquierda(255);
    } else if (valorDerecho < umbralLinea) {
      girarDerecha(255);
    }
  }
}

void comprobarSeguimiento(int DistSonar){
  if (DistSonar > distanciaObstaculo) {
    seguirLinea();
  } 
  else {
    quitarObstaculo();
  }
}

void buscarObstaculos() {
  int DistSonar;

  for (int i = 45; i <= 120; i++) {
    DistSonar = leerDistanciaSonar();
    moverServoYaw(i);
    comprobarSeguimiento(DistSonar);
  }

  for (int i = 120; i > 45; i--) {
    DistSonar = leerDistanciaSonar();
    moverServoYaw(i);
    comprobarSeguimiento(DistSonar);
  }
}

void loop() {
  buscarObstaculos();

}
