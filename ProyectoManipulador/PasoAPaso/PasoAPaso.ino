/*
Controla un motor paso a paso utilizando una secuencia de pasos predefinida. A continuación, se describe su funcionamiento:

Se definen las variables IN1, IN2, IN3 y IN4 para representar los pines de salida del Arduino a los que se conectan las bobinas del motor paso a paso. Estos pines se configuran como salidas digitales.

La variable pot se define como A2, lo que indica que se utilizará el pin analógico A2 del Arduino para leer la posición actual del potenciómetro. El potenciómetro se utiliza para controlar la dirección del motor.

La variable anterior se inicializa en 0 y se utiliza para almacenar la lectura anterior del potenciómetro. Se utiliza para determinar si ha habido un cambio en la posición del potenciómetro.

Se define la matriz paso que contiene una secuencia de pasos para el motor. Cada fila de la matriz representa un paso del motor y los valores en cada columna representan el estado de los pines IN1, IN2, IN3 y IN4 correspondientes a ese paso.

En la función setup(), se configuran los pines IN1, IN2, IN3 y IN4 como salidas digitales utilizando pinMode(). Además, se inicializa la comunicación serial a una velocidad de 9600 baudios mediante Serial.begin().

En la función loop(), se lee la posición actual del potenciómetro utilizando analogRead() y se almacena en la variable actual.

Se verifica si la posición actual es igual a la posición anterior. Si son iguales, se apagan todas las bobinas del motor, es decir, se establecen los pines IN1, IN2, IN3 y IN4 en bajo (LOW) utilizando digitalWrite().

Si la posición actual es diferente a la posición anterior, se verifica si la posición actual es mayor que la anterior. En caso afirmativo, se ejecuta un bucle que repite el siguiente proceso 10 veces:

a. Se recorre la matriz paso en orden ascendente, y se establecen los pines IN1, IN2, IN3 y IN4 según los valores de la fila correspondiente.

b. Se introduce un retardo de 10 milisegundos utilizando delay().

c. Se envía por el puerto serie el mensaje "Ciclo 1".

Si la posición actual es menor que la posición anterior, se ejecuta un bucle similar al anterior, pero en este caso se recorre la matriz paso en orden descendente.

Al final del bucle principal, se actualiza la variable anterior con el valor de actual, para que en la próxima iteración se pueda determinar si ha habido un cambio en la posición del potenciómetro.

En resumen, el código controla un motor paso a paso en función de la posición de un potenciómetro. Dependiendo de si la posición actual es mayor o menor que la posición anterior, el motor girará en una dirección u otra, utilizando una secuencia de pasos predefinida. Además, se muestra información sobre el ciclo en el que se encuentra el motor a través de la comunicación serial.
*/

int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
int pot = A2;
int anterior = 0;
 
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
  
  Serial.begin(9600); 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
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
}