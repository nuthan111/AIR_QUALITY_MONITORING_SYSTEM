#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// Wi-Fi Credentials
const char* ssid = "Sarvan's S24 Ultra"; // Your Wi-Fi SSID
const char* password = "6302238787"; // Your Wi-Fi Password

// ThingSpeak Settings
unsigned long myChannelNumber =  2701509; // Replace with your channel number
const char * myWriteAPIKey = "G1UQ6ZCN5BKTKY7D"; // Replace with your API Key

// Pin Definition
const int airQualityPin = A0; // A0 is the analog pin on ESP8266

WiFiClient client;

void setup() {
  Serial.begin(115200); // Start Serial for debugging
  delay(10);

  // Connect to Wi-Fi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  
  Serial.println("Connected to WiFi");
  ThingSpeak.begin(client); // Initialize ThingSpeak
}

void loop() {
  // Read air quality from MQ-135 sensor
  int airQuality = analogRead(airQualityPin);
  
  // Print air quality value to Serial Monitor
  Serial.print("Air Quality: ");
  Serial.println(airQuality);
  
  // Send data to ThingSpeak
  ThingSpeak.setField(1, airQuality); // Send air quality to Field 1
  
  // Write data to ThingSpeak channel
  if (ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey) == 200) {
    Serial.println("Data sent to ThingSpeak successfully");
  } else {
    Serial.println("Error sending data to ThingSpeak");
  }

  delay(20000); // Wait 20 seconds before sending next data
}
