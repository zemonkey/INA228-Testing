/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>

int reading = 0;

 
void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Test");
}
 
void loop() {
  Wire.beginTransmission(64);
  Wire.write(byte(0x01));      // sets register pointer to the command register (0x00)
  Wire.endTransmission();      // stop transmitting
  Wire.requestFrom(64, 2);    // request 2 bytes from slave device #112

  // step 5: receive reading from sensor

  if (2 <= Wire.available()) { // if two bytes were received

    reading = Wire.read();  // receive high byte (overwrites previous reading)

    reading = reading << 8;    // shift high byte to be high 8 bits

    reading |= Wire.read(); // receive low byte as lower 8 bits

    Serial.println(reading); 

delay(1000);
}
}
