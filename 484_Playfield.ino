#include <LiquidCrystal_I2C.h>
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
#include <Servo.h>
// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
Servo myservo;

int count = 0;
int score = 0;
int timer = 120;

int dur[10] = {1000, 2000, 2000, 3000, 3000, 3000, 3000, 4000, 4000, 5000};
int rd = random(0, 10);
int servoSpeed = 80;
int servoCount = 0;

const int leftTunnelPin = 2;
const int rightTunnelPin = 3;
const int leftGoalPin = 4;
const int rightGoalPin = 5;
const int middleGoalPin = 6;
const int bumperPin = 7;

void setup() {
  Serial.begin(9600);

  pinMode(leftTunnelPin, INPUT);
  pinMode(rightTunnelPin, INPUT);
  pinMode(leftGoalPin, INPUT);
  pinMode(rightGoalPin, INPUT);
  pinMode(middleGoalPin, INPUT);
  pinMode(bumperPin, INPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,2);
  lcd.print("Score: 0");
  lcd.setCursor(0,0);
  lcd.print("Timer: 120");

  myservo.attach(9);
  myservo.write(servoSpeed);
}

void loop() {
  int leftTunnelState = digitalRead(leftTunnelPin);
  int rightTunnelState = digitalRead(rightTunnelPin);
  int leftGoalState = digitalRead(leftGoalPin);
  int rightGoalState = digitalRead(rightGoalPin);
  int middleGoalState = digitalRead(middleGoalPin);
  int bumperState = digitalRead(bumperPin);

  if (leftTunnelState == LOW) {
    lcd.setCursor(7,2);
    score = score + 10;
    lcd.print(score);
    delay(100);
    count = count + 100;
  }

  if (rightTunnelState == LOW) {
    lcd.setCursor(7,2);
    score = score + 50;
    lcd.print(score);
    delay(100);
    count = count + 100;
  }

  if (leftGoalState == LOW) {
    lcd.setCursor(7,2);
    score = score + 500;
    lcd.print(score);
    delay(100);
    count = count + 100;
  }

  if (rightGoalState == LOW) {
    lcd.setCursor(7,2);
    score = score + 500;
    lcd.print(score);
    delay(100);
    count = count + 100;
  }
  
  if (middleGoalState == LOW) {
    lcd.setCursor(7,2);
    score = score + 1000;
    lcd.print(score);
    delay(100);
    count = count + 100;
  }

  if (bumperState == HIGH) {
    lcd.setCursor(7,2);
    score = score + 20;
    lcd.print(score);
    delay(100);
    count = count + 100;
  }
  
  count = count + 1;
  servoCount = servoCount + 1;
  delay(1);
  if (count >= 1000) {
    timer = timer - 1;
    lcd.setCursor(7,0);
    lcd.print("   ");
    lcd.setCursor(7,0);
    lcd.print(timer);
    count = 0;
  }

  if (servoCount == dur[rd]) {
    if (servoSpeed == 80) {
      servoSpeed = 100;
    } else {
      servoSpeed = 80;
    }
    myservo.write(servoSpeed);
    rd = random(0, 10);
    servoCount = 0;
  }

  if (timer == 0) {
    while (1) {
      myservo.write(90);
    }
  }
}
