/*
Las variables "echo", "trigger", "LedVerde" y "LedRojo" se declaran como constantes de tipo entero y se les asignan valores correspondientes a los pines utilizados en el circuito.
La variable "tiempo" es de tipo long y se utiliza para almacenar el tiempo transcurrido entre el envío del pulso ultrasónico y la recepción del eco.
La variable "distancia" es de tipo float y se utiliza para almacenar la distancia calculada en centímetros.
En la función setup(), se configuran los pines de los LEDs, el pin de entrada del sensor de eco, el pin de salida del trigger y se inicia la comunicación serial a una velocidad de 9600 baudios.
En la función loop(), se llaman a las funciones medir() e indicador_nivel().
La función medir() realiza las siguientes operaciones:
Primero se establece el pin del trigger en bajo durante 2 microsegundos.
A continuación, se establece el pin del trigger en alto durante 10 microsegundos y luego se vuelve a poner en bajo.
Se utiliza la función pulseIn() para medir el tiempo que tarda en llegar el eco al pin de entrada del sensor de eco (echo). El resultado se almacena en la variable "tiempo" en microsegundos.
La distancia se calcula utilizando la fórmula de conversión del tiempo a distancia: distancia = tiempo * 0.0343 / 2. El factor de conversión 0.0343 se utiliza para convertir el tiempo en distancia en centímetros.
La función indicador_nivel() controla los LEDs en función de la distancia medida:
Si la distancia es menor a 7 centímetros, se apaga el LED verde y se enciende el LED rojo durante un segundo.
Si la distancia es igual o mayor a 7 centímetros, se enciende el LED verde y se apaga el LED rojo durante un segundo.
El programa se ejecuta en un bucle continuo, midiendo la distancia y controlando los LEDs en función de la distancia medida. Los resultados de la medición se envían a través de la comunicación serial para su visualización en un monitor serial.
*/

const int echo=A1; /*pin utilizado para recibir el eco del pulso ultrasónico reflejado por un objeto. Este pin mide el tiempo transcurrido entre el envío del 
pulso y la recepción del eco. Este tiempo se utiliza posteriormente en el cálculo de la distancia.*/
const int trigger=A0;
const int LedVerde=13;
const int LedRojo=12;
long tiempo;
float distancia;

void setup() 
{
  pinMode(LedVerde, OUTPUT);
  pinMode(LedRojo,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(trigger,OUTPUT);
  Serial.begin(9600);
  delay(100);
}

void loop() 
{
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