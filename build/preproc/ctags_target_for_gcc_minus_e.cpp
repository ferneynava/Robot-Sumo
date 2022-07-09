# 1 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino"
# 2 "d:\\Material Arduino y Scratch\\Proyectos code Arduino\\Robot sumo\\Robot-Sumo\\Robot-Sumo.ino" 2
//Pines arduino a utilizar 
AF_DCMotor MotorIz(1);
AF_DCMotor MotorDer(2);


int VelocidadAtaque = 255;
int VelocidadBusqueda = 200;

void setup() {
  // put your setup code here, to run once:
    pinMode(2,0x0);
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
  // put your main code here, to run repeatedly:

}

void Detener(){
    MotorIz.run(4);
    MotorDer.run(4);
}

void Adelante (){
    MotorIz.run(1);
    MotorDer.run(1);
}

void Atras(){
    MotorIz.run(2);
    MotorDer.run(2);
}

void GiroIzquierda(){
    MotorIz.run(2);
    MotorDer.run(1);
}

void GiroDerecha(){
    MotorIz.run(1);
    MotorDer.run(2);
}
