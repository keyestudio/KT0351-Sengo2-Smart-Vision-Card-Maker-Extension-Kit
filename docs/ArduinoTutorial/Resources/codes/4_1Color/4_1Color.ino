#include <Arduino.h>
#include <Sentry.h>  // Import the Sentry vision sensor library

typedef Sengo2 Sengo;  // Create an alias Sengo for the Sengo2 type to simplify subsequent usage

// Select the communication method (enable one by uncommenting)
#define SENGO_I2C  // I2C communication is currently enabled
// #define SENGO_UART   // Alternative option: UART serial communication

#ifdef SENGO_I2C
#include <Wire.h>  // Libraries required for I2C communication
#endif

#ifdef SENGO_UART
#include <SoftwareSerial.h>               // Soft serial port library (for non-hardware serial ports)
#define TX_PIN 11                         // Customize the TX pin
#define RX_PIN 10                         // Customize the RX pin
SoftwareSerial mySerial(RX_PIN, TX_PIN);  // Create a soft serial port object
#endif

#define VISION_TYPE Sengo::kVisionColor  // Define the type of visual algorithm (color recognition)
Sengo sengo;                             // Create a Sengo sensor object

void setup() {
  sentry_err_t err = SENTRY_OK;  // Error status variable

  Serial.begin(9600);  // Initialize the serial port for debugging the output
  Serial.println("Waiting for sengo initialize...");

  // Initialize the sensor according to the selected communication method
#ifdef SENGO_I2C
  Wire.begin();  // Initialize I2C bus
  // Keep trying to connect until done
  while (SENTRY_OK != sengo.begin(&Wire)) {
    yield();  // Allow other tasks to run while waiting
  }
#endif

#ifdef SENGO_UART
  mySerial.begin(9600);  // Initialize the soft serial port
  while (SENTRY_OK != sengo.begin(&mySerial)) {
    yield();
  }
#endif

  Serial.println("Sengo begin Success.");

  // Configure detection parameters
  int param_num = 5;                          // Set the number of detection points (1-5)
  sengo.SetParamNum(VISION_TYPE, param_num);  // Apply the number of detection points

  sentry_object_t param;  // Parametric structure
  for (size_t i = 1; i <= param_num; i++) {
    // Set the location of the detection area (horizontally and equidistant distribution)
    param.x_value = 100 * i / (param_num + 1);  // X-axis (0-100%)
    param.y_value = 50;                         // Y-axis (fixed 50%)

    // Set the size of the detection area (incrementing)
    param.width = i * 2 + 1;   // Area width (odd)
    param.height = i * 2 + 1;  // Area height (odd)

    // Write the parameters into the sensor
    err = sengo.SetParam(VISION_TYPE, &param, i);
    if (err) {  // Error handling
      Serial.print("sengo.SetParam");
      Serial.print(i);
      Serial.print(" Error: 0x");
      Serial.println(err, HEX);  // Print hexadecimal error code
      while (1)
        ;  // Infinite loop blocking (manual restart required)
    }
  }

  // Enable the visual recognition algorithm
  err = sengo.VisionBegin(VISION_TYPE);
  Serial.print("sengo.VisionBegin(kVisionColor) ");
  if (err) {
    Serial.print("Error: 0x");
  } else {
    Serial.print("Success: 0x");
  }
  Serial.println(err, HEX);  // Output the initialization result
}

void loop() {
  // Read the number of detected objects (kStatus is the acquisition status)
  int obj_num = sengo.GetValue(VISION_TYPE, kStatus);

  if (obj_num > 0) {  // If an object is detected
    Serial.print("Totally ");
    Serial.print(obj_num);
    Serial.println(" objects");

    // Traverse all the detected objects
    for (int i = 1; i <= obj_num; ++i) {
      // Obtain the label (color ID) of the i-th object
      int label = sengo.GetValue(VISION_TYPE, kLabel, i);
      Serial.print('|');
      Serial.print(label);  // Output label (such as |1|3|5|)
    }
    Serial.println("|\n");  // End mark
  }
  delay(500);  // Delay 500ms to reduce the refresh rate
}