#include "KnightRoboticsLibs_Iroh.h"
#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define distanciaObstaculo 10
#define umbralLinea 150
#define velocidad 136
#define tiempoMoverse 0

void setup() {
  Serial.begin(9600);

  inicializarMovimientoRobot();
  //inicializarPantallaRobot();
  inicializarCabezaRobot();
  inicializarGolpeRobot();
  inicializarSensores();
  // Se endereza
  moverServoPitch(10);
}

void quitarObstaculo() {
  //escribirPantalla(1, 1, "Quito obstaculo");
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
  if()
  if(valorIzquierdo > umbralLinea && valorDerecho > umbralLinea ){
    avanzar(velocidad);
    //escribirPantalla(1, 1, "Avanzando");
    delay(tiempoMoverse);
  }else if (valorIzquierdo < umbralLinea) {
    girarIzquierda(velocidad);
    //escribirPantalla(1, 1, "Izquierda");
    delay(tiempoMoverse);
  } else if (valorDerecho < umbralLinea) {
    girarDerecha(velocidad);
    //escribirPantalla(1, 1, "Derecha");
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

/*   for (int i = 45; i <= 120; i++) {
    DistSonar = leerDistanciaSonar();
    Serial.println(DistSonar);
    //mostrarPantallaDist(DistSonar);
    moverServoYaw(i); */
    comprobarSeguimiento(DistSonar);
/*   }

  for (int i = 120; i > 45; i--) {
    DistSonar = leerDistanciaSonar();
    Serial.println(DistSonar);
    //mostrarPantallaDist(DistSonar);
    moverServoYaw(i);
    comprobarSeguimiento(DistSonar);
  } */
}

void loop() {
  buscarObstaculos();



}
