#include <LiquidCrystal_I2C.h>

const int buttonPin = 3;
const int ledPinRed =  11;
const int ledPinGreen =  10;

int buttonState = 0;

long startTime;
unsigned long previousMillis=0;
unsigned long actualInterval=0;
//long interval = 86400000; // 24 hours
//long interval = 72000000; // 20 hours
//long interval = 3600000 ; // 1 hour
long interval = 10000 ; // 10 sec
//long interval = 1000 ; // 1 sec

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
  actualInterval = startTime - previousMillis;

  if (actualInterval <= interval) {
    lcdprinttimereverse();
    digitalWrite(ledPinGreen, HIGH);
    digitalWrite(ledPinRed, LOW);
  } else {
    digitalWrite(ledPinGreen, LOW);
    digitalWrite(ledPinRed, HIGH);
    lcdprintwarning();
  }

  buttonState = digitalRead(buttonPin);

  delay(1000);
}

void lcdprinttime(long startTime, unsigned long previousMillis) {
  lcd.clear();
  lcd.print((long)(actualInterval)/3600000); //hours
  lcd.print(":");
  if ((unsigned long)(actualInterval)/60000 % 60 < 10) {
    lcd.print(0);
  }
  lcd.print((long)(actualInterval)/60000 % 60); //minutes
  lcd.print(":");
  if ((unsigned long)(actualInterval)/1000 % 60 < 10) {
    lcd.print(0);
  }
  lcd.print((unsigned long)(actualInterval)/1000 % 60); //seconds
}

void lcdprinttimereverse() {
  lcd.clear();
  lcd.setCursor(0,0) ;
  lcd.print("   Until CRASH");
  lcd.setCursor(0,1) ;
  lcd.print("    ");
  lcd.print((long)(19 - (actualInterval)/3600000)); //hours
  lcd.print(":");

  if ((unsigned long)(actualInterval)/60000 % 60 > 50) {
    lcd.print(0);
  }
  lcd.print((long)(59 - (actualInterval)/60000 % 60)); //minutes
  lcd.print(":");

  if ((unsigned long)(actualInterval)/1000 % 60 >49) {
    lcd.print(0);
  }
  lcd.print((unsigned long)(59 - (actualInterval)/1000 % 60)); //seconds
}
void lcdprintwarning() {
  lcd.noBacklight();
  lcd.clear();
  lcd.setCursor(0,0) ;
  lcd.print("UWAGA! UWAGA!");
  lcd.setCursor(0,1) ;
  lcd.print("Clean machine");

  delay(1000);
  lcd.backlight();
}

void button_press_action() {
  previousMillis = startTime;
}

