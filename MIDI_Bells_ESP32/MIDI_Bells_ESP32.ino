//#include <HardwareSerial.h>

HardwareSerial MySerial(2);

void setup() {
  Serial.begin(115200);
  MySerial.begin(115200, SERIAL_8N1, 16, 17);
}
 
void loop() {
  if(Serial.available() > 0){
    readMIDI();
  }
}
 
void readMIDI(){
  uint8_t status = Serial.read();
  
  if(status & 0x80){ // If status byte
    uint8_t mode     = status & 0xF0;
    uint8_t channel  = status & 0x0F;
    
    if(mode == 0x90){ // Note on
      while(Serial.available() < 2){}
 
      uint8_t note     = Serial.read();
      uint8_t velocity = Serial.read();
      
      sendMoppy(6, 0, note);
    }
    else if(mode == 0x80){ // Note off
      while(Serial.available() < 2){}
 
      uint8_t note     = Serial.read();
      uint8_t velocity = Serial.read();
      
      //sendMoppy(6, 0, note);
    }
  }
}
 
void sendMoppy(uint8_t pin, uint16_t period, uint16_t note){
  MySerial.write(note);
  MySerial.write(period >> 8 & 0xFF);
  MySerial.write(period & 0xFF);
}
