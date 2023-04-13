int pulsePin = 8; // номер пина, к которому подключен осциллограф
int delayTime = 210000; // задержка между пачками импульсов (в микросекундах)
int burstWidth = 4; // длительность импульсов в пачке (в микросекундах)
int pulseDuration = 60; // длительность отдельного импульса (в микросекундах)
int interPulsePeriod = 200; // задержка между отдельными импульсами в пачке (в микросекундах)
int numberOfBrusts = 4;// Количество отправляемых пачек
int pulseCount = 11;//Количество импульсов в пачке
bool run = false; // переменная для хранения состояния основного цикла
bool buttonState = false; // переменная для хранения состояния кнопки

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
  pinMode(3, INPUT_PULLUP); // устанавливаем пин 4 на вход с подтяжкой к +5В
}

void loop() {
  if(digitalRead(3) == LOW && !buttonState) { // проверяем состояние кнопки
    buttonState = true; // сохраняем состояние кнопки
  }
  if(digitalRead(3) == HIGH && buttonState) { // проверяем, была ли кнопка отпущена
    run = true; // запускаем основной цикл
    buttonState = false; // сбрасываем состояние кнопки
  }
  if(run) { // если запущен
	for (int i = 0; i < numberOfBrusts; i++){
		generateBrust(pulseCount, burstWidth, interPulsePeriod, pulseDuration);
	}
    run = false; // сбрасываем флаг запуска
  }
}