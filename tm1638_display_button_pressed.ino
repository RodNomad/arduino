
#include <TM1638.h>

// Define a module on data pin 8, clock pin 9, and strobe pin 7
#define DATA_PIN 8
#define CLOCK_PIN 9
#define STROBE_PIN 7

TM1638 tm1638(DATA_PIN, CLOCK_PIN, STROBE_PIN, true, 1);

const int MAX_PRESSED_TIMES = 9;
const int BUTTON_COUNT = 8;

int pressedTimes[BUTTON_COUNT] = {0};

byte BUTTONS[BUTTON_COUNT] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
int DISPLAYS[BUTTON_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7};
int LEDS[BUTTON_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7};

int GREEN = TM1638_COLOR_RED;
int RED = TM1638_COLOR_GREEN;

boolean DOT = true;
boolean NODOT = false;

void setup() {
  Serial.begin(9600);
}

void handleButtonPress(int buttonIndex) {
  pressedTimes[buttonIndex]++;
  if (pressedTimes[buttonIndex] > MAX_PRESSED_TIMES) {
    pressedTimes[buttonIndex] = 0;
  }
  
  if (buttonIndex == 1) {
    tm1638.setDisplayDigit(pressedTimes[buttonIndex], DISPLAYS[buttonIndex], DOT);
  } else if (buttonIndex == 4) {
    tm1638.setDisplayDigit(pressedTimes[buttonIndex], DISPLAYS[buttonIndex], DOT);
  } else {
    tm1638.setDisplayDigit(pressedTimes[buttonIndex], DISPLAYS[buttonIndex], NODOT);
  }

  tm1638.setLED(RED, LEDS[buttonIndex]);
  delay(500);
  tm1638.setLED(GREEN, LEDS[buttonIndex]);
  
  String output = "Display: ";
  for (int i = 0; i < BUTTON_COUNT; i++) {
    output += String(pressedTimes[i]);
  }
  
  while (output.length() < 9) {
    output += "0";
  }

  Serial.println(output);
}

void loop() {
  byte buttons = tm1638.getButtons();

  for (int i = 0; i < BUTTON_COUNT; i++) {
    if (buttons & BUTTONS[i]) {
      handleButtonPress(i);
    }
  }
}
