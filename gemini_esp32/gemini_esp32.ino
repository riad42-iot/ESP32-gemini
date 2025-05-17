#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Wi-Fi credentials
const char* ssid = "Your Wifi ssid";           // Replace with your Wi-Fi SSID
const char* password = "Your wifi password";   // Replace with your Wi-Fi password

// Gemini API credentials
const char* Gemini_Token = "Use your API key"; // Replace with your Gemini API key
const int Gemini_Max_Tokens = 100;               // Adjust as needed

String userInput = "";  // To store user input

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Prompt user for input
  Serial.println("\nAsk your question: ");
  while (!Serial.available()) {
    delay(10); // Wait for user input
  }
  userInput = Serial.readStringUntil('\n'); // Read input from Serial
  userInput.trim(); // Remove leading/trailing whitespaces
  Serial.println("\nAsking your question: " + userInput);

  // Prepare HTTPS request
  HTTPClient https;
  String url = String("https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=") + Gemini_Token;

  if (https.begin(url)) {  // Initialize connection
    https.addHeader("Content-Type", "application/json");

    // Construct JSON payload
    DynamicJsonDocument jsonDoc(512);
    JsonObject contents = jsonDoc.createNestedObject("contents");
    JsonArray parts = contents.createNestedArray("parts");
    JsonObject part = parts.createNestedObject();
    part["text"] = userInput;

    JsonObject generationConfig = jsonDoc.createNestedObject("generationConfig");
    generationConfig["maxOutputTokens"] = Gemini_Max_Tokens;

    String payload;
    serializeJson(jsonDoc, payload);

    // Send POST request
    int httpResponseCode = https.POST(payload);

    if (httpResponseCode > 0) {
      // Check for a successful response
      String response = https.getString();
      Serial.println("\nRaw Response: " + response);

      // Parse JSON response
      DynamicJsonDocument responseDoc(2048);
      DeserializationError error = deserializeJson(responseDoc, response);

      if (error) {
        Serial.println("Failed to parse response: " + String(error.c_str()));
      } else {
        // Extract answer
        const char* answer = responseDoc["candidates"][0]["content"]["parts"][0]["text"];
        Serial.println("\nHere is your Answer:\n");
        Serial.println(answer);
      }
    } else {
      Serial.printf("[HTTPS] POST failed, error: %s\n", https.errorToString(httpResponseCode).c_str());
    }

    https.end(); // End connection
  } else {
    Serial.println("[HTTPS] Unable to connect");
  }

  userInput = ""; // Clear input
  delay(10000);   // Wait before next query
}
