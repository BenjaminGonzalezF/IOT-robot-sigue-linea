

#ifndef KnightRoboticsLibs_Iroh_h
#define KnightRoboticsLibs_Iroh_h

void retroceder(int vel);

void retroceder(int velIzq, int velDer);

void avanzar(int vel);

void avanzar(int velIzq, int velDer);

void mover(int velIzq, int velDer);

void detenerse();

void girarDerecha(int vel);

void girarIzquierda(int vel);

void inicializarMovimientoRobot();

void inicializarCabezaRobot();

void inicializarGolpeRobot();

void inicializarSensoresRobot();

void inicializarPantallaRobot();

void apagarCabezaRobot();

void inicializarMovimiento();

void inicializarCabeza();

void inicializarGolpe();

void inicializarSensores();

void inicializarPantalla();

void apagarCabeza();

void moverServoYaw(int pos);

void moverServoPitch(int pos);

void moverServoGolpe(int pos);

int leerBoton();

void botonInicio();

int leerDistanciaSonar();

int leerSensorLineaIzquierdo();

int leerSensorLineaCentral();

int leerSensorLineaDerecho();

int leerSensorObstaculoIzquierdo();

int leerSensorObstaculoDerecho();

void escribirPantalla(int col, int fil, const char Text[]);

void escribirPantalla(int col, int fil, int Number);

void apagarPantalla();

void prenderPantalla();

void borrarPantalla();

void finPrograma();

void pausa(int tiempo);

#endif
