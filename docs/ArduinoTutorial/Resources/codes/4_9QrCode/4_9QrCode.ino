#include <Arduino.h>          // Arduino core library
#include <Sentry.h>           // Sentry machine vision sensor library

// Create an alias Sengo for the Sengo2 type to simplify subsequent usage
typedef Sengo2 Sengo;

// Communication mode (currently enabled I2C).
#define SENGO_I2C             
// #define SENGO_UART         // UART serial communication solution (annotated as disabled)

// Include the corresponding library according to the selected communication mode
#ifdef SENGO_I2C
#include <Wire.h>             // Libraries required for I2C communication
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
}

// loop
void loop() {
    // Obtain the number of detected QR codes (kStatus is the query status)
  int obj_num = sengo.GetValue(VISION_TYPE, kStatus);
  
  if (obj_num) {  // If QR code is detected
    Serial.print("Totally ");
    Serial.print(obj_num);
    Serial.println(" objects");
    
    // Obtain the coordinate and size of QR code
    int x = sengo.GetValue(VISION_TYPE, kXValue);      // QR code upper-left coordinate x
    int y = sengo.GetValue(VISION_TYPE, kYValue);      // QR code upper-left coordinate y
    int w = sengo.GetValue(VISION_TYPE, kWidthValue);  // QR code width
    int h = sengo.GetValue(VISION_TYPE, kHeightValue); // QR code height
    
    // Obtain the text content of QR code (character string)
    char* c = sengo.GetQrCodeValue();
    
    // Print the detailed information of the QR code
    Serial.print("  obj");
    Serial.print(": ");
    Serial.print("x=");
    Serial.print(x);
    Serial.print(",y=");
    Serial.print(y);
    Serial.print(",w=");
    Serial.print(w);
    Serial.print(",h=");
    Serial.print(h);
    Serial.print(",value=");
    Serial.println(c);  // Print the content of QR code
  }
}