#include <Arduino.h>
#include <Sentry.h>
#include <Adafruit_NeoPixel.h>

#define PIN A3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

typedef Sengo2 Sengo;

#define SENGO_I2C
// #define SENGO_UART

#ifdef SENGO_I2C
#include <Wire.h>
#endif
#ifdef SENGO_UART
#include <SoftwareSerial.h>
#define TX_PIN 11
#define RX_PIN 10
SoftwareSerial mySerial(RX_PIN, TX_PIN);
#endif

#define VISION_TYPE Sengo::kVisionAprilTag
Sengo sengo;


#define BUZZER_PIN 3

int left_speed = 255;
int right_speed = 255;

String gesture[3] = { "Rock", "Scissors", "Paper" };


void setup() {
  sentry_err_t err = SENTRY_OK;

  Serial.begin(9600);

  Serial.println("Waiting for sengo initialize...");
#ifdef SENGO_I2C
  Wire.begin();
  while (SENTRY_OK != sengo.begin(&Wire)) {
    yield();
  }
#endif  // SENGO_I2C
#ifdef SENGO_UART
  mySerial.begin(9600);
  while (SENTRY_OK != sengo.begin(&mySerial)) {
    yield();
  }
#endif  // SENGO_UART
  Serial.println("Sengo begin Success.");
  err = sengo.VisionSetMode(VISION_TYPE, Sengo::kVisionModeFamily16H5);
  err = sengo.VisionSetLevel(VISION_TYPE, kLevelSpeed);
  if (err) {
    Serial.print("sengo.VisionSetMode Error: 0x");
    Serial.println(err, HEX);
  }
  err = sengo.VisionBegin(VISION_TYPE);
  Serial.print("sengo.VisionBegin(kVisionAprilTag) ");
  if (err) {
    Serial.print("Error: 0x");
  } else {
    Serial.print("Success: 0x");
  }
  Serial.println(err, HEX);

  pinMode(BUZZER_PIN, OUTPUT);

  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
}

void loop() {

  int randomNumber = random(3);  // Randomly generate one of the numbers 0, 1 or 2
  int result = 0;

  int obj_num = sengo.GetValue(VISION_TYPE, kStatus);
  if (obj_num) {
    for (int i = 1; i <= obj_num; ++i) {
      int userNumber = sengo.GetValue(VISION_TYPE, kLabel, i);
      if (userNumber < 3) {
        countdown(2);
        playStartSound();
        result = (userNumber - randomNumber + 3) % 3;
        Serial.print("Robot picks:");
        Serial.print(gesture[randomNumber]);
        Serial.print("    You pick:");
        Serial.print(gesture[userNumber]);
        Serial.print("    Robot says:");
        if (result == 0) {
          Serial.println("Draw");
          drawSound();
          colorWipe(strip.Color(0, 0, 255), 50);  // blue on
        } else if (result == 1) {
          Serial.println("I win!");
          victorySound();
          colorWipe(strip.Color(0, 255, 0), 50);  // green on
        } else if (result == 2) {
          Serial.println("I lose!");
          defeatSound();
          colorWipe(strip.Color(255, 0, 0), 50);  // red on
        }
      } else {
        break;
      }
    }
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void countdown(int seconds) {
  for (int i = seconds; i > 0; i--) {
    // The ticking of the countdown
    tone(BUZZER_PIN, 800, 100);
    delay(200);
    noTone(BUZZER_PIN);

    // Interval time
    delay(800);
  }
}

void playStartSound() {
  // The sound of the game starting - Ascending scale + ending note
  tone(BUZZER_PIN, 523, 100);  // C5
  delay(120);
  tone(BUZZER_PIN, 659, 100);  // E5
  delay(120);
  tone(BUZZER_PIN, 784, 100);  // G5
  delay(120);
  tone(BUZZER_PIN, 1046, 300);  // C6 high
  delay(350);
  noTone(BUZZER_PIN);
}


void victorySound() {
  // Victory: A light and brisk rhythm (tick - tick tick)
  tone(BUZZER_PIN, 587, 150);  // D5
  delay(200);
  tone(BUZZER_PIN, 784, 100);  // G5
  delay(120);
  tone(BUZZER_PIN, 1046, 200);  // C6
  delay(250);
  noTone(BUZZER_PIN);
}

void defeatSound() {
  // Defeat: Slow double bass (beep... beep...)
  tone(BUZZER_PIN, 220, 400);  // A3
  delay(500);
  tone(BUZZER_PIN, 196, 600);  // G3
  delay(700);
  noTone(BUZZER_PIN);
}

void drawSound() {
  // Draw: Smooth trill
  for (int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, 349, 80);  // F4
    delay(100);
    tone(BUZZER_PIN, 330, 80);  // E4
    delay(100);
  }
  noTone(BUZZER_PIN);
}