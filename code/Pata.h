
class Pata {
  private:
    byte motor1 = 0;
    byte motor2 = 0;
    byte motor3 = 0;
    int offsetM1 = 0;
    int offsetM2 = 0;
    int offsetM3 = 0;
    int centro = 6000;

    int invM1 = 1;
    int invM2 = 1;
    int invM3 = 1;

    const int factor = 45; //variar el pulso es un factor de 45 (son 11.1, pero el maestro divide entre 4) equivale a moverse 1º

    int levantar = 15 * factor;

    int del500 = 500;
    int del000 = 1000;

  public:
    /**
       Constructor, recibe el pin del Maestro al que están conectados el motor 1 y 2 de cada pata
    */
    int inicialM1 = 20;
    int inicialM2 = 15;
    int inicialM3 = -15;

    Pata(byte m1, byte m2, byte m3) {
      motor1 = m1;
      motor2 = m2;
      motor3 = m3;
    }

    void setOffset(int off1, int off2, int off3) {
      offsetM1 = off1;
      offsetM2 = off2;
      offsetM3 = off3;
    }

    void setInversionMotores(int i1, int i2, int i3) {
      invM1 = i1;
      invM2 = i2;
      invM3 = i3;
    }

    /**
       Inicializa los motores, los pone en posicion centrada y les da la velocidad y aceleracion recibidas
    */
    void setupPata(int vel, int acel) {
      int del = 500;
      
      maestro.setSpeed(motor1, vel);
      maestro.setAcceleration(motor1, acel);
      //maestro.setTarget(motor1, centro + offsetM1 + invM1 * inicialM1 * factor);
      //delay(del);
      
      maestro.setSpeed(motor3, vel);
      maestro.setAcceleration(motor3, acel);
     // maestro.setTarget(motor3, centro + offsetM3 + invM3 * inicialM3 * factor);
     // delay(del);
      
      maestro.setSpeed(motor2, vel);
      maestro.setAcceleration(motor2, acel);
      //maestro.setTarget(motor2, centro + offsetM2 + invM2 * inicialM2 * factor);
     // delay(del);
    }

    void moverMotor(int motor, int angulo){
      angulo = angulo * factor;
      if (motor == 1){
        maestro.setTarget(motor1, centro + invM1 * angulo + offsetM1);
      }
      if (motor == 2){
        maestro.setTarget(motor2, centro + invM2 * angulo + offsetM2);
      }
      if (motor == 3){
        maestro.setTarget(motor3, centro + invM3 * angulo + offsetM3);
      }
    }

    /**
       Recibe los grados que tiene que moverse cada motor
    */
    void moverPata(int m1, int m2, int m3) {

      m1 = factor * m1;
      m2 = factor * m2;
      m3 = factor * m3;

      int del = 200;
      maestro.setTarget(motor2, centro + invM2 * m2 + offsetM2 + invM2 *levantar);
      maestro.setTarget(motor3, centro + invM3 * m3 + offsetM3 + invM3 *levantar);
      delay(del);
      maestro.setTarget(motor1, centro + invM1 * m1 + offsetM1);
      delay(del);

      maestro.setTarget(motor2, centro + invM2 * m2 + offsetM2);
      maestro.setTarget(motor3, centro + invM3 * m3 + offsetM3);
      delay(del);
    }

    void empujarPata(int m1, int m2, int m3) {
      m1 = factor * m1;
      m2 = factor * m2;
      m3 = factor * m3;
      maestro.setTarget(motor1, centro + invM1 * m1 + offsetM1);
      maestro.setTarget(motor2, centro + invM2 * m2 + offsetM2);
      maestro.setTarget(motor3, centro + invM3 * m3 + offsetM3);
    }

    void levantarPata() {
      maestro.setTarget(motor2, levantar + offsetM2);
    }

    void posicionInicial() {
      int del = 500;
      maestro.setTarget(motor1, centro + offsetM1 + invM1 * inicialM1 * factor);
      delay(del);

      maestro.setTarget(motor3, centro + offsetM3 + invM3 * inicialM3 * factor);
      maestro.setTarget(motor2, centro + offsetM2 + invM2 * inicialM2 * factor);
      delay(del);
    }

    void posicionR1() {
      moverPata(0, 0, 0);
    }

    void posicionR2() {
      int despl = 30 * factor;
      moverPata(despl, despl, despl);
    }

    void posicionR3() {
      int despl = 45 * factor;
      moverPata(despl, despl, despl);

    }

    void subir () {
      int despl = 45 * factor;
      moverPata(despl, -despl, -despl);
    }

    void saludar () {

      int despl = -90 * factor;
      int despl1 = 30 * factor;
      int despl3 = -15 * factor;
      maestro.setTarget(motor3, centro + offsetM3 + invM3 * despl);
      delay(500);
      maestro.setTarget(motor1, centro + offsetM1 + 2 * invM1 * despl1 );
      delay(500);
      maestro.setTarget(motor1, centro + offsetM1 - invM1 * despl1 );
      delay(500);
      maestro.setTarget(motor1, centro + offsetM1 + invM1 * despl1 );
      delay(500);
      maestro.setTarget(motor3, centro + offsetM3 + invM3 * despl3);

    }
};
