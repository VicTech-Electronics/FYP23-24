#include <Keypad.h>
#include "Display.h"

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  { 'D', '#', '0', '*' },
  { 'C', '9', '8', '7' },
  { 'B', '6', '5', '4' },
  { 'A', '3', '2', '1' }
};
byte rowPins[ROWS] = { 8, 9, 10, 11 };
byte colPins[COLS] = { 12, 13, A0, A1 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char key;
String time;

char getCharKey() {
  key = keypad.getKey();
  while (!key) key = keypad.getKey();
  return key;
}

String getTime(String state) {
  lcdPrint("Time " + state + " Setting", "");
  while (true) {
    key = getCharKey();
    if (key >= '0' && key <= '9') {
      if (time.length() < 4)
        time = time + String(key);
      lcdPrint("Time Setting", time);
    } else if (key == 'D') {
      time = time.substring(0, time.length() - 1);
      lcdPrint("Time Setting", time);
    } else if (key == '*') break;
  }
  return time;
}
