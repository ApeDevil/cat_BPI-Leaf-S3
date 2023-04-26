class WHEEL {

  private:
  
    #define encoder_a 21  
    #define encoder_b 47 
    
    byte value = 0; 
    byte previous_state;  
    byte state;
    int scroll_value = 0;
    
  public:

    void Setup(){
      pinMode (encoder_a,INPUT_PULLUP);
      pinMode (encoder_b,INPUT_PULLUP);
      previous_state = digitalRead(encoder_a);   
      } 


    void Loop() { 
     state = digitalRead(encoder_a);
     
       if (state != previous_state){              // we use the encoder_b pin to find out which way we turning.
          
         if (digitalRead(encoder_b) != state) {   // Clockwise
           value ++;
           scroll_value = 1;
    //       LeftRight = true;
            Event.actuate(36);
            Event.deactuate(36);
         } 
         else {                                 //Counterclockwise
    //       LeftRight = false;
           value--;
           scroll_value = -1;
            Event.actuate(38);
            Event.deactuate(38);           
         }
    
         Serial.println(value);
         Serial.println(scroll_value);
         
//         Mouse.move(0, 0, scroll_value);
       
     } 
     previous_state = state;
    } 

}; // class end

WHEEL Wheel;
