#include <Ultrasonic.h>


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

//Ultrasonic sensor
Ultrasonic front_sensor(2, 3); // Trig - 2, Echo - 3
//----------------------------------------------------------------

const int dia = 60;  // Radius of the wheel (mm)
const int len = M_PI * dia;

const int dia2 = 175; // Distance between two wheels (mm)
const int len2 = M_PI * dia2;
 
int delayTime = 4; // Delay between each step (ms)

int stop_distance = 15; // How close the robot will move to the barrier before he stops (cm)

int sensor_freq = 150; // ticks

int front_sensor_prev = -1;


void setup() {
    pinMode(stepPin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    pinMode(stepPin2, OUTPUT);
    pinMode(directionPin2, OUTPUT);
    
    Serial.begin(9600);
    
    //mov(500, F, 100);  

    mov(2, B, 0);
    delay(1000);
   
    mov(335, F, 1);
    turn(90, R);
    mov(205, F, 0);
    turn(90, L);
    mov(850, F, 100);  // Castle
    mov(580, B, 0);
    
    turn(90, L);
    mov(825, F, 0);  // First flag
    mov(250, B, 0);
    turn(90, L);
    mov(270, F, 0);
    turn(90, R);
    mov(275, F, 0);  // Second flag
}

void loop() {
}


void mov(int dist, int dir, int check) {  // check: 0 - never check. 1 - always check. n - stop checking on last n mm.
    int steps = dist * 200.0 / len;
    int no_check_steps = (check + stop_distance * 10.0) * 200.0 / len;
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

        digitalWrite(stepPin, LOW);
        digitalWrite(stepPin2, LOW);

//        Serial.println(front_sensor_prev);
        
        front_sensor_prev = front_sensor.Ranging(CM);
        
        sensor_freq = front_sensor_prev / 3 + 100;
        
        Serial.println(sensor_freq);
        
        if (check == 1 && i % sensor_freq == 0) {
            bool tg = false;
            while (front_sensor.Ranging(CM) <= stop_distance) {continue; tg = true;}
            if (tg) {delay(500);}
        } else if (check > 1) {
            while (front_sensor.Ranging(CM) <= stop_distance && (steps - i) > no_check_steps) {continue;}
        } 
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
        Serial.println(i);
        digitalWrite(stepPin, HIGH);
        digitalWrite(stepPin2, HIGH);
        delay(delayTime);
        digitalWrite(stepPin, LOW);
        digitalWrite(stepPin2, LOW);
        delay(delayTime);
    }
}


