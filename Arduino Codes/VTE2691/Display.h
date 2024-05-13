#include <LiquidCrystal.h>
#define rs 13
#define en A0
#define d4 A1
#define d5 A2
#define d6 A3
#define d7 A4

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


void welcomeMessage(){
  lcdPrint("Welcome", "");
  delay(1000);
  lcdPrint("FETA Mbegani", "Project 2023/24");
  delay(2000);
}