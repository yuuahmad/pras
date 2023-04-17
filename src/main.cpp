// #include <Arduino.h>
// #include <Wire.h>
// #include "MAX30100_PulseOximeter.h"
// // include wifi
// #include <SD.h>

// // include firebase dan wifi
// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>

// // include lcd
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// // #define REPORTING_PERIOD_MS 1000

// // Create a PulseOximeter object
// PulseOximeter pox;

// // Time at which the last beat occurred
// unsigned long tsLastReport = 0;

// // variabel nilai gula darah
// float gulaDarah = 0;
// float nilaiJantung = 0;
// float nilaispo2 = 0;

// // Replace with your network credentials
// const char *ssid = "Tselhome-03F0";
// const char *password = "71314517";

// // Create an instance of the server
// ESP8266WebServer server(80);

// // Callback routine is executed when a pulse is detected
// void onBeatDetected()
// {
//   Serial.println("Beat!");
// }

// void handleRoot()
// {
//   // Create HTML page with sensor data
//   String html = "<html><body>";
//   html += "<head><meta http-equiv=\"refresh\"content=\"1\"></head>";
//   html += "<h1>Sensor Data</h1>";
//   html += "<p>detak jantung: " + String(nilaiJantung) + " bpm</p>";
//   html += "<p>nilai spo2: " + String(nilaispo2) + " %</p>";
//   html += "<p>gula darah: " + String(gulaDarah) + " mg/dl</p>";
//   html += "</body></html>";

//   // Send HTML page to client
//   server.send(200, "text/html", html);
// }

// void setup()
// {
//   // setup lcd
//   lcd.init(); // initialize the lcd
//   lcd.backlight();

//   // setup serial monitor
//   Serial.begin(115200);

//   // Connect to Wi-Fi network
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }

//   // Print local IP address and start server
//   Serial.println(WiFi.localIP());
//   server.on("/", handleRoot);
//   server.begin();

//   Serial.print("Initializing pulse oximeter..");
//   lcd.setCursor(0, 0);
//   lcd.print("memulai      ");

//   // Initialize sensor
//   if (!pox.begin())
//   {
//     Serial.println("FAILED");
//     lcd.setCursor(0, 1);
//     lcd.print("sensor ggl      ");
//     for (;;)
//       ;
//   }
//   else
//   {
//     Serial.println("SUCCESS");
//     lcd.setCursor(0, 1);
//     lcd.print("sensor bnr      ");
//   }

//   // Configure sensor to use 7.6mA for LED drive
//   pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

//   // Register a callback routine
//   pox.setOnBeatDetectedCallback(onBeatDetected);
// }

// void loop()
// {
//   // Read from the sensor
//   pox.update();

//   // Grab the updated heart rate and SpO2 levels
//   unsigned long milisSekarang = millis();
//   if (milisSekarang - tsLastReport >= 1000)
//   {
//     gulaDarah = pox.getHeartRate() / 120 * 140;
//     nilaiJantung = pox.getHeartRate();
//     nilaispo2 = pox.getSpO2();

//     Serial.print("Heart rate:");
//     Serial.print(pox.getHeartRate());
//     Serial.print("bpm / SpO2:");
//     Serial.print(pox.getSpO2());
//     Serial.println("%");
//     Serial.print("gulaDarah : ");
//     Serial.print(gulaDarah);
//     Serial.print("mg/dl");
//     Serial.println();

//     lcd.setCursor(0, 0);
//     lcd.print("Dtk jnt: ");
//     lcd.print(pox.getHeartRate());
//     lcd.print("     ");

//     lcd.setCursor(0, 1);
//     lcd.print("spo2: ");
//     lcd.print(pox.getSpO2());
//     lcd.print(" ");
//     lcd.print(gulaDarah);
//     lcd.print("mg/dl");
//     tsLastReport = milisSekarang;
//   }

//   server.handleClient();
// }

#include <Arduino.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
// include wifi
#include <ESP8266WiFi.h> //Memasukkan library WiFi ESP8266
// // include firebase dan wifi
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#define WIFI_SSID "Tselhome-03F0" // ini adalah nama wifi
#define WIFI_PASSWORD "71314517"  // dan ini adalah passwordnya. kosongkan bagian ini kalau tidak pakai password
#define API_KEY "AIzaSyBaABgqu6h0IDKAa7PO6b8U1HHje5FZRhg"
#define DATABASE_URL "pras-soton-default-rtdb.asia-southeast1.firebasedatabase.app" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define USER_EMAIL "ahmadyusufmaulana0@gmail.com"
#define USER_PASSWORD "yusuf1112"
// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;

// include lcd
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// #define REPORTING_PERIOD_MS 1000

// Create a PulseOximeter object
PulseOximeter pox;

// Time at which the last beat occurred
unsigned long tsLastReport = 0;

// variabel nilai gula darah
float gulaDarah = 100;
float nilaiJantung = 10;
float nilaispo2 = 23;

WiFiServer server(80); // mulai pada port 80

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
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  lcd.setCursor(0, 0);
  lcd.print("connecting     ");
  lcd.setCursor(0, 1);
  lcd.print("               ");
  delay(3000);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    lcd.setCursor(0, 1);
    lcd.print(".");
    delay(3000);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  lcd.setCursor(0, 0);
  lcd.print("connected!?    ");
  lcd.setCursor(0, 1);
  lcd.print("IP:");
  lcd.print(WiFi.localIP());
  delay(1000);

  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Firebase.setDoubleDigits(5);
  // akhir setup firebase

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
    gulaDarah = pox.getHeartRate() / 120 * 140;
    nilaiJantung = pox.getHeartRate();
    nilaispo2 = pox.getSpO2();

    Serial.print("Heart rate:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / SpO2:");
    Serial.print(pox.getSpO2());
    Serial.println("%");
    Serial.print("gulaDarah : ");
    Serial.print(gulaDarah);
    Serial.print("mg/dl");
    Serial.println();

    lcd.setCursor(0, 0);
    lcd.print("Dtk jnt: ");
    lcd.print(pox.getHeartRate());
    lcd.print("     ");

    lcd.setCursor(0, 1);
    lcd.print("spo2: ");
    lcd.print(pox.getSpO2());
    lcd.print(" ");
    lcd.print(gulaDarah);
    lcd.print("mg/dl");
    tsLastReport = milisSekarang;
  }

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    Firebase.RTDB.setFloat(&fbdo, "/gulaDarah", gulaDarah);
    Firebase.RTDB.setFloat(&fbdo, "/nilaijantung", nilaiJantung);
  }
}