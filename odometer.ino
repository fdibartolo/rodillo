#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 8, 7, 6, 5);

// Circumference of bicycle wheel expressed in meters
float bicycleWheelCircumference = 0.2915;  

const int revolutionButton = 4;

unsigned long currentTime = 0;
unsigned long revolutionTime = 0;
unsigned long lastRevolutionTime = 0;
unsigned long revolutionCount = 0;
unsigned long lastPrintValTime = 0;

float currentDistance;
int currentKPH;
int maxKPH = 0;

void setup()
{
  pinMode(revolutionButton, INPUT);
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
    if (currentKPH > maxKPH) { maxKPH = currentKPH; }
  }
  // no pulse detected (pulseIn has exit on timeout), means it is stopped
  else { currentKPH = 0; }

  // if half a second has elapsed, print values (to avoid lcd to flicker)
  if (currentTime > (lastPrintValTime + 500)) { 
    printValues();
    lastPrintValTime = currentTime;
  }
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
  lcd.setCursor(9, 1);
  lcd.print("max: ");
}

void printValues() {
  lcd.setCursor(4, 0);
  lcd.print(currentDistance);
  lcd.setCursor(5, 1);
  if (currentKPH < 10) { lcd.print(" "); }
  lcd.print(currentKPH);
  lcd.setCursor(14, 1);
  lcd.print(maxKPH);
}
