class BUTTONS_thumb {

  private:

    const byte outPin[3] = {6, 5, 4};         //declaring inputs and outputs tor thumb buttons moudule
    const byte inPin[4] = {7, 15, 16, 17};    
    const byte outPin_count = 3;
    const byte inPin_count = 4;
    
    const byte t_map[4][3] = {{29,  30,    25},      // thumb buttons layout tor left side
                              {28,  99,   26},
                              {24,  27,   20},
                              {23,  22,   21}};     // case 99 will never happen
    byte to;
    byte ti;
    byte map_index;


  public:

    void Setup(){
      for(byte j=0; j<outPin_count; j++){    //initialize outputpins tinger module
        pinMode(outPin[j],OUTPUT);
        digitalWrite(outPin[j],HIGH);  
      }
      for(byte j=0; j<inPin_count; j++){     //initialize inputpins tinger module
        pinMode(inPin[j],INPUT_PULLUP);
      }
    }

    void Loop() {
    
      for (to=0; to<outPin_count; to++){               //looping through Outputpins and setting one at a time to LOW 
          digitalWrite(outPin[to],LOW);   
                    
            for (ti=0; ti<inPin_count; ti++){          // looping through Inputpins and checking tor the LOW
    
                map_index = t_map[ti][to];
    
                if (digitalRead(inPin[ti]) == LOW){
                  
                  // Serial.println(map_index);     
                  Event.actuate(map_index);  //function from events.h File
                }
                else {     
                  Event.deactuate(map_index);  //function from events.h File    
                }
            }      
        digitalWrite(outPin[to],HIGH);              //setting the Outputpin back to HIGH 
      }
    }


  
}; // class end

BUTTONS_thumb Buttons_Thumb;
