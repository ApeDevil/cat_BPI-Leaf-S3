
// code is taken form this forum: https://forum.arduino.cc/t/adns5050/67599/9

class ADNS5050  {

  private:
    //pins conections
    #define SCLK                14
    #define SDIO                13
    #define NRESET              12
    #define NCS                 11

    //stuff for adsn5050
    #define PRODUCT_ID          0x00 // should be 0x12
    #define PRODUCTID2          0x3e
    #define REVISION_ID         0x01
    #define DELTA_Y_REG         0x03
    #define DELTA_X_REG         0x04
    #define SQUAL_REG           0x05
    #define MAXIMUM_PIXEL_REG   0x08
    #define MINIMUM_PIXEL_REG   0x0a
    #define PIXEL_SUM_REG       0x09
    #define PIXEL_DATA_REG      0x0b
    #define SHUTTER_UPPER_REG   0x06
    #define SHUTTER_LOWER_REG   0x07
    #define RESET               0x3a
    #define CPI500v             0x00
    #define CPI1000v            0x01
    
    #define NUM_PIXELS          361

    byte pix[360];
    
    int y_mouse;
    int x_mouse;


      
  public:

        void Setup() {
        
          pinMode(SDIO, OUTPUT);
          pinMode(SCLK, OUTPUT);
          pinMode(NCS, OUTPUT);
        
        //  pinMode(RESET, OUTPUT);
        //  digitalWrite(RESET, LOW);
          
          sync();
          
          ADNS_write(RESET, 0x5a);
          delay(50);                // From NRESET pull high to valid motion, assuming VDD and motion is present.
        
          pinMode(NRESET,OUTPUT);
          digitalWrite(NRESET,HIGH);
        }


        
        
        void Loop() {
          //digitalWrite(RESET, LOW);
          //delay(50);
        
          y_mouse = convert(ADNS_read(DELTA_Y_REG));
          x_mouse = convert(ADNS_read(DELTA_X_REG));

//          Serial.print("h ");
//          Serial.print(y_mouse);
//            
//          Serial.print("    v ");
//          Serial.println(x_mouse);
          
          y_mouse = y_mouse * Serialcomm.mouse_factor[Cat.active_layer][0]; // Y horizontal 
          x_mouse = x_mouse * Serialcomm.mouse_factor[Cat.active_layer][1]; // X vertical

          Mouse.move(y_mouse, x_mouse);

          
//          Serial.print("h ");
//          Serial.print(y_mouse);
//            
//          Serial.print("    v ");
//          Serial.println(x_mouse);
          
        }
        
        
        
        
        
        int  convert(byte twoscomp){
          int value;
        
          twoscomp = twoscomp << 1;
        
          if (bitRead(twoscomp,7)){
            value = -128 + (twoscomp & B01111111 );
          }
          else{
            value = twoscomp;
          }
          return value;
        }
        
        
        
        
        void sync() {
          digitalWrite(NCS, LOW);
          delayMicroseconds(2);
          digitalWrite(NCS, HIGH);
        }
        
        
        
        
        
        void ADNS_write(unsigned char addr, unsigned char data) {
          char temp;
          int n;
        
          digitalWrite(NCS, LOW);//nADNSCS = 0; // select the chip
        
          temp = addr;
          digitalWrite(SCLK, LOW);//SCK = 0;          // start clock low
          pinMode(SDIO, OUTPUT);//DATA_OUT; // set data line for output
          for (n=0; n<8; n++) {
            digitalWrite(SCLK, LOW);//SCK = 0;
            pinMode(SDIO, OUTPUT);
            delayMicroseconds(1);
            if (temp & 0x80)
              digitalWrite(SDIO, HIGH);//SDOUT = 1;
            else
              digitalWrite(SDIO, LOW);//SDOUT = 0;
            temp = (temp << 1);
            digitalWrite(SCLK, HIGH);//SCK = 1;
            delayMicroseconds(1);//delayMicroseconds(1);      // short clock pulse
          }
          temp = data;
          for (n=0; n<8; n++) {
            digitalWrite(SCLK, LOW);//SCK = 0;
            delayMicroseconds(1);
            if (temp & 0x80)
              digitalWrite(SDIO, HIGH);//SDOUT = 1;
            else
              digitalWrite(SDIO, LOW);//SDOUT = 0;
            temp = (temp << 1);
            digitalWrite(SCLK, HIGH);//SCK = 1;
            delayMicroseconds(1);     // short clock pulse
          }
          delayMicroseconds(20);
          digitalWrite(NCS, HIGH);//nADNSCS = 1; // de-select the chip
        }



        
        byte ADNS_read(unsigned char addr) {
          byte temp;
          int n;
        
          digitalWrite(NCS, LOW);//nADNSCS = 0;       // select the chip
          temp = addr;
          digitalWrite(SCLK, OUTPUT); //SCK = 0;          // start clock low
          pinMode(SDIO, OUTPUT); //DATA_OUT;          // set data line for output
          for (n=0; n<8; n++) {
        
            digitalWrite(SCLK, LOW);//SCK = 0;
            pinMode(SDIO, OUTPUT); //DATA_OUT;
            if (temp & 0x80) {
              digitalWrite(SDIO, HIGH);//SDOUT = 1;
            } 
            else {
              digitalWrite(SDIO, LOW);//SDOUT = 0;
            }
            temp = (temp << 1);
            delayMicroseconds(1);
            digitalWrite(SCLK, HIGH); //SCK = 1;
            delayMicroseconds(1);     // short clock pulse
          }
          
          temp = 0; // This is a read, switch to input
          pinMode(SDIO, INPUT); //DATA_IN;
          for (n=0; n<8; n++) {   // read back the data
            digitalWrite(SCLK, LOW);
            if(digitalRead(SDIO)) {// got a '1'
              temp |= 0x1;
            }
            if( n != 7) temp = (temp << 1); // shift left
            digitalWrite(SCLK, HIGH);
          }
          
          digitalWrite(NCS, HIGH);// de-select the chip
          return temp;
        }



        
        
        void pixelGrab(){
          int grabCount = 0; 
          while( grabCount < NUM_PIXELS )
          {
            pix[grabCount] = ADNS_read(PIXEL_DATA_REG);
            grabCount++;
          }
        }
      
};//class end

ADNS5050 adns5050;
