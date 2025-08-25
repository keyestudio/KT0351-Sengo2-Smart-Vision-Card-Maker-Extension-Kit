#include <Arduino.h>          // Arduino core library
#include <Sentry.h>           // Sentry machine vision sensor library

// Create an alias Sengo for the Sengo2 type to simplify subsequent usage
typedef Sengo2 Sengo;

// Communication method (currently enabled I2C).
#define SENGO_I2C             
// #define SENGO_UART          // UART serial communication solution (annotated as disabled)

// Include the corresponding library according to the selected communication mode
#ifdef SENGO_I2C
#include <Wire.h>             // Libraries required for I2C communication
#endif

#ifdef SENGO_UART
#include <SoftwareSerial.h>   // Soft serial library
#define TX_PIN 11  // Customize the TX pin
#define RX_PIN 10  // Customize the RX pin
SoftwareSerial mySerial(RX_PIN, TX_PIN);  // Create a soft serial port object
#endif

// Define the visual processing type as a machine learning mode
#define VISION_TYPE Sengo::kVisionLearning  

// Create a Sengo sensor object
Sengo sengo;

void setup() {
  sentry_err_t err = SENTRY_OK;  // Define the error state variable and initialize it to be error-free

  Serial.begin(9600);            // Initialize the serial port for debugging the output
  Serial.println("Waiting for sengo initialize...");  // Print the initialization prompt

// Initialize the sensor according to the selected communication mode
#ifdef SENGO_I2C
  Wire.begin();  // Initialize the I2C bus
  // Keep trying to connect until succeed
  while (SENTRY_OK != sengo.begin(&Wire)) { 
    yield();  // Allow other tasks to run while waiting
  }
#endif  // SENGO_I2C

#ifdef SENGO_UART
  mySerial.begin(9600);           // Initialize the soft serial port with a baud rate of 9600
  // Keep trying to connect until succeed
  while (SENTRY_OK != sengo.begin(&mySerial)) { 
    yield();  // Allow other tasks to run while waiting
  }
#endif  // SENGO_UART

  Serial.println("Sengo begin Success.");  // Print the successful initialization information of the sensor
  
  // Activate the machine learning visual recognition function
  err = sengo.VisionBegin(VISION_TYPE);
  
  // Print the initialization result of visual recognition
  Serial.print("sengo.VisionBegin(kVisionLearning) ");
  if (err) {
    Serial.print("Error: 0x");    // If an error occurs, print the error prefix
  } else {
    Serial.print("Success: 0x");  // If successful, print the success prefix
  }
  Serial.println(err, HEX);       // Print the error code in hexadecimal format
}

void loop() {
  // Obtain the number of detected objects (the kStatus parameter returns the total number of detected objects)
  int obj_num = sengo.GetValue(VISION_TYPE, kStatus);
  
  // If at least one object is detected
  if (obj_num) {
    // Print the total number of detected objects
    Serial.print("Totally ");
    Serial.print(obj_num);
    Serial.println(" objects");
    
 // Traverse all the detected objects
    for (int i = 1; i <= obj_num; ++i) {
      // Obtain the classification label of the current object (the ID defined during model training)
      int label = sengo.GetValue(VISION_TYPE, kLabel, i);
      
      // Print the object ID number and its label
      Serial.print("  obj");
      Serial.print(i);
      Serial.print(": ");
      Serial.print("label=");
      Serial.println(label);
    }
  }
  
  delay(200);
}