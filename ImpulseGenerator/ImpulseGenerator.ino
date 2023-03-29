int pulsePin = 2; // номер пина, к которому подключен осциллограф
int delayTime = 1000; // задержка между пачками импульсов (в микросекундах)
int burstWidth = 4; // длительность импульсов в пачке (в микросекундах)
int pulseDuration = 2000; // длительность отдельного импульса (в микросекундах)
int interPulsePeriod = 50; // задержка между отдельными импульсами в пачке (в микросекундах)

void generateBrust(int pulseCount, int brustWidth, int interPulsePeriod, int pulseDuration) {
  for (int i = 0; i < pulseCount; i++) { // генерируем pulseCount пачек импульсов
    digitalWrite(pulsePin, HIGH); // включаем нагрузку
    delayMicroseconds(pulseDuration); // длительность импульса
    digitalWrite(pulsePin, LOW); // выключаем нагрузку
    delayMicroseconds(interPulsePeriod); // задержка между отдельными импульсами в пачке
  }
  delayMicroseconds(delayTime - brustWidth * pulseCount - interPulsePeriod * (pulseCount - 1)); // задержка между пачками импульсов
}

void setup() {
  pinMode(pulsePin, OUTPUT); // устанавливаем пин на вывод
  pinMode(A0, INPUT);
  pinMode(A1, INPUT); 
  pinMode(A2, INPUT); 
  pinMode(A3, INPUT); 
}

void loop() {
  burstWidth = map(analogRead(A0), 0, 1023, 1, 500); // изменяем burstWidth соответственно значению на потенциометре 1
  interPulsePeriod = map(analogRead(A1), 0, 1023, 0, 10000); // изменяем interPulsePeriod соответственно значению на потенциометре 2
  pulseDuration = map(analogRead(A2), 0, 1023, 0, 10000); // изменяем pulseDuration соответственно значению на потенциометре 3
  delayTime = map(analogRead(A3), 0, 1023, 1, 10000);
  generateBrust(1, burstWidth, interPulsePeriod, pulseDuration); // вызываем функцию с новыми параметрами
}