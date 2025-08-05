
// 1. LIBRARY INCLUSION

#include <ESP8266WiFi.h>

#include "ThingSpeak.h"

#include "DHT.h"

#include "MQ135.h"



// 2. CONSTANTS AND PIN DEFINITIONS

// -- WiFi and ThingSpeak Credentials

const char* WIFI_SSID = "YOUR WIFI NAME";

const char* WIFI_PASSWORD = "YOUR WIFI PASSWORD";

unsigned long CHANNEL_ID = THINGSPEAK_CHANNEL_ID; // Replace with your ThingSpeak Channel ID

const char* WRITE_API_KEY = "THINGSPEAK_WRITE_KEY"; // Replace with your ThingSpeak Write API Key



// -- Sensor Pin Assignments

#define DHT_PIN 4 // D2 on NodeMCU (GPIO4)

#define MQ135_PIN A0 // A0 on NodeMCU



// -- Sensor Type Definition

#define DHT_TYPE DHT11 // Using a DHT11 sensor



// -- MQ135 Calibration Constant

// IMPORTANT: This value MUST be found by running a calibration sketch

// after a 24-48 hour burn-in period in clean, fresh air.

const float RZERO = 76.63; // Replace with YOUR calibrated RZERO value



// -- Timing Control

const long UPLOAD_INTERVAL = 30000; // Upload data every 30 seconds (30000 ms)

unsigned long lastUploadTime = 0;



// 3. OBJECT INSTANTIATION

WiFiClient client;

DHT dht(DHT_PIN, DHT_TYPE);

MQ135 gasSensor = MQ135(MQ135_PIN);



// --- FUNCTION PROTOTYPES ---

void connectToWiFi();



void setup() {

// 4. INITIALIZATION

Serial.begin(115200); // Start serial communication for debugging


dht.begin(); // Initialize the DHT sensor


WiFi.mode(WIFI_STA); // Set ESP8266 to Wi-Fi station mode

ThingSpeak.begin(client); // Initialize ThingSpeak client



Serial.println("System Initialized. Connecting to WiFi...");

connectToWiFi();

}



void loop() {

// 5. MAIN LOOP

// Reconnect to WiFi if the connection is lost

if (WiFi.status() != WL_CONNECTED) {

connectToWiFi();

}



// Use millis() for non-blocking delay

if (millis() - lastUploadTime > UPLOAD_INTERVAL) {

// -- Read Sensor Data

float humidity = dht.readHumidity();

float temperature = dht.readTemperature(); // in Celsius



// Check if sensor readings are valid (will be NaN if read fails)

if (isnan(humidity) || isnan(temperature)) {

Serial.println("Failed to read from DHT sensor!");

return; // Skip this loop iteration if readings are invalid

}


// -- Process MQ135 Data with Correction

// The library uses its internal functions to calculate the corrected PPM

// based on the temperature and humidity values you pass to it.

float ppm = gasSensor.getCorrectedPPM(temperature, humidity);



Serial.println("--------------------");

Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" *C");

Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");

Serial.print("Air Quality (Corrected CO2 PPM): "); Serial.println(ppm);



// -- Upload Data to ThingSpeak

ThingSpeak.setField(1, temperature);

ThingSpeak.setField(2, humidity);

ThingSpeak.setField(3, ppm);



// ** FIX: Use the constants defined at the top of the code. **

// This ensures the API key is correctly treated as a string.

int httpCode = ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);


if (httpCode == 200) {

Serial.println("Channel update successful.");

} else {

Serial.println("Problem updating channel. HTTP error code " + String(httpCode));

}



lastUploadTime = millis(); // Update the last upload time

}

}



// Helper function to connect to WiFi

void connectToWiFi() {

Serial.print("Attempting to connect to SSID: ");

Serial.println(WIFI_SSID);

WiFi.begin(WIFI_SSID, WIFI_PASSWORD);



int retries = 0;

while (WiFi.status() != WL_CONNECTED && retries < 20) {

delay(500);

Serial.print(".");

retries++;

}



if (WiFi.status() == WL_CONNECTED) {

Serial.println("\nWiFi connected!");

Serial.print("IP address: ");

Serial.println(WiFi.localIP());

} else {

Serial.println("\nFailed to connect to WiFi. Will retry.");

}

}
