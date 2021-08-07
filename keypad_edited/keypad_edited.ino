/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = ; //connect to the row pinouts of the keypad
byte colPins[COLS] = ; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key=='A'){
    Serial.println(key);
  }
}

int Num_Input(){
  char key = keypad.getKey();
  if (key == '1' or key =='2' or key =='3' or key =='4' or key =='5' or key =='6' or key =='7' or key =='8' or key =='9' or key =='0'){
    int key_val = key - '0';
    
  }
}
