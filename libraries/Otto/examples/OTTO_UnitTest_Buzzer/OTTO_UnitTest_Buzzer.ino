/* Unit test for Buzzer */
/* Please refer to otto.h & ott_sounds.h for API usages */

#include <Otto.h>

#define OTTO_PIN_BUZ    4 

Otto myOTTO;

void setup()
{  
  Serial.begin(115200);
  myOTTO.initBuzzer(OTTO_PIN_BUZ);
}

void loop()
{

  /* sing all 19 songs */
  for (int i = 0 ; i < 19; i++)
  {
    Serial.print("song:");
    Serial.println(i);
    myOTTO.sing(i);
    delay(1000);
  } 
}


/* 
  song definitions within Otto_sounds.h 

  #define S_connection    0
  #define S_disconnection 1
  #define S_buttonPushed  2
  #define S_mode1         3
  #define S_mode2         4
  #define S_mode3         5
  #define S_surprise      6
  #define S_OhOoh         7
  #define S_OhOoh2        8
  #define S_cuddly        9
  #define S_sleeping      10
  #define S_happy         11
  #define S_superHappy    12
  #define S_happy_short   13
  #define S_sad           14
  #define S_confused      15
  #define S_fart1         16
  #define S_fart2         17
  #define S_fart3         18

*/


