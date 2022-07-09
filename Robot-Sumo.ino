#include <AFMotor.h>
//Pines arduino a utilizar 
AF_DCMotor MotorIz(1);
AF_DCMotor MotorDer(2); 
#define boton 2

int VelocidadAtaque = 255;
int VelocidadBusqueda = 200;
 
void setup() { 
  // put your setup code here, to run once:
    pinMode(boton,INPUT);
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
  // put your main code here, to run repeatedly:

}

void Detener(){
    MotorIz.run(RELEASE);
    MotorDer.run(RELEASE); 
}

void Adelante (){
    MotorIz.run(FORWARD);
    MotorDer.run(FORWARD);
}

void Atras(){
    MotorIz.run(BACKWARD);
    MotorDer.run(BACKWARD);
}

void GiroIzquierda(){
    MotorIz.run(BACKWARD);
    MotorDer.run(FORWARD);
}

void GiroDerecha(){
    MotorIz.run(FORWARD);
    MotorDer.run(BACKWARD);
}