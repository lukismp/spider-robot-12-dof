
///////////////////////////////
//con servo.h
#include <Servo.h>
Servo myservo;
///////////////////////////////


///////////////////////////////
//con maestro.h
#include <PololuMaestro.h>

#ifdef SERIAL_PORT_HARDWARE_OPEN
#define maestroSerial SERIAL_PORT_HARDWARE_OPEN
#else
#include <SoftwareSerial.h>
SoftwareSerial maestroSerial(10, 11);
#endif
MicroMaestro maestro(maestroSerial);

SoftwareSerial bluetooth(5,6);
///////////////////////////////

#include "Pata.h"

//orden patas: empieza delantera derecha y aumenta en sentido agujas reloj
Pata pata1(0, 1, 2);
Pata pata2(3, 4, 5);
Pata pata3(6, 7, 8);
Pata pata4(9, 10, 11);


///////////////////////////////


const int speed = 50;
const int acceleration = 100;

bool primero = true;

char orden = 'n';
char ordenCurso = ' ';

///////////////////////////////

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  //setupServo();

  maestroSerial.begin(9600);

  bluetooth.begin(9600);

  setupPatas();

  delay(500);

}

void loop() {
  Serial.println(orden);
  int del = 2000;
//  if(bluetooth.available()){
//    String data = bluetooth.readString();
//    Serial.println("blue " + data);
//    bluetooth.println("recibido");
//  }

    while (bluetooth.available()) {
    //orden = Serial.read();
    String data = bluetooth.readString();
    Serial.println("blue " + data);
    //data.toCharArray(orden, 5);
    orden = data[0];
    Serial.println(orden);
    bluetooth.println("recibido: "+ orden);

    //      orden = data.trim();

  }
  
  while (Serial.available()) {
    //orden = Serial.read();
    String data = Serial.readString();
    Serial.println("leido " + data);
    //data.toCharArray(orden, 5);
    orden = data[0];
    Serial.println(orden);

    //      orden = data.trim();

  }
  switch (orden) {
    case 'a':
    case 'A':
      if ((ordenCurso == 'b') || (ordenCurso == 'B')) {
        levantar();
        delay(100);
      }
      avanzar();
      break;

    case 'd':
    case 'D':
      if ((ordenCurso == 'b') || (ordenCurso == 'B')) {
        levantar();
        delay(100);
      }
      girarDerecha();
      break;
    case 'i':
    case 'I':
      if ((ordenCurso == 'b') || (ordenCurso == 'B')) {
        delay(100);
        levantar();
      }
      girarIzquierda();
      break;

    case 'l':
    case 'L':
      levantar();
      break;

    case 'b':
    case 'B':
      if ((ordenCurso != 'b') && (ordenCurso != 'B')) {
        bajar();
      } else {
        delay(200);
      }
      break;

    case 'r':
    case 'R':
      if ((ordenCurso != 'r') && (ordenCurso != 'R')) {
        if ((ordenCurso == 'b') || (ordenCurso == 'B')) {
          delay(100);
          levantar();
        }
        reverencia();
       } else {
        delay(200);
      }
      break;

      case 'p':
    case 'P':
      if ((ordenCurso != 'p') && (ordenCurso != 'P')) {
        if ((ordenCurso == 'b') || (ordenCurso == 'B')) {
          delay(100);
          levantar();
        }
        aullar();
       } else {
        delay(200);
      }
      break;

    case 's':
    case 'S':
      if ((ordenCurso == 'b') || (ordenCurso == 'B')) {
        levantar();
        delay(100);
      }
      retroceder();
      break;

      case 'h':
    case 'H':
    if ((ordenCurso != 'h')  && (ordenCurso != 'H')) {
      saludar();
      ordenCurso = 'n';
      orden = 'n';
    } else {
      delay(200);
    }
      break;

    default:
      delay(200);
      break;
  }

  ordenCurso = orden;

  //avanzar();
  //delay(del);

  //girarDerecha();

  //girarIzquierda();

  //  bajar();
  //  delay(del);
  //  levantar();
  //
  //  //posicionInicial();
  //  delay(del);

}


/**
   Inicializa los valores de las clases pata
*/

void setupPatas() {

  pata1.setOffset(-350, 0, 150);
  pata2.setOffset(250, 0, 0);
  pata3.setOffset(150, -350, 100);
  pata4.setOffset(-300, 300, -350);

  pata1.setInversionMotores(1, -1, -1);
  pata2.setInversionMotores(-1, 1, 1);
  pata3.setInversionMotores(1, -1, -1);
  pata4.setInversionMotores(-1, 1, 1);

  // setTarget takes the channel number you want to control, and the target position in units of 1/4 microseconds.
  //   A typical RC hobby servo responds to pulses between 1 ms (4000) and 2 ms (8000).

  // setSpeed takes channel number you want to limit and the speed limit in units of (1/4 microseconds)/(10 milliseconds).
  // A speed of 0 makes the speed unlimited, so that setting the target will immediately affect the position. Note that the
  //actual speed at which your servo moves is also limited by the design of the servo itself, the supply voltage, and mechanical loads.

  //  setAcceleration takes channel number you want to limit and the acceleration limit value from 0 to 255 in units of (1/4 microseconds)/(10 milliseconds) / (80 milliseconds).
  //  A value of 0 corresponds to no acceleration limit. An acceleration limit causes the speed of a servo to slowly ramp up until it reaches the maximum speed,
  //  then to ramp down again as the position approaches the target, resulting in relatively smooth motion from one point to another.

  pata1.setupPata(speed, acceleration);
  pata2.setupPata(speed, acceleration);
  pata3.setupPata(speed, acceleration);
  pata4.setupPata(speed, acceleration);
  delay(500);
  levantar();
  delay(1000);

}

void levantar() {
  int del = 2000;
  pata1.moverMotor(1, pata1.inicialM1);
  pata2.moverMotor(1, pata2.inicialM1);
  pata3.moverMotor(1, pata3.inicialM1);
  pata4.moverMotor(1, pata4.inicialM1);
  delay(del);
  pata1.moverMotor(2, pata1.inicialM2);
  pata2.moverMotor(2, pata2.inicialM2);
  pata3.moverMotor(2, pata3.inicialM2);
  pata4.moverMotor(2, pata4.inicialM2);
  //delay(del);
  pata1.moverMotor(3, pata1.inicialM3);
  pata2.moverMotor(3, pata2.inicialM3);
  pata3.moverMotor(3, pata3.inicialM3);
  pata4.moverMotor(3, pata4.inicialM3);
}

void bajar() {
  int del = 500;
  pata1.moverPata(0, pata1.inicialM2, pata1.inicialM3);
  delay(del);
  pata3.moverPata(0, pata3.inicialM2, pata3.inicialM3);
  delay(del);
  pata2.moverPata(0, pata2.inicialM2, pata2.inicialM3);
  delay(del);

  pata4.moverPata(0, pata4.inicialM2, pata4.inicialM3);
  delay(del);
  pata1.moverMotor(2, 0);
  pata2.moverMotor(2, 0);
  pata3.moverMotor(2, 0);
  pata4.moverMotor(2, 0);
  //delay(del);
  pata1.moverMotor(3, 90);
  pata2.moverMotor(3, 90);
  pata3.moverMotor(3, 90);
  pata4.moverMotor(3, 90);
  delay(del);
}


/**
   Movimientos para avanzar
*/
void avanzar() {
  int del = 300;

  if (primero) {
    paso1();
    primero = false;
    delay(del);
  }
  paso2();
  delay(del);
  paso3();
  delay(del);
  paso4();
  delay(del);
  paso5();
  delay(del);
  paso6();
  delay(del);
  paso7();
  delay(del);
}

/**
   Movimientos para avanzar
*/
void retroceder() {
  int del = 300;

  if (primero) {
    pasoAtras1();
    primero = false;
    delay(del);
  }
  pasoAtras2();
  delay(del);
  pasoAtras3();
  delay(del);
  pasoAtras4();
  delay(del);
  pasoAtras5();
  delay(del);
  pasoAtras6();
  delay(del);
  pasoAtras7();
  delay(del);
}


void girarDerecha() {
  int del1 = 300;
  int del2 = 10;


  pata1.moverPata(-20, pata1.inicialM2, pata1.inicialM3);
  delay(del1);
  pata2.moverPata(60, pata2.inicialM2, pata2.inicialM3);
  delay(del1);
  pata3.moverPata(-20, pata3.inicialM2, pata3.inicialM3);
  delay(del1);
  pata4.moverPata(60, pata4.inicialM2, pata4.inicialM3);
  delay(del1);

  pata1.empujarPata(pata1.inicialM1, pata1.inicialM2, pata1.inicialM3);
  pata2.empujarPata(pata2.inicialM1, pata2.inicialM2, pata2.inicialM3);
  pata3.empujarPata(pata1.inicialM1, pata1.inicialM2, pata1.inicialM3);
  pata4.empujarPata(pata4.inicialM1, pata4.inicialM2, pata4.inicialM3);
  delay(del1);

  //  pata2.moverPata(60, 40, 30);
  //  pata4.moverPata(60, 40, 30);
  //  delay(del2);
  //  pata1.empujarPata(60, pata1.inicialM2, pata1.inicialM3);
  //  pata3.empujarPata(60, pata1.inicialM2, pata1.inicialM3);
  //
  //  pata2.moverPata(60, pata2.inicialM2, pata2.inicialM3);
  //  pata4.moverPata(60, pata4.inicialM2, pata4.inicialM3);
  //
  //  delay(del1);
  //
  //  pata1.moverPata(pata1.inicialM1, 40, 30);
  //  pata3.moverPata(pata3.inicialM3, 40, 30);
  //  delay(del2);
  //  pata2.empujarPata(pata2.inicialM1, pata2.inicialM2, pata2.inicialM3);
  //  pata4.empujarPata(pata4.inicialM1, pata4.inicialM2, pata4.inicialM3);
  //
  //  pata1.moverPata(pata1.inicialM1, pata1.inicialM2, pata1.inicialM3);
  //  pata3.moverPata(pata1.inicialM1, pata1.inicialM2, pata1.inicialM3);
}

void girarIzquierda() {
  int del1 = 300;
  int del2 = 10;


  pata1.moverPata(60, pata1.inicialM2, pata1.inicialM3);
  delay(del1);
  pata3.moverPata(60, pata3.inicialM2, pata3.inicialM3);
  delay(del1);
  pata2.moverPata(-20, pata2.inicialM2, pata2.inicialM3);
  delay(del1);

  pata4.moverPata(-20, pata4.inicialM2, pata4.inicialM3);
  delay(del1);

  pata1.empujarPata(pata1.inicialM1, pata1.inicialM2, pata1.inicialM3);
  pata2.empujarPata(pata2.inicialM1, pata2.inicialM2, pata2.inicialM3);
  pata3.empujarPata(pata1.inicialM1, pata1.inicialM2, pata1.inicialM3);
  pata4.empujarPata(pata4.inicialM1, pata4.inicialM2, pata4.inicialM3);
  delay(del1);
}


void test() {

  int del = 1000;
}


/**
   Inicializa los servos a su posicion centrada usando la biblioteca Servo.h
*/
void setupServo() {

  //attach pin salida
  myservo.attach(3);
  //mueve el serfvo al angulo en grados
  myservo.write(90);

}


void posicionInicial() {
  int del = 100;
  pata1.posicionInicial();
  delay(del);
  pata2.posicionInicial();
  delay(del);
  pata3.posicionInicial();
  delay(del);
  pata4.posicionInicial();
  Serial.println("posicion inicial");
}

void pasoPrueba() {
  int del = 300;

  int aux1 = 45;
  int aux2 = 40;
  int aux3 = -40;

  pata1.empujarPata(35, pata3.inicialM2, pata3.inicialM3);
  //  pata3.moverPata(45, pata3.inicialM2, pata3.inicialM3);
  //  delay(del);
  //  pata2.moverPata(0, aux2, aux3);
  //  delay(del);
  //  pata4.moverPata(45, pata4.inicialM2, pata4.inicialM3);
  //  delay(del);
  //  pata1.moverPata(0, aux2, aux3);
}
/**
   Lado derecho centrado lado izquierdo abierto
*/
void paso1() {
  int del = 200;
  int aux1 = 45;
  int aux2 = 40;
  int aux3 = -40;
  pata3.moverPata(45, pata3.inicialM2, pata3.inicialM3);
  delay(del);
  pata2.moverPata(0, aux2, aux3);
  delay(del);
  pata1.moverPata(0, aux2, aux3);
  delay(del);
  pata4.moverPata(45, pata4.inicialM2, pata4.inicialM3);
  Serial.println("paso 1");
}

/**
   mover para derecha delantera
*/
void paso2() {
  pata1.moverPata(65, 40, 40);
  pata1.moverPata(65, 0, 30);
  Serial.println("paso 2");
}

/**
   Empujar todas patas
*/
void paso3() {
  int del = 5;
  pata1.empujarPata(35, pata1.inicialM2, pata1.inicialM3);
  delay(del);
  pata2.empujarPata(45, pata1.inicialM2, pata1.inicialM3);
  delay(del);
  pata3.empujarPata(65, 0, 30);
  delay(del);
  pata4.empujarPata(0, 40, -40);
  Serial.println("paso 3");
}

/**
   mover pata trasera izquierda para centrar lado izquierdo, lado derecho abierto
*/
void paso4() {
  pata3.moverPata(0, 40, -40);
  Serial.println("paso 4");
}

/**
   mover pata delantera izquierda
*/
void paso5() {
  pata4.moverPata(65, 40, 40);
  pata4.moverPata(65, 0, 30);
  Serial.println("paso 5");
}

/**
   Empujar todas patas
   Ir a paso 1
*/
void paso6() {
  int del = 5;

  pata1.empujarPata(0, 40, -40);
  delay(del);
  pata2.empujarPata(65, 0, 30);
  delay(del);
  pata3.empujarPata(45, pata3.inicialM2, pata3.inicialM3);
  delay(del);
  pata4.empujarPata(35, pata3.inicialM2, pata3.inicialM3);
  Serial.println("paso 6");
}

/**
   Misma posicion que el paso1 pero solo hay que avanzar la pata trasera izquierda
*/
void paso7() {
  //  pata2.moverPata(posicion3);
  pata2.moverPata(0, 40, -40);
  Serial.println("paso 7");
}



/**
   Lado derecho centrado lado izquierdo abierto
*/
void pasoAtras1() {
  int del = 200;
  int aux1 = 45;
  int aux2 = 40;
  int aux3 = -40;
  pata3.moverPata(45, pata3.inicialM2, pata3.inicialM3);
  delay(del);
  pata2.moverPata(0, aux2, aux3);
  delay(del);
  pata1.moverPata(0, aux2, aux3);
  delay(del);
  pata4.moverPata(45, pata4.inicialM2, pata4.inicialM3);
  Serial.println("paso atras 1");
}

/**
   mover para derecha delantera
*/
void pasoAtras2() {
  pata2.moverPata(65, 40, 40);
  pata2.moverPata(65, 0, 30);
  Serial.println("paso atras 2");
}

/**
   Empujar todas patas
*/
void pasoAtras3() {
  int del = 5;
  pata1.empujarPata(45, pata3.inicialM2, pata3.inicialM3);
  delay(del);
  pata2.empujarPata(35, pata3.inicialM2, pata3.inicialM3);
  delay(del);
  pata3.empujarPata(0, 40, -40);
  delay(del);
  pata4.empujarPata(65, 0, 30);
  Serial.println("paso atras 3");
}

/**
   mover pata trasera izquierda para centrar lado izquierdo, lado derecho abierto
*/
void pasoAtras4() {
  pata4.moverPata(0, 40, -40);
  Serial.println("paso atras 4");
}

/**
   mover pata delantera izquierda
*/
void pasoAtras5() {
  pata3.moverPata(65, 40, 40);
  pata3.moverPata(65, 0, 30);
  Serial.println("paso atras 5");
}

/**
   Empujar todas patas
   Ir a paso 1
*/
void pasoAtras6() {
  int del = 5;

  pata1.empujarPata(65, 0, 30);
  delay(del);
  pata2.empujarPata(0, 40, -40);
  delay(del);
  pata3.empujarPata(35, pata3.inicialM2, pata3.inicialM3);
  delay(del);
  pata4.empujarPata(45, pata3.inicialM2, pata3.inicialM3);
  Serial.println("paso atras 6");
}

/**
   Misma posicion que el paso1 pero solo hay que avanzar la pata trasera izquierda
*/
void pasoAtras7() {
  //  pata2.moverPata(posicion3);
  pata1.moverPata(0, 40, -40);
  Serial.println("paso atras 7");
}


void reverencia() {
  int del = 300;
  int del2 = 10;


  pata1.moverPata(pata1.inicialM1, pata1.inicialM2, pata1.inicialM3);
  delay(del);
  pata2.moverPata(pata2.inicialM1, pata2.inicialM2, pata2.inicialM3);
  delay(del);
  pata3.moverPata( pata3.inicialM1, pata3.inicialM2, pata3.inicialM3);
  delay(del);
  pata4.moverPata(pata4.inicialM1, pata4.inicialM2, pata4.inicialM3);
  delay(del);

  pata1.moverPata(90, pata1.inicialM2, pata1.inicialM3);
  delay(del);
  pata4.moverPata(90, pata4.inicialM2, pata4.inicialM3);
  delay(del);

  pata1.moverMotor(2, 0);
  pata4.moverMotor(2, 0);
  //delay(del);
  pata1.moverMotor(3, 90);
  pata4.moverMotor(3, 90);
}

void aullar() {
  int del = 300;


  pata1.moverPata(pata1.inicialM1, pata1.inicialM2, pata1.inicialM3);
  delay(del);
  pata2.moverPata(pata2.inicialM1, pata2.inicialM2, pata2.inicialM3);
  delay(del);
  pata3.moverPata( pata3.inicialM1, pata3.inicialM2, pata3.inicialM3);
  delay(del);
  pata4.moverPata(pata4.inicialM1, pata4.inicialM2, pata4.inicialM3);
  delay(del);

  pata2.moverPata(90, pata1.inicialM2, pata1.inicialM3);
  delay(del);
  pata3.moverPata(90, pata4.inicialM2, pata4.inicialM3);
  delay(del);

  pata2.moverMotor(2, 0);
  pata3.moverMotor(2, 0);
  //delay(del);
  pata2.moverMotor(3, 90);
  pata3.moverMotor(3, 90);
}

void saludar(){
  int del = 300;

  int aux2 = 40;
  int aux3 = -40;
  
  pata1.moverPata(pata1.inicialM1, pata1.inicialM2, pata1.inicialM3);
  delay(del);
  pata2.moverPata(0, pata2.inicialM2, pata2.inicialM3);
  delay(del);

  pata3.moverPata(0, aux2, aux3);
  delay(del);
  pata4.moverPata(45, pata4.inicialM2, pata4.inicialM3);
delay(del);

  pata1.moverPata(60,40,90);
  delay(del);
  pata1.moverMotor(1,90);
  delay(del);
  pata1.moverMotor(1, 60);
  delay(del);
  pata1.moverMotor(1,90);
  delay(del);
  pata1.moverMotor(1, 60);
  delay(del);
  pata1.moverPata(pata1.inicialM1, pata1.inicialM2, pata1.inicialM3);
}
