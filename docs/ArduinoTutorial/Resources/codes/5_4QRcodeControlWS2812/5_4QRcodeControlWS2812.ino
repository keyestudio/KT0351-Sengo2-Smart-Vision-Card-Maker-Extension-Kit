// Arduino core library
#include <Arduino.h>
// Sentry machine vision sensor library
#include <Sentry.h>
#include <Adafruit_NeoPixel.h>

#define PIN A3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

// Create an alias Sengo for the Sengo2 type to simplify subsequent usage
typedef Sengo2 Sengo;

// Communication mode (currently enabled I2C).
#define SENGO_I2C
// #define SENGO_UART  // UART serial communication solution (annotated as disabled)

// Include the corresponding library according to the selected communication mode
#ifdef SENGO_I2C
#include <Wire.h>  // Libraries required for I2C communication
#endif
#ifdef SENGO_UART
#include <SoftwareSerial.h>
#define TX_PIN 11  // Customize the TX pin
#define RX_PIN 10  // Customize the RX pin
SoftwareSerial mySerial(RX_PIN, TX_PIN);  // Create a soft serial port object
#endif

// Define the visual processing type as QR code recognition mode
#define VISION_TYPE Sengo::kVisionQrCode
Sengo sengo;  // Create a Sengo sensor object

String QCcodeStr = "";
unsigned long lastDetectionTime = 0;

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Initialization
void setup() {
  sentry_err_t err = SENTRY_OK;  // error state variable

  Serial.begin(9600);  // Initialize the serial port for debugging the output
  Serial.println("Waiting for sengo initialize...");

  // I2C initialization
#ifdef SENGO_I2C
  Wire.begin();  // Initialize the I2C bus
  // Keep trying to connect until succeed
  while (SENTRY_OK != sengo.begin(&Wire)) {
    yield();  // Give up CPU control during the waiting period
  }
#endif  // SENGO_I2C

  // UART initialization (disabled currently)
#ifdef SENGO_UART
  mySerial.begin(9600);
  while (SENTRY_OK != sengo.begin(&mySerial)) {
    yield();
  }
#endif  // SENGO_UART

  Serial.println("Sengo begin Success.");

  // Activate the QR code recognition
  err = sengo.VisionBegin(VISION_TYPE);

  // Print the initialization result
  Serial.print("sengo.VisionBegin(kVisionQrCode) ");
  if (err) {
    Serial.print("Error: 0x");
  } else {
    Serial.print("Success: 0x");
  }
  Serial.println(err, HEX);  // Print the error code in hexadecimal format

  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
}

// loop
void loop() {
  // Obtain the number of detected QR codes (kStatus is the query status)
  int obj_num = sengo.GetValue(VISION_TYPE, kStatus);
  // Read the running time
  unsigned long currentMillis = millis();

  if (obj_num) {  // If QR code is detected
    lastDetectionTime = currentMillis;
    // Obtain the text content of QR code (character string)
    QCcodeStr = sengo.GetQrCodeValue();
    Serial.print(",value=");
    Serial.println(QCcodeStr);  // Print the content of the QR code

    if (QCcodeStr == "Red") {
      colorWipe(strip.Color(255, 0, 0), 50);  // Red
    } else if (QCcodeStr == "Green") {
      colorWipe(strip.Color(0, 255, 0), 50);  // Green
    } else if (QCcodeStr == "Blue") {
      colorWipe(strip.Color(0, 0, 255), 50);  // Blue
    } else if (QCcodeStr == "Black") {
      colorWipe(strip.Color(0, 0, 0), 50);  // off
    } else if (QCcodeStr == "White") {
      colorWipe(strip.Color(255, 255, 255), 50);  // white
    }
  }
  // If the QR code is not detected within 5 seconds, turn off the WS2812
  if (currentMillis - lastDetectionTime >= 5000) {
    lastDetectionTime = currentMillis;
    colorWipe(strip.Color(0, 0, 0), 50);  // off
  }
}