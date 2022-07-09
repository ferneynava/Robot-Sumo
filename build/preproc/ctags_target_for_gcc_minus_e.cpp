# 1 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
# 2 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino" 2
//Pines arduino a utilizar
AF_DCMotor MotorIz(1);
AF_DCMotor MotorDer(2);





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

void setup() {
  // put your setup code here, to run once:
    pinMode(2,0x0);
    pinMode(A1, 0x0);
    pinMode(A0, 0x0);
    pinMode(10, 0x1); //Pin como salida emite sonido ultrasonico 
    pinMode(9, 0x0); //Pin como entrada recibe el echo
    MotorIz.setSpeed(VelocidadAtaque);
    MotorDer.setSpeed(VelocidadAtaque);

    Detener();

    //Bloque para indicar que fue presionado el boton inicio de la competencia 5 segundos de seguridad
    while (true)
    {
        int pulsado = digitalRead(2);
        if(pulsado == 0x1){
            delay(5000); //5 segundos de seguridad
            break;
        }
    }
}

void loop() {

    int Distancia_oponente = Detecta_Oponente();

    //lECTURA DE LOS SENSORES DE PISO
    LecturaDelantero = digitalRead(A1);
    LecturaTrasero = digitalRead(A0);

    if(LecturaDelantero == 0x1 && LecturaTrasero == 0x1){
        Delantero = 0;
        Trasero = 0;
    }

    if(LecturaDelantero == 0x0){
        Delantero = 1;
        Trasero = 0;
    }

    if (LecturaTrasero == 0x0)
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
    digitalWrite(10, 0x1); //Genera el pulso de trigger
    delayMicroseconds(10); //Enviamos el pulso durante 10us
    digitalWrite(10, 0x0);
    duracion = pulseIn(9, 0x1); //Lee el tiempo del ECHO pulsoIn(función para medir los pulsos) pulseIn(pin, value)
    distancia = (duracion/2) / 29; //Calcula la distancia en centimetros
    delay(5);
    return distancia;
}

void Detener(){
    MotorIz.run(4);
    MotorDer.run(4);
}

void Adelante(int vel, int tim){
    MotorDer.setSpeed(vel);
    MotorIz.setSpeed(vel);
    MotorIz.run(1);
    MotorDer.run(1);
    delay(tim);
}

void Atras(int vel, int tim){
    MotorDer.setSpeed(vel);
    MotorIz.setSpeed(vel);
    MotorIz.run(2);
    MotorDer.run(2);
    delay(tim); //Retrocede 3 segundo
}

void GiroIzquierda(){
    MotorIz.run(2);
    MotorDer.run(1);
}

void GiroDerecha(int vel){
    MotorDer.setSpeed(vel);
    MotorIz.setSpeed(vel);
    MotorIz.run(1);
    MotorDer.run(2);
}
