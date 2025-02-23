// Smart Servo Controller with Pattern Recognition, EEPROM, and Safety Mode

#include <Servo.h>
#include <EEPROM.h>
#include <Wire.h>

Servo servo1, servo2, servo3;

const int LED1 = 2, LED2 = 3, LED3 = 4, LED4 = 7, LED5 = 8;
const int button1 = 12, button2 = 13, buzzer = 10;
const int pot1 = A0, pot2 = A1, pot3 = A2;

int pot1Val, pot2Val, pot3Val;
int pot1Angle, pot2Angle, pot3Angle;
int button1Presses = 0;
boolean button2Pressed = false;
unsigned long lastButton2Press = 0;

int servo1PosSaves[5], servo2PosSaves[5], servo3PosSaves[5];

const int MIN_ANGLE = 10;
const int MAX_ANGLE = 170;

void setup() {
  servo1.attach(5);
  servo2.attach(6);
  servo3.attach(9);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

  Serial.begin(9600);
  loadEEPROM();
}

void loop() {
  // Read potentiometer values
  pot1Val = analogRead(pot1);
  pot2Val = analogRead(pot2);
  pot3Val = analogRead(pot3);

  pot1Angle = constrain(map(pot1Val, 0, 1023, 0, 179), MIN_ANGLE, MAX_ANGLE);
  pot2Angle = constrain(map(pot2Val, 0, 1023, 0, 179), MIN_ANGLE, MAX_ANGLE);
  pot3Angle = constrain(map(pot3Val, 0, 1023, 0, 179), MIN_ANGLE, MAX_ANGLE);

  servo1.write(pot1Angle);
  servo2.write(pot2Angle);
  servo3.write(pot3Angle);

  // Save Position
  if (digitalRead(button1) == HIGH) {
    savePosition(button1Presses);
    button1Presses++;
    delay(300); // Debounce delay
  }

  // Replay Positions
  if (digitalRead(button2) == HIGH) {
    if (millis() - lastButton2Press < 2000) {
      randomizedReplay();
    } else {
      normalReplay();
    }
    lastButton2Press = millis();
    delay(300);
  }
}

void savePosition(int index) {
  if (index < 5) {
    servo1PosSaves[index] = pot1Angle;
    servo2PosSaves[index] = pot2Angle;
    servo3PosSaves[index] = pot3Angle;

    digitalWrite(LED1 + index, HIGH);
    tone(buzzer, 1000, 200); // Short beep

    EEPROM.put(index * 6, servo1PosSaves[index]);
    EEPROM.put(index * 6 + 2, servo2PosSaves[index]);
    EEPROM.put(index * 6 + 4, servo3PosSaves[index]);

    Serial.print("Position "); Serial.print(index + 1); Serial.println(" Saved");
  } else {
    tone(buzzer, 500, 600); // Long beep for error
  }
}

void normalReplay() {
  for (int i = 0; i < 5; i++) {
    moveServos(servo1PosSaves[i], servo2PosSaves[i], servo3PosSaves[i]);
    delay(1000);
  }
  playMelody();
}

void randomizedReplay() {
  int order[5] = {0, 1, 2, 3, 4};
  shuffleArray(order, 5);

  for (int i = 0; i < 5; i++) {
    moveServos(servo1PosSaves[order[i]], servo2PosSaves[order[i]], servo3PosSaves[order[i]]);
    delay(1000);
  }
  playMelody();
}

void moveServos(int angle1, int angle2, int angle3) {
  if (angle1 < MIN_ANGLE || angle1 > MAX_ANGLE ||
      angle2 < MIN_ANGLE || angle2 > MAX_ANGLE ||
      angle3 < MIN_ANGLE || angle3 > MAX_ANGLE) {
    tone(buzzer, 500, 800); // Error beep
    return;
  }
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  Serial.print("Moving to: "); Serial.print(angle1); Serial.print(", ");
  Serial.print(angle2); Serial.print(", "); Serial.println(angle3);
}

void shuffleArray(int *array, int size) {
  for (int i = size - 1; i > 0; i--) {
    int j = random(i + 1);
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
  }
}

void loadEEPROM() {
  for (int i = 0; i < 5; i++) {
    EEPROM.get(i * 6, servo1PosSaves[i]);
    EEPROM.get(i * 6 + 2, servo2PosSaves[i]);
    EEPROM.get(i * 6 + 4, servo3PosSaves[i]);
  }
  Serial.println("Positions Loaded from EEPROM");
}

void playMelody() {
  tone(buzzer, 1000, 200);
  delay(250);
  tone(buzzer, 1200, 200);
  delay(250);
  tone(buzzer, 1500, 200);
}
