class WHEEL {

  private:
  
    #define encoder_a 35    //a2
    #define encoder_b 36    //a1
    #define encoder_GND 0   //a3
    
    #define forward_scroll 41
    #define backward_scroll 43


    byte value = 0; 
    byte previous_state;  
    byte state;
    int scroll_value = 0;
    
  public:

    void Setup(){

      pinMode(encoder_GND,OUTPUT);
      digitalWrite(encoder_GND,LOW);

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
            Event.actuate(forward_scroll);
            Event.deactuate(forward_scroll);
         } 
         else {                                 //Counterclockwise
    //       LeftRight = false;
           value--;
           scroll_value = -1;
            Event.actuate(backward_scroll);
            Event.deactuate(backward_scroll);           
         }
    
         Serial.println(value);
         Serial.println(scroll_value);
         
//         Mouse.move(0, 0, scroll_value);
       
     } 
     previous_state = state;
    } 

}; // class end

WHEEL Wheel;
