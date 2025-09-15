#include <Arduino.h>          // Arduino core library
#include <Sentry.h>           // Sentry machine vision sensor library

// Create an alias Sengo for the Sengo2 type to simplify subsequent usage
typedef Sengo2 Sengo;

// Communication method (currently enabled I2C).
#define SENGO_I2C             
// #define SENGO_UART         // UART serial communication solution (annotated as disabled)

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

// Define the visual processing type as a machine face recognition mode
#define VISION_TYPE Sengo::kVisionFace  

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
  // The yield() function allows ESP8266/ESP32 to handle background tasks during the waiting period
  while (SENTRY_OK != sengo.begin(&Wire)) { 
    yield();  
  }
#endif  // SENGO_I2C

#ifdef SENGO_UART
  mySerial.begin(9600);    // Initialize the soft serial port with a baud rate of 9600
  // Keep trying to connect until succeed
  while (SENTRY_OK != sengo.begin(&mySerial)) { 
    yield();  
  }
#endif  // SENGO_UART

  Serial.println("Sengo begin Success.");  // Print the successful initialization information of the sensor
  
  // Activate the machine face recognition function
  err = sengo.VisionBegin(VISION_TYPE);
  
  // Print the initialization result of face recognition
  Serial.print("sengo.VisionBegin(kVisionFace) ");
  if (err) {
    Serial.print("Error: 0x");    // If an error occurs, print the error prefix
  } else {
    Serial.print("Success: 0x");  // If successful, print the success prefix
  }
  Serial.println(err, HEX);       // Print the error code in hexadecimal format
  
  // Note: There is no additional configuration here. Use the default face detection parameters
  // Optional: Set parameters such as the minimum face size and detection angle
}

void loop() {
  // Obtain the number of detected faces (kStatus returns the total number of detected faces)
  int face_count = sengo.GetValue(VISION_TYPE, kStatus);
  
  // If at least one face is detected
  if (face_count > 0) {
    // Print the total number of detected faces
    Serial.print("Totally ");
    Serial.print(face_count);
    Serial.println(" faces detected");
    
    // Traverse all the detected faces
    for (int i = 1; i <= face_count; ++i) {
      // Obtain the coordinate and size of the face in the image
      int face_x = sengo.GetValue(VISION_TYPE, kXValue, i);      // Face central coordinate x
      int face_y = sengo.GetValue(VISION_TYPE, kYValue, i);      // Face central coordinate y
      int face_width = sengo.GetValue(VISION_TYPE, kWidthValue, i);  // Face width
      int face_height = sengo.GetValue(VISION_TYPE, kHeightValue, i); // Face height
      
      // Obtain the face label (usually representing the face ID in face detection, used to track different people)
      int face_id = sengo.GetValue(VISION_TYPE, kLabel, i);
      
      // Print the detailed information of the face
      Serial.print("  Face #");
      Serial.print(i);
      Serial.print(": ");
      Serial.print("Position=(");
      Serial.print(face_x);
      Serial.print(",");
      Serial.print(face_y);
      Serial.print("), Size=");
      Serial.print(face_width);
      Serial.print("x");
      Serial.print(face_height);
      Serial.print(", ID=");
      Serial.println(face_id);
      
    }
  }
  
  delay(200);
}