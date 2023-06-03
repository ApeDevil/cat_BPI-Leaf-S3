class EVENT {

  private:
  
    String passing_event;
    char event_component;
    
    byte pel;
    byte k;
    bool event_active[46];
    
    const char cat_function = 0xfa;
    
    const char mouse_function = 0xf0;

    



  public:


    void actuate(byte event){
      
      if (event_active[event] == false){

//        Serial.println("p");
        Serial.println(event);  
        
        passing_event = layouts_manager.events_array[layer_control.active_layer][event];

        // Serial.println(passing_event); /
        


        if (passing_event[0] == cat_function){
         Serial.println("cat");
          layer_control.switch_layer(passing_event[1]);
        }


        else if (passing_event[0] == mouse_function){
         Serial.println("mouse");
          mouse_press(passing_event[1]);
        }      


        else{
            pel = passing_event.length();
            for(k=0; k < pel; k++){ 
                event_component = passing_event[k];
                Keyboard.press(event_component); 
            }
        }  
        event_active[event] = true;
      }
    }
    
    
    
    void deactuate(byte event){
      
      if (event_active[event] == true){

//        Serial.println("r");
        
          passing_event = layouts_manager.events_array[layer_control.active_layer][event];
          
          if (passing_event[0] == cat_function){
//            Serial.println("release cat");
            //do nothing
          }
          else if (passing_event[0] == mouse_function){
            mouse_release(passing_event[1]);
          }    
          else{
            pel = passing_event.length();
            for(k=0; k < pel; k++){ 
              event_component = passing_event[k];
              Keyboard.release(event_component);
            }
          } 
          event_active[event] = false;
      }
    }



    void mouse_press(char m){

        Serial.println("mouse press");
      Serial.println(m);


        switch (m) {
          
          // #if mouse_module == true
          
          case 0xf1:
            Serial.println("left_click");
            Mouse.press(MOUSE_LEFT);
            break;
            
          case 0xf2:
            Serial.println("middle_click");
            Mouse.press(MOUSE_MIDDLE);
            break;
            
          case 0xf3:
            Serial.println("right_click");
            Mouse.press(MOUSE_RIGHT);
            break;   
            
          case 0xf4:
            Serial.println("mouse_move 1");
            Mouse.move(0, 0, 1);
            break;
            
          case 0xf5:
            Serial.println("mouse_move -1");
            Mouse.move(0, 0, -1);
            break;    

          // #endif
          
          default:
            // do nothing
            break;
        }
    }



    void mouse_release(char m){
      
        switch (m) {

          // #if mouse_module == true
          
          case 0xf1:
            Mouse.release(MOUSE_LEFT);
            break;
            
          case 0xf2:
            Mouse.release(MOUSE_MIDDLE);
            break;
            
          case 0xf3:
            Mouse.release(MOUSE_RIGHT);
            break;  
            
          // #endif
          
          default:
            // do nothing
            break;
        }
    }

  
}; // class end


EVENT Event;
