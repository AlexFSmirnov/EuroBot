//Right, Left, Forward and Backward (for more comfort control)
const int R = 0;
const int L = 1;
const int F = 2;
const int B = 3;


//PINS------------------------------------------------------------
//Right driver
const byte stepPin = 12;
const byte directionPin = 11;

//Left driver
const byte stepPin2 = 10;
const byte directionPin2 = 9;
//----------------------------------------------------------------

const int dia = 60;  // Radius of the wheel (mm)
const int len = M_PI * dia;

const int dia2 = 175; // Distance between two wheels (mm)
const int len2 = M_PI * dia2;
 
int delayTime = 4; // Delay between each step (ms)


void setup() {
    pinMode(stepPin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    pinMode(stepPin2, OUTPUT);
    pinMode(directionPin2, OUTPUT);
    
    Serial.begin(9600);
    mov(2, B);
    delay(4000);
    
    mov(335, F);
    turn(90, R);
    mov(205, F);
    turn(90, L);
    mov(850, F);  // Castle
    mov(580, B);
    
    turn(90, L);
    mov(785, F);  // First flag
    mov(250, B);
    turn(90, L);
    mov(270, F);
    turn(90, R);
    mov(275, F);  // Second flag
}

void loop() {
}


void mov(int dist, int dir) {
    int steps = dist * 200.0 / len;
    if (dir == F) {
        digitalWrite(directionPin, LOW);
        digitalWrite(directionPin2, LOW);
    } else if (dir == B) {
        digitalWrite(directionPin, HIGH);
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
    if (dir == R) {
        digitalWrite(directionPin, HIGH);
        digitalWrite(directionPin2, LOW);
    } else if (dir == L) {
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


