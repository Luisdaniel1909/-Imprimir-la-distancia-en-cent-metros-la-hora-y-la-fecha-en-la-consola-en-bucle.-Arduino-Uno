#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;
const int trigPin = 9; // Pin TRIG del HC-SR04
const int echoPin = 10; // Pin ECHO del HC-SR04
const int interval = 1000; // Intervalo de tiempo para la medición (en milisegundos) si deseas puedes cambiar este valor a mas, por ejemplo a 2000

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  // En caso de que la hora y la fecha del Reloj DS3231 este mal utiliza solo la siguiente line de código:
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  DateTime now = rtc.now(); // Obtiene la hora actual del DS3231
  digitalWrite(trigPin, LOW); // Establece el pin TRIG en LOW durante 2 microsegundos
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // Establece el pin TRIG en HIGH durante 10 microsegundos
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // Establece el pin TRIG en LOW
  long duration = pulseIn(echoPin, HIGH); // Mide la duración del pulso de ECHO
  int distance = duration / 58; // Calcula la distancia en centímetros
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.print(" cm, ");
  Serial.print(now.day(), DEC);
  Serial.print("/");
  Serial.print(now.month(), DEC);
  Serial.print("/");
  Serial.print(now.year(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.println(); // Imprime una línea vacía
  delay(interval); // Espera un segundo antes de volver a medir
}
