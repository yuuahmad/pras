#include <ESP8266WiFi.h>    
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // Lebar pixel
#define SCREEN_HEIGHT 64 // Tinggi pixel

// Deklarasi SSD1306 ke I2C (SDA, SCL)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int sensor = A0;
//int nilaimax = 200;

void setup() {
  Serial.begin(115200);
  pinMode (sensor, INPUT);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Alamat 0x3D untuk 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Gula Darah");
  display.display(); 

}

void loop() {
  int nilaisensor = analogRead (sensor);
  int nilaikalibrasi = (200-(nilaisensor/2)-3.5);
  //int rata = nilaisensor
 Serial.println(nilaisensor);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("Nilai Gula Darah");
  display.setTextSize(2);
  display.setCursor(0, 30);
  display.println(nilaikalibrasi);
  delay(500);
  
  display.display(); 

}
