class BUTTONS_finger {

  private:

                           // u1  u2  u3  u4  u5  u6
    const byte outPin_f[6] = {42, 41, 40, 39, 38, 37}; //declaring output pins for finger buttons moudule
    
                         // j1  j2  j3  j4    
    const byte inPin_f[4] = {45, 48, 47, 21};  //declaring inputs pins for finger buttons moudule   
    
    const byte outPin_f_count = 6;
    const byte inPin_f_count = 4;
    
                            // u1  u2  u3  u4  u5  u6     
    const byte f_map[4][6] = {{42,  3, 10, 14, 99, 88},   // j1      // button layout for left side
                              { 6,  2,  9, 13, 17, 88},   // j2 
                              { 5,  1,  8, 12, 16, 19},   // j3 
                              { 4,  0,  7, 11, 15, 18}};  // j4      // case 99 will never happen


    byte fo;
    byte fi;
    byte map_index;

  public:

    void Setup(){
      for(byte j=0; j<outPin_f_count; j++){    //initialize outputpins finger module
        pinMode(outPin_f[j],OUTPUT);
        digitalWrite(outPin_f[j],HIGH);  
      }
      for(byte j=0; j<inPin_f_count; j++){     //initialize inputpins finger module
        pinMode(inPin_f[j],INPUT_PULLUP);
      }
    }

    void Loop() {
    
      for (fo=0; fo<outPin_f_count; fo++){               //looping through Outputpins and setting one at a time to LOW 
          digitalWrite(outPin_f[fo],LOW);   
                    
            for (fi=0; fi<inPin_f_count; fi++){          // looping through Inputpins and checking for the LOW
    
                map_index = f_map[fi][fo];
    
                if (digitalRead(inPin_f[fi]) == LOW){
                  
                  Serial.println(map_index);     
                  Event.actuate(map_index);  //function from events file
                }
                else {     
                  Event.deactuate(map_index);  //function from events file    
                }
            }      
        digitalWrite(outPin_f[fo],HIGH);              //setting the Outputpin back to HIGH 
      }
    }


  
}; // class end

BUTTONS_finger Buttons_Finger;
