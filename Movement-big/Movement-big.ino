// Troyka-Stepper подключён к следующим пинам:
const byte stepPin = 3;
const byte directionPin = 4;
const byte enablePin = 5;

const byte stepPin2 = 9;
const byte directionPin2 = 10;
const byte enablePin2 = 11;

const int R = 0;
const int L = 1;
const int F = 2;
const int B = 3;

const int rad = 30; //radius of the wheel (mm)
const int len = 2 * M_PI * rad;

const int dia2 = 238; //dist between two steppers. Big - 238
const int len2 = M_PI * dia2;
 
// Выдержка для регулировки скорости вращения
int delayTime = 2;


int prev = 0;
void setup() {
  // Настраиваем нужные контакты на выход
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);
  pinMode(stepPin2, OUTPUT);
  pinMode(directionPin2, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  digitalWrite(enablePin2, HIGH);
  Serial.begin(9600);
  delay(2000);
  turn(360, R);
  //mov(300, F);
}
 
void loop() {
//  mov(600, F);
//  delay(1000);
//  turn(360, R);
//  delay(1000);
  
}


void mov(int dist, int dir) {
  int steps = dist * 200.0 / len;
  if (dir == F) {
    digitalWrite(directionPin, HIGH);
    digitalWrite(directionPin2, LOW);
  }else if (dir == B) {
    digitalWrite(directionPin, LOW);
    digitalWrite(directionPin2, HIGH);
  }
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin2, HIGH);
    delay(delayTime);
    digitalWrite(stepPin, LOW);
    digitalWrite(stepPin2, LOW);
    delay(delayTime);
  }
}



void turn(int angle, int dir) {
  int steps = (len2 * 1.0) / (len * 1.0) * (angle / 360.0) * 200;
  Serial.println(steps);
  if (dir == R) {
    digitalWrite(directionPin, HIGH);
    digitalWrite(directionPin2, HIGH);
  }else if (dir == L) {
    digitalWrite(directionPin, LOW);
    digitalWrite(directionPin2, LOW);
  }
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin2, HIGH);
    delay(delayTime);
    digitalWrite(stepPin, LOW);
    digitalWrite(stepPin2, LOW);
    delay(delayTime);
  }
}


