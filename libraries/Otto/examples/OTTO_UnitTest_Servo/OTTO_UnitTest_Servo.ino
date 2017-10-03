/* Unit test for Servos , OTTO will walk and turn */
/* Please refer to otto.h for API usage */

#include <Otto.h>

  /*
             ----------- 
            |   O   O   |
            |-----------|
            |           |  
  RLEG ==>   ------------ <== LLEG
              ||     ||
              ||     ||
  RFOOT ==> -----    ----- <== LFOOT
           |-----    -----|
  */


/* servo pin assignment */
#define OTTO_PIN_LLEG 15
#define OTTO_PIN_RLEG 16
#define OTTO_PIN_LFOOT 5
#define OTTO_PIN_RFOOT 11

/* calibratoin the servo if it is not at it's perfect position, can be + or - */
#define OTTO_TRIM_LLEG 0
#define OTTO_TRIM_RLEG 0   
#define OTTO_TRIM_LFOOT 0
#define OTTO_TRIM_RFOOT 0

Otto myOTTO;

void setup()
{  
  Serial.begin(115200);


  // last var 
  // true : load trim value from EEPROM
  // false : need set trim value from setTrims()
  myOTTO.initLegs(OTTO_PIN_LLEG, OTTO_PIN_RLEG, OTTO_PIN_LFOOT, OTTO_PIN_RFOOT, false);
  myOTTO.setTrims(OTTO_TRIM_LLEG, OTTO_TRIM_RLEG, OTTO_TRIM_LFOOT, OTTO_TRIM_RFOOT);  

  myOTTO.home();
}

void loop()
{

  /* init position for 3 sec */
  Serial.println("home");
  myOTTO.home();
  delay(3000);

  Serial.println("Walk Forward");
  myOTTO.walk(4, 1000, FORWARD);   /* walk foward 4 steps, each step for 1 sec */

  Serial.println("Walk Backward");
  myOTTO.walk(4, 1000, BACKWARD); /* walk backward 4 steps, each step for 1 sec */

  Serial.println("Turn Left");
  myOTTO.turn(4, 2000, LEFT);     /* turn left for 4 steps, each step for 2 sec */

  Serial.println("Turn right");
  myOTTO.turn(4, 2000, RIGHT);    /* turn left for 4 steps, each step for 2 sec */

}

/* 
  movement related API, can be found in Otto.h 

  void jump(float steps=1, int T = 2000);
  void walk(float steps=4, int T=1000, int dir = FORWARD);
  void turn(float steps=4, int T=2000, int dir = LEFT);
  void bend (int steps=1, int T=1400, int dir=LEFT);
  void shakeLeg (int steps=1, int T = 2000, int dir=RIGHT);
  void updown(float steps=1, int T=1000, int h = 20);
  void swing(float steps=1, int T=1000, int h=20);
  void tiptoeSwing(float steps=1, int T=900, int h=20);
  void jitter(float steps=1, int T=500, int h=20);
  void ascendingTurn(float steps=1, int T=900, int h=20);
  void moonwalker(float steps=1, int T=900, int h=20, int dir=LEFT);
  void crusaito(float steps=1, int T=900, int h=20, int dir=FORWARD);
  void flapping(float steps=1, int T=1000, int h=20, int dir=FORWARD);
*/

