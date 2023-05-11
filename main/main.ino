/*
Version: 0.1.0
Date: 01.04.2023
Developer: Stanislaw Kirpicnikow (Ape Devil)
Remark:
*/




/* CONFIG */
#define side               0    // 0-(left) || 1-(right)
#define thumb_module        0  // 0-(buttons) || 1-(joystick+buttons) || 2-(trackball) 
#define finger_module       0   // 0-(buttons) || 1-(buttons+wheel) 
#define additional_modules  0   // 0-(none) || 1-(mouse moudule)




// import libraries
#include <Arduino.h>

#include <Preferences.h>
Preferences preferences;


#include "USB.h"

#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

#include "USBHIDMouse.h"
USBHIDMouse Mouse;


// #if additional_modules == 1 || finger_module == 1
//     #include "USBHIDMouse.h"
//     USBHIDMouse Mouse;
// #endif




//import files
#include "config.h"

#include "layer_control.h"

#include "layouts_manager.h"

#include "event.h"

#include "finger_events.h"

#include "thumb_events.h"


#if thumb_module == 1
  #include "joystick.h"
#endif


#if finger_module == 1
    #include "wheel.h"
#endif


#if additional_modules == 1
    #include "adns5050.h"
#endif







//test button
#define pI 46
int bRead;
byte t;
 
//extern String events_array[][];




void setup() {

  Config.Setup();

  layer_control.Setup();

  Buttons_Finger.Setup();

  Buttons_Thumb.Setup();



#if thumb_module == 1
  Joystick.Setup();
#endif

  

  
#if finger_module == 1
    Wheel.Setup();
#endif

#if additional_modules == 1
    adns5050.Setup();
#endif



  preferences.begin("myPrefs", false);
  layouts_manager.split(preferences.getString("layout", ""));
  preferences.end();


  Serial.begin(115200);

  USB.begin();
  Keyboard.begin();

#if additional_modules == 1 || finger_module == 1
    Mouse.begin();
#endif



  //test buton
  pinMode(pI, INPUT_PULLUP);

}//setup





void loop() {

  layouts_manager.Loop();

  Buttons_Finger.Loop();

  Buttons_Thumb.Loop();


#if thumb_module == 1
  Joystick.Loop();
#endif
  

#if finger_module == 1
    Wheel.Loop();
#endif


#if additional_modules == 1
   adns5050.Loop();
#endif  



  bRead = digitalRead(pI);
  if (bRead == 0) {

//    t = byte(Serialcomm.events_array[0][27][0]);
//    Serial.println("TEST"); 
//    Serial.println(t); 
    // Serial.println(layouts_manager.events_array[0][0]);
    // Serial.println(layouts_manager.events_array[0][0]);

    // Serial.print("h ");
    // Serial.print(layouts_manager.mouse_factor[layer_control.active_layer][0]);
    // Serial.print("     v ");
    // Serial.println(layouts_manager.mouse_factor[layer_control.active_layer][1]);    

    Serial.println("b");

    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.release(KEY_LEFT_GUI);
    // Keyboard.press(97);          // press and hold F2
    delay(1000);
    Keyboard.releaseAll();

    Serial.println("n");

    // new 
    // new
   
  //  Serial.println(layouts_manager.mouse_factor[0][1]);
  //  Serial.println(layouts_manager.mouse_factor[1][1]);    
  //  Serial.println(layouts_manager.mouse_factor[2][1]);
  //  Serial.println(layouts_manager.mouse_factor[3][1]);
  }
}
