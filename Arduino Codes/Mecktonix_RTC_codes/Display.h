#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Methode to Cut String
String cutString(String str, int col) {
  return str.substring(0, col);
}

// Function to simplify the printing on LCD
void lcdPrint(String str0, String str1) {
  lcd.clear();
  const int columns = 16;
  if (str0.length() > columns) str0 = cutString(str0, columns);
  if (str1.length() > columns) str1 = cutString(str1, columns);

  int pre_space0 = int((columns - str0.length()) / 2),
      pre_space1 = int((columns - str1.length()) / 2);

  lcd.setCursor(pre_space0, 0);
  lcd.print(str0);
  lcd.setCursor(pre_space1, 1);
  lcd.print(str1);
  delay(1e3);
}