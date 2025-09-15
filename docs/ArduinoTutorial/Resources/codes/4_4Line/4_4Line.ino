#include <Arduino.h>
#include <Sentry.h>  // Introduce the Sentry machine vision sensor library

typedef Sengo2 Sengo;  // Create an alias Sengo for the Sengo2 type to simplify subsequent usage

// Communication method (currently enabled I2C)
#define SENGO_I2C
// #define SENGO_UART   // UART alternative options (annotated)

#ifdef SENGO_I2C
#include <Wire.h>  // Libraries required for I2C communication
#endif

#ifdef SENGO_UART
#include <SoftwareSerial.h>
#define TX_PIN 11  // Customize the TX pin
#define RX_PIN 10  // Customize the RX pin
SoftwareSerial mySerial(RX_PIN, TX_PIN);  // Create a soft serial port object
#endif

#define VISION_TYPE Sengo::kVisionLine  // line detection mode
Sengo sengo;  // Create a Sengo sensor object

void setup() {
  sentry_err_t err = SENTRY_OK;  // Error status variable

  Serial.begin(9600);  // Initialize the serial port for debugging the output
  Serial.println("Waiting for sengo initialize...");

// Initialize the sensor according to the selected communication method
#ifdef SENGO_I2C
  Wire.begin();  // Initialize the I2C bus
  // Keep trying to connect until succeed
  while (SENTRY_OK != sengo.begin(&Wire)) { 
    yield();  //Allow other tasks to run while waiting
  }
#endif

#ifdef SENGO_UART
  mySerial.begin(9600);
  while (SENTRY_OK != sengo.begin(&mySerial)) { 
    yield();
  }
#endif

  Serial.println("Sengo begin Success.");
  
  // ============== Line Detection Configuration ==============
  
  /* Set the number of detection lines */
  err = sengo.VisionSetMode(VISION_TYPE, 4);  // A maximum of 5 lines can be detected
  Serial.print("sengo.VisionSetMode");
  if (err) {
    Serial.print(" Error: 0x");
  } else {
    Serial.print(" Success: 0x");
  }
  Serial.println(err, HEX);  // Output configuration result
  
  // Enable line visual recognition
  err = sengo.VisionBegin(VISION_TYPE);
  Serial.print("sengo.VisionBegin(kVisionLine) ");
  if (err) {
    Serial.print("Error: 0x");
  } else {
    Serial.print("Success: 0x");
  }
  Serial.println(err, HEX);
}

void loop() {
  // Read the number of detected lines
  int obj_num = sengo.GetValue(VISION_TYPE, kStatus);
  
  if (obj_num > 0) {  // If a line is detected
    Serial.print("Totally ");
    Serial.print(obj_num);
    Serial.println(" lines detected");
    
    // Traverse all the detected lines
    for (int i = 1; i <= obj_num; ++i) {
      // Obtain the coordinates of the line endpoints
      int x1 = sengo.GetValue(VISION_TYPE, kXValue, i);      // x-coordinate of the starting point
      int y1 = sengo.GetValue(VISION_TYPE, kYValue, i);      // y-coordinate of the starting point
      int x2 = sengo.GetValue(VISION_TYPE, kWidthValue, i);  // x-coordinate of the end point
      int y2 = sengo.GetValue(VISION_TYPE, kHeightValue, i);  // y-coordinate of the end point
      
      // Obtain the line angle (0-180 degrees)
      int degree = sengo.GetValue(VISION_TYPE, kLabel, i);
      
      // Format and output the detection results
      Serial.print("  Line #");
      Serial.print(i);
      Serial.print(": ");
      Serial.print("Start=(");
      Serial.print(x1);
      Serial.print(",");
      Serial.print(y1);
      Serial.print("), End=(");
      Serial.print(x2);
      Serial.print(",");
      Serial.print(y2);
      Serial.print("), Angle=");
      Serial.print(degree);
      Serial.println("°");
    }
  }
  
  delay(100);  // Delay appropriately to reduce the refresh rate
}