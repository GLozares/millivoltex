//
#include "Keyboard.h"
#include "Mouse.h"
#include "Encoder.h"

#define START 4
#define BT_A 5
#define BT_B 6
#define BT_C 7
#define BT_D 8
#define FX_L 9
#define FX_R 10

int buttons[] = {START, BT_A, BT_B, BT_C, BT_D, FX_L, FX_R};

#define ENCODER_SENSITIVITY (double) 0.375
// encoder sensitivity = number of positions per rotation times 4 (24*4) / number of positions for HID report (256)
Encoder encL(3, 2), encR(1, 0);
float knob1 = 0;
float knob2 = 0;
float old_knob1 = 0;
float old_knob2 = 0;

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i <= sizeof(buttons); i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  //ENCODERS
  knob1 =  (float)(encL.read());
  knob2 = (float)encR.read();
  
  if(knob1 != old_knob1)
  {
    // if there's a difference in encoder movement from last pass, move the mouse
    if(knob1 < old_knob1)
    {
      Mouse.move(5, 0);
    }
    else
    {
      Mouse.move(-5, 0);
    }
    
  // we count the difference in the encoders, but we must not go over arduino's int limit
    if(knob1 < -255)
    {
      encL.write(0);
      old_knob1 = 0;
    }
    else if (knob1 > 255)
    {
      encL.write(0);
      old_knob1 = 0;
    }
    else
    {
      old_knob1 = knob1;
    }
  }
  
  if(knob2 != old_knob2)
  {
    if(knob2 > old_knob2)
    {
      Mouse.move(0, 5);
    }
    else
    {
      Mouse.move(0, -5);
    }
    
    if(knob2 < -255)
    {
      encR.write(0);
      old_knob2 = 0;
    }
    else if(knob2 > 255)
    {
      encR.write(0);
      old_knob2 = 0;
    }
    else
    {
      old_knob2 = knob2;
    }
  }

  //BUTTONS
  if(digitalRead(START) == LOW)
  {
    Keyboard.press(KEY_RETURN);
  }
  else
  {
    Keyboard.release(KEY_RETURN);
  }
  
  if(digitalRead(BT_A) == LOW)
  {
    Keyboard.press('a');
  }
  else
  {
    Keyboard.release('a');
  }
  
  if(digitalRead(BT_B) == LOW)
  {
    Keyboard.press('s');
  }
  else
  {
    Keyboard.release('s');
  }
  
  if(digitalRead(BT_C) == LOW)
  {
    Keyboard.press('d');
  }
  else
  {
    Keyboard.release('d');
  }
  
  if(digitalRead(BT_D) == LOW)
  {
    Keyboard.press('f');
  }
  else
  {
    Keyboard.release('f');
  }
  
  if(digitalRead(FX_L) == LOW)
  {
    Keyboard.press('z');
  }
  else
  {
    Keyboard.release('z');
  }
  
  if(digitalRead(FX_R) == LOW)
  {
    Keyboard.press('x');
  }
  else
  {
    Keyboard.release('x');
  }
}
