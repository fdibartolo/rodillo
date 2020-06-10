#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 8, 7, 6, 5);

// Circumference of bicycle wheel expressed in meters
float bicycleWheelCircumference = 0.275;  

const int revolutionButton = 4;

unsigned long currentTime = 0;
unsigned long revolutionTime = 0;
unsigned long lastRevolutionTime = 0;
unsigned long revolutionCount = 0;

float currentDistance;
int currentKPH;

void setup()
{
  pinMode (revolutionButton, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.begin(16, 2);

  printConfig();
  printLabels();
}

void loop() {
  currentTime = millis();

  if (pulseIn(revolutionButton, LOW) > 0) {
    revolutionCount++;
    revolutionTime = currentTime - lastRevolutionTime;

    currentKPH = (3600000 / revolutionTime) * bicycleWheelCircumference / 1000;
    currentDistance = revolutionCount * bicycleWheelCircumference / 1000;
    lastRevolutionTime = currentTime;
  }
  else {
    // no pulse detected (pulseIn has exit on timeout), means it is stopped
    currentKPH = 0;
  }

  printValues();
}

void printConfig() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wheel circ: " + String(bicycleWheelCircumference));
  digitalWrite(LED_BUILTIN, HIGH);
  delay(3000);
  digitalWrite(LED_BUILTIN, LOW);
}

void printLabels() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("km: ");
  lcd.setCursor(0, 1);
  lcd.print("kph: ");
}

void printValues() {
  lcd.setCursor(4, 0);
  lcd.print(currentDistance);
  lcd.setCursor(5, 1);
  if (currentKPH < 10) { lcd.print(" "); }
  lcd.print(currentKPH);
}
