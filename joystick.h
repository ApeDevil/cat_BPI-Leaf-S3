
class JOYSTICK {

  private:
  
    #define pin_jx 18  
    #define pin_jy 8
    
    int xVal;
    int yVal;
    int h1 = 2200;   // frirst event height
    int l1 = 1700;   // frirst event low
    int h2 = 4045;    //second event height
    int l2 = 50;    //second event low

    byte xl1 = 33;  //JF1
    byte xl2 = 34;  //JF2
    byte xh1 = 35;  //JB1
    byte xh2 = 36;  //JB2
    byte yl1 = 37;  //JL1
    byte yl2 = 38;  //JL2
    byte yh1 = 39;  //JR1
    byte yh2 = 40;  //JR2

//    char js = 0x30;

    
  public:

    void Setup(){
        pinMode(pin_jx, INPUT_PULLUP);     
        pinMode(pin_jy, INPUT_PULLUP);  
      } 

  
    void Loop(){
//      xVal = analogRead(pin_jx);       //read the analog value, joystick
//      yVal = analogRead(pin_jy);
//
//      Serial.print("x-");
//      Serial.print(xVal);
//      Serial.print("    y-");
//      Serial.println(yVal);  

      
      if (layouts_manager.events_array[layer_control.active_layer][32][0] == '0'){
        one_step();
//        Serial.print("one   ");
//        Serial.println(Serialcomm.events_array[Cat.active_layer][27]);
      }
      else{
        two_step();
//        Serial.print("two   ");
//        Serial.println(Serialcomm.events_array[Cat.active_layer][27]);
      }
    }
    


    void one_step(){
      xVal = analogRead(pin_jx);       //read the analog value, joystick
      yVal = analogRead(pin_jy);
//
//      Serial.print("x-");
//      Serial.print(xVal);
//      Serial.print("    y-");
//      Serial.println(yVal);   
    
      if (xVal < l1){  // x low value events
        Event.actuate(xl1);
          Serial.println("xl1");
      }
      else{
        Event.deactuate(xl1);
      }
      
      if (xVal > h1){   // x heigh value events
        Event.actuate(xh1);
          Serial.println("xh1");
      }
      else{
        Event.deactuate(xh1);
      }
    
      if (yVal < l1){   // y low value events
        Event.actuate(yl1);
          Serial.println("yl1");
      }
      else{
        Event.deactuate(yl1);
      }
      
      if (yVal > h1){   // y heigh value events
        Event.actuate(yh1);
          Serial.println("yh1");
      }
      else{
        Event.deactuate(yh1);
      }
    }



  
    void two_step(){
      xVal = analogRead(pin_jx);       //read the analog value, joystick
      yVal = analogRead(pin_jy);
//
//      Serial.print("x-");
//      Serial.print(xVal);
//      Serial.print("    y-");
//      Serial.println(yVal);   
    
      if (xVal < l1 && xVal > l2){  // x low value events
        Event.actuate(xl1);
          Serial.println("xl1");
      }
      else{
        Event.deactuate(xl1);
      }
      
      if (xVal < l2){
        Event.actuate(xl2);  
          Serial.println("xl2");
      }
      else{
        Event.deactuate(xl2);
      }
      
      if (xVal > h1 && xVal < h2){   // x heigh value events
        Event.actuate(xh1);
          Serial.println("xh1");
      }
      else{
        Event.deactuate(xh1);
      }
      
      if (xVal > h2){
        Event.actuate(xh2);
          Serial.println("xh2");
      }
      else{
        Event.deactuate(xh2);
      }
    
    
      if (yVal < l1 && yVal > l2){   // y low value events
        Event.actuate(yl1);
          Serial.println("yl1");
      }
      else{
        Event.deactuate(yl1);
      }
      
      if (yVal < l2){
        Event.actuate(yl2);   
          Serial.println("yl2");
      }
      else{
        Event.deactuate(yl2);
      }  
      
      if (yVal > h1 && yVal < h2){   // y heigh value events
        Event.actuate(yh1);
          Serial.println("yh1");
      }
      else{
        Event.deactuate(yh1);
      }
      
      if (yVal > h2){
        Event.actuate(yh2);
          Serial.println("yh2");
      }
      else{
        Event.deactuate(yh2);
      }
    }

    
};//class end

JOYSTICK Joystick;
