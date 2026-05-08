#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo gate;

int trigPins[] = {6, 8, 10};
int echoPins[] = {7, 9, A0};

int leds[] = {A1, A2, A3};

int trigGate = A5;
int echoGate = 13;

void setup() {
  lcd.begin(16, 2);

  for(int i=0;i<3;i++){
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
    pinMode(leds[i], OUTPUT);
  }

  pinMode(trigGate, OUTPUT);
  pinMode(echoGate, INPUT);

  gate.attach(A4);
  gate.write(0);
}

long readDistance(int trig, int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 30000);

  if(duration == 0) return 999;

  return duration * 0.034 / 2;
}

void loop() {
  int bos = 0;

  for(int i=0;i<3;i++){
    int dist = readDistance(trigPins[i], echoPins[i]);

    if(dist < 20){
      digitalWrite(leds[i], LOW);
    } else {
      digitalWrite(leds[i], HIGH);
      bos++;
    }
  }

  lcd.setCursor(0,0);
  lcd.print("Bos: ");
  lcd.print(bos);
  lcd.print("   ");

  lcd.setCursor(0,1);
  lcd.print("Toplam: 3");

  int gateDist = readDistance(trigGate, echoGate);

  if(gateDist < 10){
    gate.write(90);
  } else {
    gate.write(0);
  }

  delay(300);
}