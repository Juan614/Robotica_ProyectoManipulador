/*
#include <Servo.h>: Esta línea incluye la biblioteca Servo.h, que proporciona las funciones necesarias para controlar un servo motor.

Servo Servo1;: Se declara un objeto de tipo Servo llamado Servo1. Este objeto se utilizará para controlar el servo motor.

const int Pot=A2;: Se declara una constante Pot que se asigna al pin analógico A2. Este pin se utilizará para leer el valor del potenciómetro.

int valorPot;: Se declara una variable valorPot que se utilizará para almacenar el valor leído del potenciómetro.

int Ang = 20;: Se declara una variable Ang y se le asigna un valor inicial de 20. Esta variable se utilizará para almacenar el ángulo de posición del servo motor.

void setup(): Esta es la función de configuración que se ejecuta una vez al inicio. Aquí se realiza la inicialización del servo motor y se configura la comunicación serie a una velocidad de 9600 baudios.

Servo1.attach(3);: Se llama al método attach() del objeto Servo1 para asociarlo al pin digital 3. Esto establece la conexión entre el servo motor y el pin de control.

Serial.begin(9600);: Se llama al método begin() de la clase Serial para inicializar la comunicación serie a una velocidad de 9600 baudios. Esto permite enviar datos al monitor serie para su visualización.

void loop(): Esta es la función principal que se ejecuta repetidamente después de la función de configuración.

valorPot = analogRead(Pot);: Se lee el valor analógico presente en el pin asignado al potenciómetro y se almacena en la variable valorPot.

Serial.print("Valor pot: ");: Se envía la cadena de caracteres "Valor pot: " al monitor serie.

Serial.print(valorPot);: Se envía el valor leído del potenciómetro al monitor serie.

Ang = map(valorPot, 0, 1023, 0, 180);: Se utiliza la función map() para escalar el valor leído del potenciómetro de un rango de 0 a 1023 a un rango de 0 a 180. El resultado se almacena en la variable Ang.

Serial.print("angulo= ");: Se envía la cadena de caracteres "angulo= " al monitor serie.

Serial.println(Ang);: Se envía el valor de Ang al monitor serie, seguido de un salto de línea.

Servo1.write(Ang);: Se llama al método write() del objeto Servo1 para establecer la posición del servo motor según el valor almacenado en Ang.

delay(15);: Se agrega un retraso de 15 milisegundos antes de repetir el ciclo del bucle loop(). Esto permite un tiempo de espera entre las lecturas del potenciómetro y los movimientos del servo motor.
*/

#include <Servo.h>

Servo Servo1;
const int Pot=A2;
int valorPot;
int Ang = 20;

void setup() {
  // put your setup code here, to run once:
  Servo1.attach(3);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  valorPot = analogRead(Pot);
  Serial.print("Valor pot: ");
  Serial.print(valorPot);
  Ang = map(valorPot, 0, 1023, 0, 180); // Escala el valor leído entre 0° y 180°
  Serial.print ("angulo= ");
  Serial.println (Ang);
  Servo1.write(Ang); // Define la posición del servo
  delay(15);
}
