/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>

TwoWire INA228_Wire = TwoWire(0);

int reading = 0; //note that int is 32-bit or 4-bytes on ESP-32. This is Different compared to ATMEGA328 2 bytes int

const int INA228_Addr = 64;

//register addresses
const int SOVL_Reg = 0x0C;
const int SUVL_Reg = 0x0D; 
const int BOVL_Reg = 0x0E;
const int BUVL_Reg = 0x0F;

const int VBUS_Reg = 0x04;
const int CON_Reg = 0x00;
const int ADCCON_Reg = 0x01;
const int Device_Reg = 0x3F;
const int Vendor_Reg = 0x3E;

//calculation based on examples on INA228 Datasheet
const int SOVL_Val = 0x2BC0;
const int SUVL_Val = 0xFFEC;
const int BOVL_Val = 0x44C0;
const int BUVL_Val = 0x4240;

const int Reset_Command = 0x8000;
const int Device_ID = 0x2281;
const int Vendor_ID = 0x5449;

int ADC_Config = 0xFFFA;
//seems terrible with no benefit
//int ADC_Config = 0xFFFF;

int Shunt_Val = 10;

//Write into a 2 bytes (16 bits) register
void write_16b_register(int Reg_Addr, int Data) {
  //Divide the Data per byte
  int LSB_Data= Data & 0xFF;
  int MSB_Data= Data >> 8;
  Wire.beginTransmission(INA228_Addr);
  Wire.write(byte(Reg_Addr));

  //Wire.write works by transferring the register data, byte per byte. from the Most significant one
  Wire.write(byte(MSB_Data));
  Wire.write(byte(LSB_Data));
        
  Wire.endTransmission();
}

//Set Current register
void set_register(int Reg_Addr) {
  Wire.beginTransmission(INA228_Addr);
  Wire.write(byte(Reg_Addr));   
  Wire.endTransmission();
}

//Read from a 20 bits MSB Register
int read_20b_register(int Reg_Addr) {
  set_register(Reg_Addr);
  Wire.requestFrom(INA228_Addr, 3);
  if (3 <= Wire.available()) {
    int value = Wire.read();
    value = value << 8;
    value |= Wire.read();
    value = value << 4;
    value |= Wire.read();
    return value;
}
}

//Read from a 16 bits MSB Register
int read_16b_register(int Reg_Addr) {
  set_register(Reg_Addr);
  Wire.requestFrom(INA228_Addr, 2);
  if (2 <= Wire.available()) {
    int value = Wire.read();
    value = value << 8;
    value |= Wire.read();
    return value;
}
}

//check if device at the address is actually INA228
void Check_Device() {
    int Device_Reg_Val = 0;
    int Vendor_Val = 0;
    while (true) {
      Device_Reg_Val = read_16b_register(Device_Reg);
      Vendor_Val = read_16b_register(Vendor_Reg);
      if ((Device_Reg_Val == Device_ID) && (Vendor_Val == Vendor_ID)) {
        break;
      }
      Serial.println("Error device isn't INA228");
      delay(1000);
    }
}

//Reset configuration to default
void reset_INA228(){
  write_16b_register(CON_Reg,Reset_Command);
  delay(10);
}



void setup() {
  Wire.begin();
  delay(1000);
  Serial.begin(115200);
  Check_Device();
  reset_INA228();
 
  write_16b_register(SOVL_Reg,SOVL_Val);
  write_16b_register(SUVL_Reg,SUVL_Val);
  write_16b_register(BOVL_Reg,BOVL_Val);
  write_16b_register(BUVL_Reg,BUVL_Val);
  
  write_16b_register(ADCCON_Reg,ADC_Config);
}
 
void loop() {
  //Serial.println("Reading Result");
  int VBus_value = read_20b_register(VBUS_Reg);
  Serial.println(VBus_value);
  //float Current = VBus_value*312.5/Shunt_Val/1000;
  //Serial.println(Current);
  delay(1000);
}
