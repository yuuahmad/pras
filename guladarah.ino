

/*
* GULA DARAH NON INVASIF
*/
#include <ESP8266WiFi.h>    
// Deklarasi Library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // Lebar pixel
#define SCREEN_HEIGHT 64 // Tinggi pixel

// Deklarasi SSD1306 ke I2C 
//(SDA--D2, SCL--D1)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Deklarasi Pin sensor, data sensor
int sensor = A0;
int nilaimax = 200;
int dataGula;

void setup() {
  Serial.begin(115200);
  pinMode (sensor, INPUT);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Alamat 0x3D untuk 128x64
    Serial.println(F("Alokasi SSD1306 gagal"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Gula Darah");
  display.display(); 
}

//--------------------------------------------------------------------------------------
void loop() {
  gulaDarah();delay(500);
}

//--------------------------------------------------------------------------------------
int bacaGula() {
  // Rumus pembacaan sensor Gula Darah
  int nilaisensor = analogRead (sensor);
  return nilaisensor = (nilaimax-(nilaisensor/2)-3.5);
}

//--------------------------------------------------------------------------------------
void gulaDarah() {
  // Pengambilan nilai rata-rata sensor
  for (int i=10; i>0; i--) {
    delay(50);
    dataGula += bacaGula();
  } 
  dataGula = dataGula/10;
  Serial.print("Gula Darah: ");
  Serial.print(dataGula);
  Serial.println(" mg/dL. ");
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("Nilai Gula Darah");
  display.setTextSize(2);
  display.setCursor(0, 30);
  display.println(dataGula);
  display.setCursor(20, 30);
  display.println(dataGula);
  delay(200);
  display.display(); 
}
