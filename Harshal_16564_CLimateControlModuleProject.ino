#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

// Pins
#define TEMP_SENSOR A0

#define ENA 10   // L293D Enable (PWM)
#define IN1 8
#define IN2 9

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Motor direction
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Climate Control");
  delay(2000);
  lcd.clear();
}

void loop() {

  int value = analogRead(TEMP_SENSOR);

  // LM35 calculation
  float voltage = value * (5.0 / 1023.0);
  float temp = voltage * 100;

  int pwm = 0;

  // Temperature control
  if (temp < 27) {
    pwm = 0;
  }
  else if (temp >= 40) {
    pwm = 255;
  }
  else {
    pwm = map(temp, 27, 40, 0, 255);
  }

  // Motor speed
  analogWrite(ENA, pwm);

  // Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C, PWM: ");
  Serial.println(pwm);

  // LCD Display
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print(temp);
  lcd.print(" C ");

  lcd.setCursor(0,1);
  lcd.print("PWM:");
  lcd.print(pwm);
  lcd.print("   ");

  delay(500);
}