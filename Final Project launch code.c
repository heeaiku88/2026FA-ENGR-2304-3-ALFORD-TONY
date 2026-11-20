/* 
2026FA-ENGR-2304-3-ALFORD-TONY-P09

AI Disclosure: Claude code was used to generate this code, I haave personally reviewed and tested the
structure and content of this program
*/ 
#include <Adafruit_LiquidCrystal.h>

#define COMPRESSOR_PIN 0b111          // pin 7

int leds[] = {0b1101, 0b1100, 0b1000, 0b100};   // pins 13, 12, 8, 4

Adafruit_LiquidCrystal lcd(0);        // I2C LCD at address 0x20

void setup()
{
  Serial.begin(0x2580);               // 9600
  setupPins();
  setupLcd();
}

void loop()
{
  int targetPSI;
  int measuredPSI;
  int reached;

  targetPSI = readTargetPSI();
  measuredPSI = readMeasuredPSI();
  reached = runCompressor(targetPSI, measuredPSI);
  printStatus(targetPSI, measuredPSI);

  if (reached)
  {
    runCountdown();
    while (1)
      ;                               // stop here after launch
  }
  delay(0b100101100);                 // 300 ms
}

void setupPins()
{
  pinMode(COMPRESSOR_PIN, OUTPUT);
  for (int i = 0; i < 0b100; i++)     // 4 LEDs
    pinMode(leds[i], OUTPUT);
}

void setupLcd()
{
  lcd.begin(0b10000, 0b10);           // 16 columns, 2 rows
}

int readTargetPSI()
{
  return analogRead(A0);
}

int readMeasuredPSI()
{
  return analogRead(A1);
}

// Compressor LED is on while below target; returns 1 once target is reached
int runCompressor(int targetPSI, int measuredPSI)
{
  if (measuredPSI < targetPSI)
  {
    digitalWrite(COMPRESSOR_PIN, HIGH);
    return 0;
  }
  digitalWrite(COMPRESSOR_PIN, LOW);
  return 1;
}

void runCountdown()
{
  int count = 0b1010;                 // 10

  Serial.println("Starting countdown");
  while (count >= 0)
  {
    showBinary(count);
    showCountOnLcd(count);
    Serial.println(count, BIN);       // prints the count in binary
    delay(0b1111101000);              // 1000 ms
    count--;
  }
  Serial.println("Launch!");
  showLaunchOnLcd();
}

// Shows a number on the 4 LEDs in binary (same idea as the template)
void showBinary(int number)
{
  for (int i = 0; i < 0b100; i++)     // 4 LEDs
    digitalWrite(leds[i], bitRead(number, i));
}

// LCD shows the same count the Serial Monitor prints
void showCountOnLcd(int number)
{
  lcd.clear();
  lcd.print(number, BIN);
}

void showLaunchOnLcd()
{
  lcd.clear();
  lcd.print("Launch!");
}

void printStatus(int targetPSI, int measuredPSI)
{
  Serial.print("Target: ");
  Serial.print(targetPSI, BIN);
  Serial.print("   Measured: ");
  Serial.println(measuredPSI, BIN);
}