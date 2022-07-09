#include <Arduino.h>
#line 1 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
#include <AFMotor.h>
//Pines arduino a utilizar
AF_DCMotor MotorIz(1);
AF_DCMotor MotorDer(2); 
#define boton 2
#define SensorDelantero A1
#define SensorTrasero A0
#define Trigger 10
#define Echo 9
// Constantes 
int LecturaDelantero = 0;
int LecturaTrasero = 0;
int VelocidadSalRing = 200;
int VelocidadAtaque = 250;
int VelocidadBusqueda = 150;
int TiempoRegresarAlRing = 1000;
int TiempoAtaque = 100;
int Delantero = 0;
int Trasero = 0;
 
#line 21 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
void setup();
#line 44 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
void loop();
#line 93 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
int Detecta_Oponente();
#line 104 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
void Detener();
#line 109 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
void Adelante(int vel, int tim);
#line 117 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
void Atras(int vel, int tim);
#line 125 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
void GiroIzquierda();
#line 130 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
void GiroDerecha(int vel);
#line 21 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
void setup() { 
  // put your setup code here, to run once:
    pinMode(boton,INPUT);
    pinMode(SensorDelantero, INPUT);
    pinMode(SensorTrasero, INPUT);
    pinMode(Trigger, OUTPUT); //Pin como salida emite sonido ultrasonico 
    pinMode(Echo, INPUT); //Pin como entrada recibe el echo
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
  
    int Distancia_oponente  = Detecta_Oponente(); 

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

    // Si detecta un oponente 
    if(Distancia_oponente <= 20 && Delantero == 0 && Trasero == 0){
        Adelante(VelocidadAtaque, TiempoAtaque);
    }

    // No detectra oponente 
    if(Distancia_oponente >= 21 && Delantero == 0 && Trasero == 0){
        //Estrategia si no detecta oponenete 
        GiroDerecha(VelocidadBusqueda);
    }

    // DETECTA FINAL DEL RING Sensor Delantero Motores giren hacia atras
    if(Delantero == 1){
        Atras(VelocidadSalRing, TiempoRegresarAlRing);
    }

    // DETECTA FINAL DEL RING Sensor Trasero Motores giren hacia delante 
    if (Trasero == 1)
    {
        Adelante(VelocidadSalRing, TiempoRegresarAlRing);
    }
    
}

// Función que detecta la distancia del oponente y devuelve la distancia 
int Detecta_Oponente(){
    int duracion,distancia;
    digitalWrite(Trigger, HIGH); //Genera el pulso de trigger
    delayMicroseconds(10); //Enviamos el pulso durante 10us
    digitalWrite(Trigger, LOW);
    duracion = pulseIn(Echo, HIGH); //Lee el tiempo del ECHO pulsoIn(función para medir los pulsos) pulseIn(pin, value)
    distancia = (duracion/2) / 29; //Calcula la distancia en centimetros
    delay(5);
    return distancia;
}

void Detener(){
    MotorIz.run(RELEASE);
    MotorDer.run(RELEASE); 
}

void Adelante(int vel, int tim){
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

void GiroDerecha(int vel){
    MotorDer.setSpeed(vel);
    MotorIz.setSpeed(vel);
    MotorIz.run(FORWARD);
    MotorDer.run(BACKWARD);
}
