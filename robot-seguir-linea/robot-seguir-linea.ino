#include "KnightRoboticsLibs_Iroh.h"
#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define distanciaObstaculo 12
#define umbralLinea 150
#define velocidad 30
#define tiempoMoverse 3

void setup() {
  Serial.begin(9600);

  inicializarMovimientoRobot();
  inicializarPantallaRobot();
  inicializarCabezaRobot();
  inicializarGolpeRobot();
  inicializarSensores();
  // Se endereza
  moverServoPitch(10);
  delay(5000);
}

void quitarObstaculo() {
  borrarPantalla();
  escribirPantalla(0, 0, "Quito obstaculo");
  detenerse();
  moverServoGolpe(-1); // Mueve a la izquierda
  delay(250);          
  moverServoGolpe(0);  // Centra el servo
  delay(250);          
  moverServoGolpe(1);  // Mueve a la derecha
  delay(250);
}

boolean detecIzquierdo(int valorIzquierdo){
  if(valorIzquierdo < umbralLinea){
    return true;
  }
  return false;
}

boolean detecDerecho(int valorDerecho){
  if(valorDerecho < umbralLinea){
    return true;
  }
  return false;
}




void seguirLinea() {
  int valorCentral = leerSensorLineaCentral();
  int valorIzquierdo = leerSensorLineaIzquierdo();
  int valorDerecho = leerSensorLineaDerecho();

  if (valorIzquierdo < umbralLinea && valorDerecho < umbralLinea){
    avanzar(velocidad);
    return;
  }

  if(valorIzquierdo > umbralLinea && valorDerecho > umbralLinea ){
    avanzar(velocidad);
    borrarPantalla();
    escribirPantalla(0, 0, "Avanzando");
    delay(tiempoMoverse);
  }else if (valorIzquierdo < umbralLinea) {
    girarIzquierda(velocidad);
    borrarPantalla();
    escribirPantalla(0, 0, "Izquierda");
    delay(tiempoMoverse);
  } else if (valorDerecho < umbralLinea) {
    girarDerecha(velocidad);
    borrarPantalla();
    escribirPantalla(0, 0, "Derecha");
    delay(tiempoMoverse);
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
  DistSonar = leerDistanciaSonar();

 for (int i = 60; i <= 105; i++) {
    DistSonar = leerDistanciaSonar();
    Serial.println(DistSonar);
    moverServoYaw(i);
    comprobarSeguimiento(DistSonar);
  }

  for (int i = 105; i > 60; i--) {
    DistSonar = leerDistanciaSonar();
    Serial.println(DistSonar);
    moverServoYaw(i);
    comprobarSeguimiento(DistSonar);
  } 
}

void loop() {
  buscarObstaculos();
}
