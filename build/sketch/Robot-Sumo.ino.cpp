#include <Arduino.h>
#line 1 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
#include <AFMotor.h>
//Pines arduino a utilizar 
AF_DCMotor MotorIz(1);
AF_DCMotor MotorDer(2); 
#define boton 2

int VelocidadAtaque = 255;
int VelocidadBusqueda = 200;
 
#line 10 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
void setup();
#line 29 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
void loop();
#line 34 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
void DetenerMot();
#line 10 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
void setup() { 
  // put your setup code here, to run once:
    pinMode(boton,INPUT);
    MotorIz.setSpeed(VelocidadAtaque);
    MotorDer.setSpeed(VelocidadAtaque);

    DetenerMot(); 

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

void DetenerMot(){
    MotorIz.run(RELEASE);
    MotorDer.run(RELEASE); 
}

