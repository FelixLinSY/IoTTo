/* 
  this file is modifed from https://github.com/OttoDIY
  modifed : revise interfaces to pass all pin assigment from outside
  modifed : add extra funtions (ex: getTrims(), stiff())
 */

#ifndef Otto_h
#define Otto_h

#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>

#include <US.h>
//#include <LedMatrix.h>
#include <MaxMatrix.h>
#include "Otto_mouths.h"
#include "Otto_sounds.h"
#include "Otto_gestures.h"


//-- Constants
#define FORWARD     1
#define BACKWARD    -1
#define LEFT        1
#define RIGHT       -1
#define SMALL       5
#define MEDIUM      15
#define BIG         30

class Otto
{
  public:

    // -- Constructor
    Otto();

    //-- Otto initialization
    void initLegs(int LLEG, int RLEG, int LFOOT, int RFOOT, bool load_calibration=true);
    void initBuzzer(int pin);
    void initNoiseSensor(int pin);
    void initUltrasonic(int trigger_pin, int echo_pin);
    void initLEDMatrix(int din_pin, int cs_pin, int clk_pin, int dir=MATRIX_DIR_0);

    //-- Attach & detach functions
    void attachServos();
    void detachServos();

    //-- Oscillator Trims
    void setTrims(int LLEG, int RLEG, int LFOOT, int RFOOT);
    void getTrims(int &LLEG, int &RLEG, int &LFOOT, int &RFOOT);
    void saveTrimsOnEEPROM();

    //-- Predetermined Motion Functions
    void _moveServos(int time, int  servo_target[]);
    void oscillateServos(int A[4], int O[4], int T, double phase_diff[4], float cycle);

    //-- HOME = Otto at rest position
    void home();
    bool getRestState();
    void setRestState(bool state);
    
    //--Stiff
    void stiff();

    //-- Predetermined Motion Functions
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

    //-- Sensors functions
    float getDistance(); //US sensor
    int getNoise();      //Noise Sensor

  
    //-- Mouth & Animations
    void putMouth(MouthData mouth);
    void putMouth(int predefinedIndex);
    void putAnimationMouth(unsigned long int anim, int index);
    void clearMouth();

    //-- Sounds
    void _tone (float noteFrequency, long noteDuration, int silentDuration);
    void bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
    void sing(int songName);

    //-- Gestures
    void playGesture(int gesture);

 
  private:
    
    MaxMatrix ledMatrix;
    Oscillator servo[4];
    US us;

    int servo_pins[4];
    int servo_trim[4];
    int servo_position[4];

    int pinBuzzer;
    int pinNoiseSensor;
    int ledMatrix_dir;

    unsigned long final_time;
    unsigned long partial_time;
    float increment[4];

    bool isOttoResting;
    bool isUseBuzzer;
    bool isUseNoiseSensor;
    bool isUseUltrasonic;
    bool isUseLEDMatrix;

    MatrixRotation ledOrientation;

    MouthData getMouthShape(int number);
    MouthData getAnimShape(int anim, int index);
    void _execute(int A[4], int O[4], int T, double phase_diff[4], float steps);

};

#endif


