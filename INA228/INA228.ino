/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>

int reading = 0; //note that int is 32-bit or 4-bytes on ESP-32. This is Different compared to ATMEGA328 2 bytes int

const int INA228_Addr = 64;

//register addresses
const int SOVL_Reg = 0x0C;
const int SUVL_Reg = 0x0D; 
const int BOVL_Reg = 0x0E;
const int BUVL_Reg = 0x0F;

//calculation based on examples on INA228 Datasheet
const int SOVL_Val = 0x2BC0;
const int SUVL_Val = 0xFFEC;
const int BOVL_Val = 0x44C0;
const int BUVL_Val = 0x4240;

void write_register(int Reg_Addr, int Data) {
  Wire.beginTransmission(INA228_Addr);
  Wire.write(byte(Reg_Addr));
  Wire.write(Data);      
  Wire.endTransmission();
}

void set_register(int Reg_Addr) {
  Wire.beginTransmission(INA228_Addr);
  Wire.write(byte(Reg_Addr));   
  Wire.endTransmission();
}

void read_register
int Check_Device() {
    int reading=0;
    
    if (2 <= Wire.available()) { // if two bytes were received

    reading = Wire.read();  // receive high byte (overwrites previous reading)

    reading = reading << 8;    // shift high byte to be high 8 bits

    reading |= Wire.read(); // receive low byte as lower 8 bits

}
return reading;
}

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Test");
  
  set_register(SOVL_Reg,SOVL_Val);
  set_register(SUVL_Reg,SUVL_Val);
  set_register(BOVL_Reg,BOVL_Val);
  set_register(BUVL_Reg,BUVL_Val);
}
 
void loop() {
  Wire.beginTransmission(INA228_Addr);
  Wire.write(byte(0x01));      
  Wire.endTransmission();      
  Wire.requestFrom(INA228_Addr, 2);    // request 2 bytes from slave device #112

  // step 5: receive reading from sensor

  if (2 <= Wire.available()) { // if two bytes were received

    reading = Wire.read();  // receive high byte (overwrites previous reading)

    reading = reading << 8;    // shift high byte to be high 8 bits

    reading |= Wire.read(); // receive low byte as lower 8 bits

    Serial.println(reading); 

delay(1000);
}
}
