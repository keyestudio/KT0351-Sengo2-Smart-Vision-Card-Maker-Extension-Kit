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
#include <SoftwareSerial.h>
#define TX_PIN 11  // Customize the TX pin
#define RX_PIN 10  // Customize the RX pin
SoftwareSerial mySerial(RX_PIN, TX_PIN);  // Create a soft serial port object
#endif

// Define the visual processing type as 20 types of objects recognition mode
#define VISION_TYPE Sengo::kVision20Classes
Sengo sengo;  // Create a Sengo sensor object

// 20 types of objects name and label value mapping table (0 is an unknown object)
const char* classes20[] = {
    "unknown",        // 0
    "Airplane",       // 1
    "Bicycle",        // 2
    "Bird",           // 3
    "Boat",           // 4
    "Bottle",         // 5
    "Bus",            // 6
    "Car",            // 7
    "Cat",            // 8
    "Chair",          // 9
    "Cow",            // 10
    "Dining Table",   // 11
    "Dog",            // 12
    "Horse",          // 13
    "Motorbike",      // 14
    "Person",         // 15
    "Potted Plant",   // 16
    "Sheep",          // 17
    "Sofa",           // 18
    "Train",          // 19
    "TV Monitor"      // 20
};

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
#endif

    // UART initialization (disabled currently)
#ifdef SENGO_UART
    mySerial.begin(9600);
    while (SENTRY_OK != sengo.begin(&mySerial)) { 
        yield();
    }
#endif

    Serial.println("Sengo begin Success.");

    // Activate the recognition function of 20 types of objects
    err = sengo.VisionBegin(VISION_TYPE);
    
    // Print the initialization result
    Serial.print("sengo.VisionBegin(kVision20Classes) ");
    if (err) {
        Serial.print("Error: 0x");
    } else {
        Serial.print("Success: 0x");
    }
    Serial.println(err, HEX);  // Print the error code in hexadecimal format
}

// loop
void loop() {
    // Obtain the number of detected objects (kStatus is the query status)
    int obj_num = sengo.GetValue(VISION_TYPE, kStatus);
    
    if (obj_num) {  // If object is detected
        Serial.print("Totally ");
        Serial.print(obj_num);
        Serial.println(" objects");
        
 // Traverse all the detected object
        for (int i = 1; i <= obj_num; ++i) {
            // Obtain the coordinate and size of the object in the image
            int x = sengo.GetValue(VISION_TYPE, kXValue, i);  // Object upper-left coordinate x
            int y = sengo.GetValue(VISION_TYPE, kYValue, i);  // Object upper-left coordinate y
            int w = sengo.GetValue(VISION_TYPE, kWidthValue, i);  // Object width
            int h = sengo.GetValue(VISION_TYPE, kHeightValue, i);  // Object height
            int l = sengo.GetValue(VISION_TYPE, kLabel, i);  // Object label value
            
            // Print the detailed information of the object
            Serial.print("  obj");
            Serial.print(i);
            Serial.print(": ");
            Serial.print("x=");
            Serial.print(x);
            Serial.print(",y=");
            Serial.print(y);
            Serial.print(",w=");
            Serial.print(w);
            Serial.print(",h=");
            Serial.print(h);
            Serial.print(",label=");
            Serial.println(classes20[l]);  // Obtain the object name through the index
        }
    }
}