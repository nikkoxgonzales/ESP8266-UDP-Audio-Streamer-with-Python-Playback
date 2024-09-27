#include <Arduino.h>                  // Include Arduino core library
#include <ESP8266WiFi.h>              // Include ESP8266 WiFi library
#include <WiFiUdp.h>                  // Include WiFi UDP library
#include <I2S.h>                      // Include I2S library for audio data

// WiFi credentials
const char* ssid = "****";                // Replace with your WiFi SSID
const char* password = "*******";        // Replace with your WiFi password

WiFiUDP udp;                               // Create UDP instance
const IPAddress listener(192, 168, 15, 123); // Replace with your PC's IP address
const int listenPort = 16500;              // UDP port number for listener
const int localPort = 5005;                // Local UDP port for ESP8266

int16_t buffer[100][2];                    // Buffer to store 100 stereo samples
const float gain = 3.0;                     // Gain factor for volume adjustment

void setup() {
  Serial.begin(115200);                     // Initialize serial communication at 115200 baud

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);               // Start WiFi connection

  while (WiFi.status() != WL_CONNECTED) {   // Wait until connected
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("My IP: ");
  Serial.println(WiFi.localIP());

  // Initialize I2S in RX mode with mono input
  if (!i2s_rxtx_begin(true, false)) {      // Begin I2S RX
    Serial.println("I2S Initialization Failed"); // Print error if I2S fails
    while (1);                               // Halt execution
  }

  i2s_set_rate(16000);                      // Set I2S sampling rate to 16kHz
  Serial.println("I2S Initialization Successful");

  // Begin UDP communication
  if (udp.begin(localPort)) {               // Start UDP on localPort
    Serial.print("UDP started on local port ");
    Serial.println(localPort);
  } else {
    Serial.println("Failed to start UDP");
    while (1);                               // Halt if UDP fails to start
  }

  Serial.print("\nStart the listener on ");
  Serial.print(listener);
  Serial.print(":");
  Serial.println(listenPort);
}

void loop() {
  // Read 100 stereo samples into the buffer
  for (int i = 0; i < 100; i++) {            // Loop to read samples
    if (!i2s_read_sample(&buffer[i][0], &buffer[i][1], true)) { // Read I2S samples
      Serial.println("Failed to read I2S sample"); // Print error if read fails
      break;                                   // Exit loop on failure
    }
    // Apply gain to each sample
    buffer[i][0] = (int16_t)(buffer[i][0] * gain); // Increase left channel volume
    buffer[i][1] = (int16_t)(buffer[i][1] * gain); // Increase right channel volume
  }

  // Send buffer via UDP
  udp.beginPacket(listener, listenPort);      // Begin UDP packet to listener
  udp.write((uint8_t*)buffer, sizeof(buffer)); // Write buffer to UDP
  udp.endPacket();                            // End UDP packet
}
