#include "KnightRoboticsLibs_Iroh.h"
#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define distanciaObstaculo 10
#define umbralLinea 500

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
  detenerse();
  moverTilt(0);
  delay(500);
  moverTilt(120);
  delay(500);
}

void seguirLinea() {
  int valorCentral = leerSensorLineaCentral();
  int valorIzquierdo = leerSensorLineaIzquierdo();
  int valorDerecho = leerSensorLineaDerecho();

  if (valorCentral < umbralLinea) {
    avanzar();
  } else {
    if (valorIzquierdo < umbralLinea) {
      girarIzquierda();
    } else if (valorDerecho < umbralLinea) {
      girarDerecha();
    }
  }
}

void buscarObstaculos() {
  int DistSonar;

  for (int i = 45; i <= 120; i++) {
    DistSonar = leerDistanciaSonar();

    moverServoYaw(i);

    if (DistSonar > distanciaObstaculo) {
      seguirLinea();
    } else {
      quitarObstaculo();
    }
  }
}

void loop() {
  buscarObstaculos();

}
