#include <LiquidCrystal_I2C.h>

const int buttonPin = 3;
const int ledPinRed =  11;
const int ledPinGreen =  10;

int buttonState = 0;

long startTime;
unsigned long previousMillis=0;
//long interval = 86400000; // 24 hours
long interval = 72000000; // 20 hours
//long interval = 3600000 ; // 1 hour
//long interval = 10000 ; // 10 sec

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  lcd.begin(20, 4);
  lcd.setCursor(0, 0);

  attachInterrupt(digitalPinToInterrupt(buttonPin), button_press_action, CHANGE);
}

void loop() {
  startTime = millis();

  lcdprinttimereverse(startTime, previousMillis);

  if ((unsigned long)(startTime - previousMillis) <= interval) {
    digitalWrite(ledPinGreen, HIGH);
    digitalWrite(ledPinRed, LOW);
  } else {
    digitalWrite(ledPinGreen, LOW);
    digitalWrite(ledPinRed, HIGH);
  }

  buttonState = digitalRead(buttonPin);

  delay(1000);
}

void lcdprinttime(long startTime, unsigned long previousMillis) {
  lcd.clear();
  lcd.print((long)(startTime - previousMillis)/3600000); //hours
  lcd.print(":");
  if ((unsigned long)(startTime - previousMillis)/60000 % 60 < 10) {
    lcd.print(0);
  }
  lcd.print((long)(startTime - previousMillis)/60000 % 60); //minutes
  lcd.print(":");
  if ((unsigned long)(startTime - previousMillis)/1000 % 60 < 10) {
    lcd.print(0);
  }
  lcd.print((unsigned long)(startTime - previousMillis)/1000 % 60); //seconds
}

void lcdprinttimereverse(long startTime, unsigned long previousMillis) {
  lcd.clear();
  lcd.print((long)(19 - (startTime - previousMillis)/3600000)); //hours
  lcd.print(":");

  if ((unsigned long)(startTime - previousMillis)/60000 % 60 > 50) {
    lcd.print(0);
  }
  lcd.print((long)(59 - (startTime - previousMillis)/60000 % 60)); //minutes
  lcd.print(":");



  if ((unsigned long)(startTime - previousMillis)/1000 % 60 >49) {
    lcd.print(0);
  }
  lcd.print((unsigned long)(59 - (startTime - previousMillis)/1000 % 60)); //seconds
}


void button_press_action() {
  previousMillis = startTime;
}

