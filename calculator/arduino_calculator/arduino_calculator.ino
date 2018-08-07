#include <LiquidCrystal.h>
#include <Keypad.h>

// lcd
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'q','0','=','/'}
};
byte rowPins[ROWS] = {52, 51, 48, 47}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {44, 43, 40, 39}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  lcd.print("calculator");

  Serial.begin(9600);

}

void loop() {

  
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }

}
