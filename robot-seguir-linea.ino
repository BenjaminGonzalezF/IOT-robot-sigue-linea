#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "direcciones.h"


int velocidad = 60;

int motorIzquierdo1 = 6; 
int motorIzquierdo2 = 5; 
int motorDerecho1 = 3; 
int motorDerecho2 = 11; 

int rightProximityPin = 10;
int leftProximityPin = 2;

int sensorLineaDerecho = A0;
int sensorLineaCentral = A1;
int sensorLineaIzquierdo = A2;

LiquidCrystal_I2C lcd(0x3F, 20, 4);


void inicializarCabezaRobot(){

  Yaw.attach(7);  
  Pitch.attach(8);
  Tilt.attach(9);
  
  moverServoYaw(90);
  moverServoPitch(40);

}

void inicializarMovimientoRobot() {
  pinMode(motorIzquierdo1, OUTPUT);
  pinMode(motorIzquierdo2, OUTPUT);
  pinMode(motorDerecho1, OUTPUT);
  pinMode(motorDerecho2, OUTPUT);

  digitalWrite(motorIzquierdo1, HIGH);
  digitalWrite(motorIzquierdo2, HIGH);
  digitalWrite(motorDerecho1, HIGH);
  digitalWrite(motorDerecho2, HIGH);
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando motores!");
  inicializarMovimientoRobot();
  pinMode(rightProximityPin, INPUT);
  pinMode(leftProximityPin, INPUT);
  Serial.begin(9600);
}

void mostrarPorPantalla(String texto){
  lcd.clear();
  lcd.print(texto);

}

int leerSensorObstaculoIzquierdo() {
  return digitalRead(leftProximityPin);
}

int leerSensorObstaculoDerecho() {
  return digitalRead(rightProximityPin);
}


void girarDerecha(int vel){
  digitalWrite(motorIzquierdo1, HIGH);
  digitalWrite(motorDerecho2, HIGH);
  analogWrite(motorIzquierdo2, velocidad);
  analogWrite(motorDerecho1, velocidad);
}

void girarIzquierda(int vel){
  digitalWrite(motorIzquierdo2, HIGH);
  digitalWrite(motorDerecho1, HIGH);
  analogWrite(motorIzquierdo1, velocidad);
  analogWrite(motorDerecho2, velocidad);

}

void retroceder() {
  digitalWrite(motorIzquierdo1, HIGH);
  digitalWrite(motorDerecho1, HIGH);
  analogWrite(motorIzquierdo2, velocidad);
  analogWrite(motorDerecho2, velocidad);
}

void avanzar() {
  digitalWrite(motorIzquierdo1, LOW);
  digitalWrite(motorDerecho1, LOW);
}

int leerSensorLineaIzquierdo() {
  return analogRead(sensorLineaIzquierdo);
}

int leerSensorLineaCentral() {
  return analogRead(sensorLineaCentral);
}

int leerSensorLineaDerecho() {
  return analogRead(sensorLineaDerecho);
}

void loop() {
  int valorCentral = leerSensorLineaCentral();
  int valorIzquierdo = leerSensorLineaIzquierdo();
  int valorDerecho = leerSensorLineaDerecho();
  
  int umbral = 500;

  if (valorCentral < umbral) {
    avanzar();
  } else {
    if (valorIzquierdo < umbral) {
      girarIzquierda();
    } else if (valorDerecho < umbral) {
      girarDerecha()
    } else {
      retroceder();
    }
  }
}
