#include <Arduino.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
// include lcd
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// #define REPORTING_PERIOD_MS 1000

// Create a PulseOximeter object
PulseOximeter pox;

// Time at which the last beat occurred
unsigned long tsLastReport = 0;

// Callback routine is executed when a pulse is detected
void onBeatDetected()
{
  Serial.println("Beat!");
}

void setup()
{
  // setup lcd
  lcd.init(); // initialize the lcd
  lcd.backlight();

  // setup serial monitor
  Serial.begin(9600);

  Serial.print("Initializing pulse oximeter..");
  lcd.setCursor(0, 0);
  lcd.print("memulai      ");

  // Initialize sensor
  if (!pox.begin())
  {
    Serial.println("FAILED");
    lcd.setCursor(0, 1);
    lcd.print("sensor ggl      ");
    for (;;)
      ;
  }
  else
  {
    Serial.println("SUCCESS");
    lcd.setCursor(0, 1);
    lcd.print("sensor bnr      ");
  }

  // Configure sensor to use 7.6mA for LED drive
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

  // Register a callback routine
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
  // Read from the sensor
  pox.update();

  // Grab the updated heart rate and SpO2 levels
  unsigned long milisSekarang = millis();
  if (milisSekarang - tsLastReport >= 1000)
  {
    Serial.print("Heart rate:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / SpO2:");
    Serial.print(pox.getSpO2());
    Serial.println("%");

    lcd.setCursor(0, 0);
    lcd.print("Dtk jnt: ");
    lcd.print(pox.getHeartRate());
    lcd.print("     ");

    lcd.setCursor(0, 1);
    lcd.print("spo2: ");
    lcd.print(pox.getSpO2());
    lcd.print("     ");

    tsLastReport = milisSekarang;
  }
}