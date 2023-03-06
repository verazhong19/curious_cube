// capacitive sensing includes
#include <CapacitiveSensor.h>
#define WINDOW_SIZE 5

int INDEX = 0;
int VALUE = 0;
int SUM = 0;
int READINGS[WINDOW_SIZE];
int AVERAGED = 0;
// capacitive sensing constant
CapacitiveSensor sensor = CapacitiveSensor(4,2);  // 1M resistor between pins 4 & 2, pin 2 is sensor pin


/*<------LED STRIP------>*/
#include <FastLED.h>

#define NUM_LEDS 24
#define NUM_LEDS2 4


// 24-LED strips
#define LED1_PIN 3
CRGB leds[NUM_LEDS];  // Define the array of leds

#define LED2_PIN 5
CRGB leds2[NUM_LEDS];  // Define the array of leds


// 4-LED strips
#define LED3_PIN 6
CRGB leds3[NUM_LEDS2];  // Define the array of leds

#define LED4_PIN 7
CRGB leds4[NUM_LEDS2];  // Define the array of leds

#define LED5_PIN 8
CRGB leds5[NUM_LEDS2];  // Define the array of leds

#define LED6_PIN 9
CRGB leds6[NUM_LEDS2];  // Define the array of leds

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, LED1_PIN>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LED2_PIN>(leds2, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LED3_PIN>(leds3, NUM_LEDS2);
  FastLED.addLeds<NEOPIXEL, LED4_PIN>(leds4, NUM_LEDS2);
  FastLED.addLeds<NEOPIXEL, LED5_PIN>(leds5, NUM_LEDS2);
  FastLED.addLeds<NEOPIXEL, LED6_PIN>(leds6, NUM_LEDS2);

 
}

void loop() {
  long measurement =  sensor.capacitiveSensor(30);
  SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
  VALUE = measurement;        // Read the next sensor value
  READINGS[INDEX] = VALUE;           // Add the newest reading to the window
  SUM = SUM + VALUE;                 // Add the newest reading to the sum
  INDEX = (INDEX+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

  AVERAGED = SUM / WINDOW_SIZE;      // Divide the sum of the window by the window size for the result

  // Serial.print(VALUE);
  // Serial.print(",");
  Serial.println(AVERAGED);
  // Serial.println(measurement);
  delay(10);

  int brightness = map(AVERAGED, 200, 5000, 0, 90);
  
  delay(10);

  if (brightness < 0) {
    for (int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
      leds2[i] = CRGB::Black;
    }
    for (int i=0; i<NUM_LEDS2; i++) {
      leds3[i] = CRGB::Black;
      leds4[i] = CRGB::Black;
      leds5[i] = CRGB::Black;
      leds6[i] = CRGB::Black;
    }
    FastLED.show();
  } else {
    for (int i=0; i<NUM_LEDS; i++) {
      leds[i].setRGB(brightness, brightness, brightness);
      leds2[i].setRGB(brightness, brightness, brightness);
    }
    for (int i=0; i<NUM_LEDS2; i++) {
      leds3[i].setRGB(brightness, brightness, brightness);
      leds4[i].setRGB(brightness, brightness, brightness);
      leds5[i].setRGB(brightness, brightness, brightness);
      leds6[i].setRGB(brightness, brightness, brightness);
    }
    FastLED.show();
  }
  // if (measurement > 250) {
  //   digitalWrite(13, HIGH);}
  // else{
  //   digitalWrite(13, LOW);
  // }
}
