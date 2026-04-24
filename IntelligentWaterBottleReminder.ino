#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Credentials
const char* ssid = "SSID";
const char* password = "PASSWORD";
#define BOTtoken "TOKEN"
#define CHAT_ID "ID"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

const int touchPin = 15; 
const int threshold = 1100; 

// Timing and State variables
bool isFull = false;
bool reminderSent = false;
unsigned long fullStartTime = 0;
const unsigned long reminderDelay = 30000; // 30 seconds in milliseconds

void sendTelegram(String message) {
  Serial.println("Sending: " + message);
  bot.sendMessage(CHAT_ID, message, "");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  client.setInsecure();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  configTime(0, 0, "pool.ntp.org"); // Sync time for SSL
  sendTelegram("System Online. Awaiting hydration...");
}

void loop() {
  int currentVal = touchRead(touchPin);
  Serial.print("Value: "); Serial.println(currentVal);

  // 1. DETECT FILLING
  if (!isFull && currentVal < (threshold - 30)) {
    isFull = true;
    reminderSent = false;       // Reset reminder status
    fullStartTime = millis();    // Start the 30-second clock
    sendTelegram("Bottle is full! Timer started for 30 seconds.");
  }

  // 2. CHECK FOR 30-SECOND REMINDER
  if (isFull && !reminderSent) {
    if (millis() - fullStartTime >= reminderDelay) {
      sendTelegram("Hey! You haven't taken a sip in 30 seconds. Drink up! 💧");
      reminderSent = true; // Ensure it only sends once per fill
    }
  }

  // 3. DETECT EMPTYING (The "Refill" Reminder)
  if (isFull && currentVal > (threshold + 30)) {
    isFull = false;
    reminderSent = false;
    sendTelegram("Detected: Bottle is empty. Great job! Now go refill it. 🚰");
  }

  delay(1000); 
}