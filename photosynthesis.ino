#include <LiquidCrystal.h>
#include <math.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int LDR = A0;
const int THERM = A1;

const int RED = 9;
const int GREEN = 10;
const int BLUE = 6;
const int BUZZER = 8;

const float R1 = 10000.0;
const float Beta = 3950.0;
const float To = 298.15;
const float Ro = 10000.0;

void setup()
{
  lcd.begin(16, 2);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  int light = analogRead(LDR);
  int adc = analogRead(THERM);

  // Avoid division by zero if the thermistor input reads zero.
  if (adc < 1) {
    adc = 1;
  }

  float Rt = R1 * (1023.0 / adc - 1.0);
  float tempK = 1.0 / ((log(Rt / Ro) / Beta) + (1.0 / To));
  float tempC = tempK - 273.15;

  int efficiency = map(light, 0, 1023, 0, 100);

  if (tempC < 20 || tempC > 35)
  {
    efficiency = 20;
  }

  if (efficiency < 0)
    efficiency = 0;

  if (efficiency > 100)
    efficiency = 100;

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(tempC, 1);
  lcd.print((char)223);
  lcd.print("C ");

  lcd.print("L:");
  lcd.print(light);

  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(efficiency);
  lcd.print("% ");

  if (efficiency >= 70)
  {
    lcd.print("Good");

    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(BUZZER, LOW);
  }
  else if (efficiency >= 40)
  {
    lcd.print("Med");

    digitalWrite(BLUE, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BUZZER, LOW);
  }
  else
  {
    lcd.print("Low");

    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(BUZZER, HIGH);
  }

  Serial.print("Temperature: ");
  Serial.print(tempC, 1);
  Serial.print(" C, Light: ");
  Serial.print(light);
  Serial.print(", Efficiency: ");
  Serial.print(efficiency);
  Serial.println("%");

  delay(1000);
}
