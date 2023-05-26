/*
Se incluye la biblioteca "Servo.h" que permite controlar los servomotores.
Se definen varias variables e constantes utilizadas en el código, incluyendo pines para los motores, el sensor ultrasónico y los LEDs, así como variables para almacenar valores de posición y distancia.
En la función setup(), se inicializan los pines como entradas o salidas, se establece la velocidad de comunicación serial a 9600 baudios y se adjuntan los servomotores a los pines correspondientes.
La función loop() es el bucle principal del programa y se ejecuta repetidamente.
En primer lugar, se lee el valor actual del potenciómetro y se compara con el valor anterior. Si no ha habido cambios, se apagan los motores. De lo contrario, se ejecutan diferentes secuencias de pasos en los motores dependiendo de si el valor actual es mayor o menor que el valor anterior.
A continuación, se leen los valores de los potenciómetros de los tres servomotores, se mapean a un rango de 0 a 180 grados y se establece la posición de los servos en función de estos valores.
Después de controlar los servomotores, se realiza una medición de distancia utilizando el sensor ultrasónico. Se envía un pulso de disparo y se mide el tiempo transcurrido hasta que se recibe el eco reflejado por un objeto. A partir de ese tiempo, se calcula la distancia en centímetros.
Finalmente, se llama a la función indicador_nivel() para mostrar un indicador visual (LED verde o rojo) en función de la distancia medida.
En resumen, este código controla tres servomotores y utiliza un sensor ultrasónico para medir la distancia. También muestra un indicador visual basado en la distancia medida.
*/

#include <Servo.h>

int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
int anterior = 0;

//Sensor
const int echo=A1; /*pin utilizado para recibir el eco del pulso ultrasónico reflejado por un objeto. Este pin mide el tiempo transcurrido entre el envío del 
pulso y la recepción del eco. Este tiempo se utiliza posteriormente en el cálculo de la distancia.*/
const int trigger=A0;
const int LedVerde=13;
const int LedRojo=12;
long tiempo;
float distancia;


//Servo1
Servo Servo1;
const int Pot1=A2;
int valorPot1;
int Ang1 = 20;

//Servo2
Servo Servo2
const int Pot2 =A5;
int valorPot2;
int Ang2= 20;

//Servo3
Servo Servo3
const int Pot3 =A4;
int valorPot3;
int Ang3= 20;


// Secuencia de pasos del motor. 
int paso [4][4] =
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

void setup()
{
  //Paso a paso
  Serial.begin(9600); 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // Servos
  Servo1.attach(4);
  Servo2.attach(5);
  Servo3.attach(6);
 // Sensor
  pinMode(LedVerde, OUTPUT);
  pinMode(LedRojo,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(trigger,OUTPUT);
  delay(100);
  

}
 

void loop()
{ 
  int actual = analogRead(pot);
  if (actual == anterior){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);    
  }else{
    if (actual > anterior){
      for(int k = 0; k<10; k++){  
        for (int i = 0; i < 4; i++){
          digitalWrite(IN1, paso[i][0]);
          digitalWrite(IN2, paso[i][1]);
          digitalWrite(IN3, paso[i][2]);
          digitalWrite(IN4, paso[i][3]);
          delay(10);
          Serial.print("Ciclo 1 ");
        }
      }   
    }
    else{
      for(int k = 0; k<10; k++){        
        for (int j = 3 ; j>=0; j=j-1){
          digitalWrite(IN1, paso[j][0]);
          digitalWrite(IN2, paso[j][1]);
          digitalWrite(IN3, paso[j][2]);
          digitalWrite(IN4, paso[j][3]);
          delay(10);
          Serial.print("Ciclo 2 ");
        }
          
      }
    }  
  }    
  anterior = actual;
  // Servo1
  valorPot1 = analogRead(Pot1);
  Serial.print("Valor pot: ");
  Serial.print(valorPot1);
  Ang1 = map(valorPot1, 0, 1023, 0, 180); // Escala el valor leído entre 0° y 180°
  Serial.print ("angulo= ");
  Serial.println (Ang1);
  Servo1.write(Ang1); // Define la posición del servo
  delay(15);
  //Servo2
  valorPot2 = analogRead(Pot2);
  Serial.print("Valor pot: ");
  Serial.print(valorPot2);
  Ang2 = map(valorPot2, 0, 1023, 0, 180); // Escala el valor leído entre 0° y 180°
  Serial.print ("angulo= ");
  Serial.println (Ang2);
  Servo1.write(Ang2); // Define la posición del servo
  delay(15);

  //Servo3
  valorPot3 = analogRead(Pot3);
  Serial.print("Valor pot: ");
  Serial.print(valorPot3);
  Ang3 = map(valorPot2, 0, 1023, 0, 180); // Escala el valor leído entre 0° y 180°
  Serial.print ("angulo= ");
  Serial.println (Ang3);
  Servo1.write(Ang3); // Define la posición del servo
  delay(15);
  //Sensor

  medir();
  Serial.print("Distancia: ");
  Serial.print(distancia);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  indicador_nivel();


}
void medir()
{
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  
  tiempo=pulseIn(echo,HIGH);//us=microsegundos
  distancia = float(tiempo*0.0343)/2;
  delay(10);
}
void indicador_nivel()
{
if(distancia<7){
  digitalWrite(LedVerde,LOW);
  delay(1000);
  digitalWrite(LedRojo , HIGH);   // poner el Pin en HIGH
  delay(1000);  
}
else if(distancia>=7){
  digitalWrite(LedVerde , HIGH);   // poner el Pin en HIGH
  delay(1000);
  digitalWrite(LedRojo, LOW);
  delay(1000);
}
}
