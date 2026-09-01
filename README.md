# ESP32 Gemini AI Assistant 🤖⚡

An embedded IoT project that integrates the **ESP32 microcontroller** with the **Google Gemini API** (Gemini 1.5 Flash). This project allows users to prompt the Gemini AI model directly through the Arduino Serial Monitor over Wi-Fi and receive real-time, AI-generated responses.

---

## 🌟 Features

- **Wi-Fi Connectivity:** Connects seamlessly to standard 2.4 GHz Wi-Fi networks using `WiFi.h`.
- **HTTPS & REST API Integration:** Sends secure POST requests to Google's Generative Language API (`v1beta`).
- **Dynamic JSON Parsing:** Uses `ArduinoJson` to construct API request payloads and parse response candidates efficiently.
- **Interactive Serial Interface:** Accepts real-time terminal inputs via the Arduino Serial Monitor and streams back generated text answers.

---

## 🛠️ Hardware & Software Requirements

### Hardware
* **ESP32 Development Board** (NodeMCU ESP32, ESP32 WROOM, etc.)
* Micro-USB or USB-C Cable (for power and serial communication)

### Software / Libraries
* **Arduino IDE** (v2.x recommended)
* **ESP32 Board Support Package** for Arduino
* **ArduinoJson** library (Version 6.x recommended)

---

## 📋 Prerequisites & Setup

### 1. Get a Google Gemini API Key
1. Go to [Google AI Studio](https://aistudio.google.com/).
2. Sign in with your Google account.
3. Click on **Get API Key** and create a new key.
4. Copy the generated API key.

### 2. Configure Arduino IDE
1. Open **Arduino IDE**.
2. Go to **Tools > Board > ESP32 Arduino** and select your ESP32 board (e.g., *ESP32 Dev Module*).
3. Select the correct COM port under **Tools > Port**.
4. Open the Library Manager (**Tools > Manage Libraries** or `Ctrl+Shift+I`).
5. Search for **ArduinoJson** by Benoit Blanchon and install **v6.x**.

---

## ⚙️ Code Configuration

In the `main.ino` sketch, update the following placeholders with your actual network credentials and API key:

```cpp
// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_SSID";         // Replace with your Wi-Fi SSID
const char* password = "YOUR_WIFI_PASSWORD"; // Replace with your Wi-Fi Password

// Gemini API credentials
const char* Gemini_Token = "YOUR_GEMINI_API_KEY"; // Replace with your Gemini API key
