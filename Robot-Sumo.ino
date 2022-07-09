#include <AFMotor.h>
//Pines arduino a utilizar 
AF_DCMotor MotorIz(1);
AF_DCMotor MotorDer(2); 
#define boton 2
#define SensorDelantero A1
int LecturaDelantero = 0;
#define SensorTrasero A0
int LecturaTrasero = 0;

int VelocidadSalRing = 200;
int VelocidadAtaque = 250;
int VelocidadBusqueda = 150;
int TiempoRegresarAlRing = 1000;
int Delantero = 0;
int Trasero = 0;
 
void setup() { 
  // put your setup code here, to run once:
    pinMode(boton,INPUT);
    pinMode(SensorDelantero, INPUT);
    pinMode(SensorTrasero, INPUT);
    MotorIz.setSpeed(VelocidadAtaque);
    MotorDer.setSpeed(VelocidadAtaque);

    Detener(); 

    //Bloque para indicar que fue presionado el boton inicio de la competencia 5 segundos de seguridad
    while (true)
    {
        int pulsado = digitalRead(boton);
        if(pulsado == HIGH){
            delay(5000); //5 segundos de seguridad
            break;
        }
    } 
}

void loop() {
  
    //lECTURA DE LOS SENSORES DE PISO
    LecturaDelantero = digitalRead(SensorDelantero);
    LecturaTrasero = digitalRead(SensorTrasero);

    if(LecturaDelantero == HIGH && LecturaTrasero == HIGH){
        Delantero = 0;
        Trasero = 0;
    }

    if(LecturaDelantero == LOW){
        Delantero = 1;
        Trasero = 0;
    }

    if (LecturaTrasero == LOW)
    {
        Delantero = 0;
        Trasero = 1;
    }

    // DETECTA FINAL DEL RING Sensor Delantero
    if(Delantero == 1){
        Atras(VelocidadSalRing, TiempoRegresarAlRing);
    }

    if (Trasero == 1)
    {
        Adelante(VelocidadSalRing, TiempoRegresarAlRing);
    }
    

}



void Detener(){
    MotorIz.run(RELEASE);
    MotorDer.run(RELEASE); 
}

void Adelante (int vel, int tim){
    MotorDer.setSpeed(vel);
    MotorIz.setSpeed(vel);
    MotorIz.run(FORWARD);
    MotorDer.run(FORWARD);
    delay(tim);
}

void Atras(int vel, int tim){
    MotorDer.setSpeed(vel);
    MotorIz.setSpeed(vel);
    MotorIz.run(BACKWARD);
    MotorDer.run(BACKWARD);
    delay(tim); //Retrocede 3 segundo
}

void GiroIzquierda(){
    MotorIz.run(BACKWARD);
    MotorDer.run(FORWARD);
}

void GiroDerecha(){
    MotorIz.run(FORWARD);
    MotorDer.run(BACKWARD);
}