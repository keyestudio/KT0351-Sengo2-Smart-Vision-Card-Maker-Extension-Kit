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
#include <SoftwareSerial.h>               // Soft serial library
#define TX_PIN 11                         // Customize the TX pin
#define RX_PIN 10                         // Customize the RX pin
SoftwareSerial mySerial(RX_PIN, TX_PIN);  // Create a soft serial port object
#endif

#define ML 4
#define ML_PWM 6
#define MR 2
#define MR_PWM 5

#define BUZZER_PIN 3

int left_speed = 255;
int right_speed = 255;

int Tags = 0;

// Define the visual processing type as a machine card recognition mode
#define VISION_TYPE Sengo::kVisionCard

// Create a Sengo sensor object
Sengo sengo;

// Card type name mapping table (Index corresponding to card label values)
const char* card_classes[] = {
  "unknown",      // 0: Unknown card type
  "forward",      // 1: Forward
  "left",         // 2: Turn left
  "right",        // 3: Turn right
  "turn_around",  // 4: Turn around
  "park",         // 5: Stop
  // Note: The size of the array should match the actual number of card types
};



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
  mySerial.begin(9600);  // Initialize the soft serial port, set baud rate to 9600
  // Keep trying to connect until succeed
  while (SENTRY_OK != sengo.begin(&mySerial)) {
    yield();  // Allow other tasks to run while waiting
  }
#endif  // SENGO_UART

  Serial.println("Sengo begin Success.");  // Print the successful initialization information of the sensor

  // Activate the machine card recognition function
  err = sengo.VisionBegin(VISION_TYPE);

  // Print the initialization result of card recognition
  Serial.print("sengo.VisionBegin(kVisionCard) ");
  if (err) {
    Serial.print("Error: 0x");    // If an error occurs, print the error prefix
  } else {
    Serial.print("Success: 0x");  // If successful, print the success prefix
  }
  Serial.println(err, HEX);       // Print the error code in hexadecimal format

  pinMode(ML, OUTPUT);      //Set the left motor direction control pin to output
  pinMode(ML_PWM, OUTPUT);  //Set the left motor pwm pin to output
  pinMode(MR, OUTPUT);      //Set the right motor direction control pin to output
  pinMode(MR_PWM, OUTPUT);  //Set the left motor pwm pin to output

  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Obtain the number of detected cards (kStatus returns the total number of detected cards)
  int obj_num = sengo.GetValue(VISION_TYPE, kStatus);

  // If at least one card is detected
  if (obj_num > 0) {
    // Traverse all the detected cards
    for (int i = 1; i <= obj_num; ++i) {
      // Card label value (Corresponding to the card_classes array index)
      Tags = sengo.GetValue(VISION_TYPE, kLabel, i);
      // Print the detailed information of the card
      Serial.print("  Tags:");
      Serial.println(Tags);
    }
    switch (Tags) {
      case 1: car_forward(); break;
      case 2: car_left(); break;
      case 3: car_right(); break;
      case 4: car_back(); break;
      case 5: car_stop(); break;
      case 8: speed_40(); break;
      case 9: speed_60(); break;
      case 10: speed_80(); break;
    }
  } else {
    car_stop();
  }
  delay(200);
}

// speed is set to 40% of full speed
void speed_40() {
  buzzer_play(102);
  left_speed = 255 * 0.4;
  right_speed = 255 * 0.4;
}

// speed is set to 60% of full speed(255)
void speed_60() {
  buzzer_play(153);
  left_speed = 255 * 0.6;
  right_speed = 255 * 0.6;
}

// speed is set to 80% of full speed(255)
void speed_80() {
    buzzer_play(204);
  left_speed = 255 * 0.8;
  right_speed = 255 * 0.8;
}

void buzzer_play(int speed) {
  if (left_speed != speed) {
    // a short “beep”
    tone(BUZZER_PIN, 1000, 100);  // frequency of 1000Hz lasting 100ms
    delay(100);
    noTone(BUZZER_PIN);
  }
}

// the car moves forward
void car_forward() {
  digitalWrite(ML, LOW);
  analogWrite(ML_PWM, left_speed);
  digitalWrite(MR, LOW);
  analogWrite(MR_PWM, right_speed);
}

// the car moves backward
void car_back() {
  digitalWrite(ML, HIGH);
  analogWrite(ML_PWM, (255 - left_speed));
  digitalWrite(MR, HIGH);
  analogWrite(MR_PWM, (255 - right_speed));
}

// the car turns left
void car_left() {
  digitalWrite(ML, HIGH);
  analogWrite(ML_PWM, 127);
  digitalWrite(MR, LOW);
  analogWrite(MR_PWM, 127);
}

// the car turns right
void car_right() {
  digitalWrite(ML, LOW);
  analogWrite(ML_PWM, 127);
  digitalWrite(MR, HIGH);
  analogWrite(MR_PWM, 127);
}

// the car stops
void car_stop() {
  digitalWrite(ML, LOW);
  analogWrite(ML_PWM, 0);
  digitalWrite(MR, LOW);
  analogWrite(MR_PWM, 0);
}
