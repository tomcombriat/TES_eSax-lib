 #ifndef _BUTTON_
#define _BUTTON_

#include<Arduino.h>

/*
      Combriat 2018, 2019, 2020, 2023, 2024
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the include file for the class managing buttons (modifiers and joystick)
*/



class Button
{
  public:
    Button();
    Button(int pin, bool inverse = false, unsigned long _response_time = 20);
    bool has_been_pressed();
    bool has_been_released();
    bool has_been_long_pressed();
    bool has_been_released_after_long_press();
    bool is_pressed();
    void set_pin(int pin);
    void manual_input(bool _input);
    unsigned long get_response_time();
    unsigned long get_last_press_time();
    void reset();


    void update();

  private:
    bool previous_state;
    int pin;
    bool been_pressed, been_released, pressed=false, been_long_pressed = false, been_released_after_long_press;
    unsigned long last_event_time;
    unsigned long last_press_time;
    unsigned long response_time;
    bool manual = false;
    bool last_manual_input = true;
    bool inverse_logic;
};



#endif
