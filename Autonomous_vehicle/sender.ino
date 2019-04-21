//Sender Code
#include <Wire.h>
#include <SPI.h>
#include <Pixy.h>
Pixy pixy;

int value;
void setup() {
  Wire.begin();
  pixy.init();
  Serial.begin(9600);
}

void loop() {
  static int i=0;
  int j;
  uint16_t blocks;
  
  blocks=pixy.getBlocks();
  value=0;
  if(blocks){
    
      
      for(j=0;j<blocks;j++){
        
        Serial.println(pixy.blocks[j].y);
      if(pixy.blocks[j].y>value)
       value=pixy.blocks[j].y;
      }
      }
    
    
    
    
    
Wire.beginTransmission(8); // transmit to device #8
  Wire.write(value);        // sends five bytes
  // sends one byte
  Wire.endTransmission();    // stop transmitting
  //Serial.println(value);

  delay(500);
}
