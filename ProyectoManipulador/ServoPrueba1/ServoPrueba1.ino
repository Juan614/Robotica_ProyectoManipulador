/*
Se incluye la librería "Servo.h" que permite controlar el servo en Arduino.

Se declara una variable llamada "servoMotor" de tipo "Servo" que se utilizará para controlar el servo.

En la función "setup()", se inicia la comunicación serial a una velocidad de 9600 baudios utilizando "Serial.begin(9600)".

A continuación, se utiliza "servoMotor.attach(4)" para conectar el pin 4 de Arduino al servo y prepararlo para su uso.

Dentro de la función "loop()", se realizan las siguientes acciones en bucle:

a. El servo se desplaza a la posición 0 grados utilizando "servoMotor.write(0)".

b. Se espera 1 segundo utilizando "delay(1000)".

c. El servo se desplaza a la posición 90 grados utilizando "servoMotor.write(90)".

d. Se espera 1 segundo.

e. El servo se desplaza a la posición 180 grados utilizando "servoMotor.write(180)".

f. Se espera 1 segundo.

g. El servo se desplaza a la posición -90 grados utilizando "servoMotor.write(-90)".

h. Se espera 1 segundo.

i. El servo vuelve a la posición 0 grados utilizando "servoMotor.write(0)".

j. Se espera 1 segundo.

Este ciclo se repite continuamente mientras la placa Arduino esté encendida. Cada vez que el servo se desplaza a una posición, se espera 1 segundo antes de moverse nuevamente. Este código básico permite controlar un servo y hacer que se mueva a diferentes ángulos en un intervalo de tiempo determinado.
*/

// Incluímos la librería para poder controlar el servo
#include <Servo.h>
 
// Declaramos la variable para controlar el servo
Servo servoMotor;
 
void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);
 
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(4);
}
 
void loop() {
  
  // Desplazamos a la posición 0º
  servoMotor.write(0);
  // Esperamos 1 segundo
  delay(1000);
  
  // Desplazamos a la posición 90º
  servoMotor.write(90);
  // Esperamos 1 segundo
  delay(1000);
  
  // Desplazamos a la posición 180º
  servoMotor.write(180);
  // Esperamos 1 segundo
  delay(1000);

  servoMotor.write(-90);

  delay(1000);

  servoMotor.write(0);
  // Esperamos 1 segundo
  delay(1000);
}