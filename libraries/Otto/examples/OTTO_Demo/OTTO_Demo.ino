#include <Otto.h>
#include <EEPROM.h>
#include <LBLE.h>
#include <LRemote.h>

  /*
             --------------- 
            |     O   O     |
            |---------------|
  RLEG ==>  |               | <== LLEG 
             --------------- 
                ||     ||
                ||     ||
  RFOOT==>   -----     -----  <== LFOOT 
            |-----     -----|
  */

#define OTTO_PIN_LLEG 15
#define OTTO_PIN_RLEG 16
#define OTTO_PIN_LFOOT 5
#define OTTO_PIN_RFOOT 11

#define OTTO_PIN_US_TRIGGER   2
#define OTTO_PIN_US_ECHO      3
#define OTTO_PIN_BUZ          4 
#define OTTO_PIN_LED_DIN      7
#define OTTO_PIN_LED_CS       8
#define OTTO_PIN_LED_CLK      9


/* not used if OTTO already calibrated */
#define OTTO_TRIM_LLEG 0
#define OTTO_TRIM_RLEG 0   
#define OTTO_TRIM_LFOOT 0
#define OTTO_TRIM_RFOOT 0



LRemoteCircleButton home_btn;
LRemoteButton fwd_btn;
LRemoteButton bwd_btn;
LRemoteButton left_btn;
LRemoteButton right_btn;
LRemoteButton act0_btn;
LRemoteButton act1_btn;
LRemoteButton act2_btn;
LRemoteSwitch us_switch;
LRemoteButton gesture0_btn;
LRemoteButton gesture1_btn;
LRemoteButton gesture2_btn;
LRemoteButton gesture3_btn;
LRemoteButton gesture4_btn;
LRemoteButton gesture5_btn;
LRemoteButton gesture6_btn;
LRemoteButton gesture7_btn;
LRemoteButton gesture8_btn;

Otto myOTTO;

void setup()
{  
  
  Serial.begin(115200);

  myOTTO.initLegs(OTTO_PIN_LLEG, OTTO_PIN_RLEG, OTTO_PIN_LFOOT, OTTO_PIN_RFOOT, true);
  //OTTO.setTrims(OTTO_TRIM_LLEG, OTTO_TRIM_RLEG, OTTO_TRIM_LFOOT, OTTO_TRIM_RFOOT);  
  myOTTO.initUltrasonic(OTTO_PIN_US_TRIGGER, OTTO_PIN_US_ECHO);
  myOTTO.initBuzzer(OTTO_PIN_BUZ);
  myOTTO.initLEDMatrix(OTTO_PIN_LED_DIN, OTTO_PIN_LED_CS, OTTO_PIN_LED_CLK, MATRIX_DIR_270);
  
  myOTTO.home();
  myOTTO.putMouth(happyOpen);
  /* Init Remote */
  initRemoteUI();


}

void loop()
{
  // Process the incoming BLE write request
  // and translate them to control events

  LRemote.process();
 
  if(home_btn.getValue())
  {
     Serial.println("HOME");   
     myOTTO.setRestState(false); // reset make sure the home action will be excuted 
     myOTTO.home();
  }
  else if(fwd_btn.getValue())
  {
    // ultrasonice is on and detected distance < 10 cm
    if (us_switch.getValue() && myOTTO.getDistance() < 10)
    {
      myOTTO.jitter(1, 500, 20);
    }
    else
    {
      Serial.println("WALK FORWARD");    
      myOTTO.walk(1, 1000, FORWARD);     
    }
  }
  else if(bwd_btn.getValue())
  {
    Serial.println("WALK BACKWARD");    
    myOTTO.walk(1, 1000, BACKWARD);     
  } 
  else if (left_btn.getValue())
  {
    Serial.println("TURN LEFT");        
    myOTTO.turn(1, 1000, LEFT);
  }
  else if (right_btn.getValue())
  {
    Serial.println("TURN RIGHT");        
    myOTTO.turn(1, 1000, RIGHT);
  }
  else if (act0_btn.getValue())
  {
    Serial.println("JUMP");        
    myOTTO.jump(1, 2000);
  }
  else if (act1_btn.getValue())
  {
    Serial.println("JITTER");        
    myOTTO.jitter(1, 500, 20);
  }
  else if (act2_btn.getValue())
  {
    Serial.println("SWING");        
    myOTTO.swing(1, 2000, 20);
  }
  else if (gesture0_btn.getValue())
  {
    Serial.println("HAPPY");        
    myOTTO.playGesture(OttoHappy);
  }
  else if (gesture1_btn.getValue())
  {
    Serial.println("SAD");        
    myOTTO.playGesture(OttoSad);
  } 
  else if (gesture2_btn.getValue())
  {
    Serial.println("SLEEPING");        
    myOTTO.playGesture(OttoSleeping);
  }  
  else if (gesture3_btn.getValue())
  {
    Serial.println("FART");        
    myOTTO.playGesture(OttoFart);
  }
  else if (gesture4_btn.getValue())
  {
    Serial.println("CONFUSED");        
    myOTTO.playGesture(OttoConfused);
  }   
  else if (gesture5_btn.getValue())
  {
    Serial.println("LOVE");        
    myOTTO.playGesture(OttoLove);
  }  
  else if (gesture6_btn.getValue())
  {
    Serial.println("ANGRY");        
    myOTTO.playGesture(OttoAngry);
  }     
  else if (gesture7_btn.getValue())
  {
    Serial.println("WAVE");        
    myOTTO.playGesture(OttoWave);
  }   
  else if (gesture8_btn.getValue())
  {
    Serial.println("VICTORY");        
    myOTTO.playGesture(OttoVictory);
  }     
  else 
  {
    delay(100);
  }
}


void initRemoteUI()
{

  // Setup the Remote Control's UI canvas
  LRemote.setGrid(3, 10);
  LRemote.setName("OTTO");

  // Add a push button
  home_btn.setText("HOME");
  home_btn.setPos(1, 6);
  home_btn.setSize(1, 2);
  home_btn.setColor(RC_ORANGE);
  LRemote.addControl(home_btn);

  fwd_btn.setText("FORWARD");
  fwd_btn.setPos(1, 4);
  fwd_btn.setSize(1, 2);
  fwd_btn.setColor(RC_BLUE);
  LRemote.addControl(fwd_btn);

  bwd_btn.setText("BACKWARD");
  bwd_btn.setPos(1, 8);
  bwd_btn.setSize(1, 2);
  bwd_btn.setColor(RC_BLUE);
  LRemote.addControl(bwd_btn);

  left_btn.setText("LEFT");
  left_btn.setPos(0, 6);
  left_btn.setSize(1, 2);
  left_btn.setColor(RC_BLUE);
  LRemote.addControl(left_btn);

  right_btn.setText("RIGHT");
  right_btn.setPos(2, 6);
  right_btn.setSize(1, 2);
  right_btn.setColor(RC_BLUE);
  LRemote.addControl(right_btn);

  act0_btn.setText("Jump");
  act0_btn.setPos(0, 3);
  act0_btn.setSize(1, 1);
  act0_btn.setColor(RC_GREY);
  LRemote.addControl(act0_btn);

  act1_btn.setText("Jitter");
  act1_btn.setPos(1, 3);
  act1_btn.setSize(1, 1);
  act1_btn.setColor(RC_GREY);
  LRemote.addControl(act1_btn);

  act2_btn.setText("Swing");
  act2_btn.setPos(2, 3);
  act2_btn.setSize(1, 1);
  act2_btn.setColor(RC_GREY);
  LRemote.addControl(act2_btn);

  us_switch.setText("Ultrasonic");
  us_switch.setPos(2, 8);
  us_switch.setSize(1, 2);
  us_switch.setColor(RC_PINK);
  LRemote.addControl(us_switch);

  gesture0_btn.setText("Happy");
  gesture0_btn.setPos(0, 0);
  gesture0_btn.setSize(1, 1);
  gesture0_btn.setColor(RC_GREEN);
  LRemote.addControl(gesture0_btn);

  gesture1_btn.setText("Sad");
  gesture1_btn.setPos(1, 0);
  gesture1_btn.setSize(1, 1);
  gesture1_btn.setColor(RC_GREEN);
  LRemote.addControl(gesture1_btn);

  gesture2_btn.setText("Sleeping");
  gesture2_btn.setPos(2, 0);
  gesture2_btn.setSize(1, 1);
  gesture2_btn.setColor(RC_GREEN);
  LRemote.addControl(gesture2_btn);

  gesture3_btn.setText("Fart");
  gesture3_btn.setPos(0, 1);
  gesture3_btn.setSize(1, 1);
  gesture3_btn.setColor(RC_GREEN);
  LRemote.addControl(gesture3_btn);

  gesture4_btn.setText("Confused");
  gesture4_btn.setPos(1, 1);
  gesture4_btn.setSize(1, 1);
  gesture4_btn.setColor(RC_GREEN);
  LRemote.addControl(gesture4_btn);

  gesture5_btn.setText("Love");
  gesture5_btn.setPos(2, 1);
  gesture5_btn.setSize(1, 1);
  gesture5_btn.setColor(RC_GREEN);
  LRemote.addControl(gesture5_btn);

  gesture6_btn.setText("Angry");
  gesture6_btn.setPos(0, 2);
  gesture6_btn.setSize(1, 1);
  gesture6_btn.setColor(RC_GREEN);
  LRemote.addControl(gesture6_btn);

  gesture7_btn.setText("Wave");
  gesture7_btn.setPos(1, 2);
  gesture7_btn.setSize(1, 1);
  gesture7_btn.setColor(RC_GREEN);
  LRemote.addControl(gesture7_btn);

  gesture8_btn.setText("Victory");
  gesture8_btn.setPos(2, 2);
  gesture8_btn.setSize(1, 1);
  gesture8_btn.setColor(RC_GREEN);
  LRemote.addControl(gesture8_btn);


  // Start broadcasting our remote contoller
  LRemote.begin();

}
