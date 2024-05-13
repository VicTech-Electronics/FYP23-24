#include <LiquidCrystal.h>
uint8_t rs=A1, en=A0, d4=13, d5=12, d6=11, d7=10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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