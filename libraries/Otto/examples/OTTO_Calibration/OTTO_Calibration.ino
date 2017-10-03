#include <Otto.h>
#include <EEPROM.h>
#include <LBLE.h>
#include <LRemote.h>

  /*
             ----------- 
            |   O   O   |
            |-----------|
            |           |  
  RLEG ==>  ------------ <== LLEG
              ||     ||
              ||     ||
  RFOOT ==> -----    ----- <== LFOOT
           |-----    -----|
  */

#define OTTO_PIN_LLEG 15
#define OTTO_PIN_RLEG 16
#define OTTO_PIN_LFOOT 5
#define OTTO_PIN_RFOOT 11

#define OTTO_PIN_US_TRIGGER   2
#define OTTO_PIN_US_ECHO      3
#define OTTO_PIN_BUZ          4 
#define OTTO_PIN_LED_DIN      7
#define OTTO_PIN_LED_CS_PIN   8
#define OTTO_PIN_LED_CLK_PIN  9

#define OTTO_MOUTH_COUNT  31
#define OTTO_SOUND_COUNT  19

LRemoteLabel label;
LRemoteSlider slideLLEG;
LRemoteSlider sliderRLEG;
LRemoteSlider slideRLEGF;
LRemoteSlider sliderRFOOT;
LRemoteSwitch usSwitch;
LRemoteSwitch buzSwitch;
LRemoteSwitch ledSwitch;
LRemoteButton saveBtn;
LRemoteButton walkBtn;
LRemoteButton stiffBtn;
LRemoteButton homeBtn;

int trimLLEG = 0;
int trimRLEG = 0;
int trimLFOOT = 0;
int trimRFOOT = 0;
int mouthID = 0;
int soundID = 0;

Otto myOTTO;

void setup()
{  
  Serial.begin(115200);

  LRemote.setName("OTTO Cal");
  LRemote.setOrientation(RC_PORTRAIT);
  LRemote.setGrid(4, 6);

  myOTTO.initLegs(OTTO_PIN_LLEG, OTTO_PIN_RLEG, OTTO_PIN_LFOOT, OTTO_PIN_RFOOT, true);
  myOTTO.initBuzzer(OTTO_PIN_BUZ);
  myOTTO.initLEDMatrix(OTTO_PIN_LED_DIN, OTTO_PIN_LED_CS_PIN, OTTO_PIN_LED_CLK_PIN, MATRIX_DIR_270);
  myOTTO.initUltrasonic(OTTO_PIN_US_TRIGGER, OTTO_PIN_US_ECHO);
  myOTTO.getTrims(trimLLEG, trimRLEG, trimLFOOT, trimRFOOT);
  printTrim();

  myOTTO.home();

  // init LinkIt Remote UI
  slideLLEG.setText("Left Leg");
  slideLLEG.setPos(0, 0);
  slideLLEG.setSize(4, 1);
  slideLLEG.setColor(RC_ORANGE);
  slideLLEG.setValueRange(-20, 20, trimLLEG);
  LRemote.addControl(slideLLEG);
  
  sliderRLEG.setText("Right Leg");
  sliderRLEG.setPos(0, 1);
  sliderRLEG.setSize(4, 1);
  sliderRLEG.setColor(RC_ORANGE);
  sliderRLEG.setValueRange(-20, 20, trimRLEG);
  LRemote.addControl(sliderRLEG);

  slideRLEGF.setText("Left Foot");
  slideRLEGF.setPos(0, 2);
  slideRLEGF.setSize(4, 1);
  slideRLEGF.setColor(RC_ORANGE);
  slideRLEGF.setValueRange(-20, 20, trimLFOOT);
  LRemote.addControl(slideRLEGF);

  sliderRFOOT.setText("Right Foot");
  sliderRFOOT.setPos(0, 3);
  sliderRFOOT.setSize(4, 1);
  sliderRFOOT.setColor(RC_ORANGE);
  sliderRFOOT.setValueRange(-20, 20, trimRFOOT);
  LRemote.addControl(sliderRFOOT);

  usSwitch.setText("US");
  usSwitch.setPos(0, 4);
  usSwitch.setSize(1, 1);
  usSwitch.setColor(RC_ORANGE);
  LRemote.addControl(usSwitch);

  buzSwitch.setText("BUZ");
  buzSwitch.setPos(1, 4);
  buzSwitch.setSize(1, 1);
  buzSwitch.setColor(RC_ORANGE);
  LRemote.addControl(buzSwitch);

  ledSwitch.setText("LED ");
  ledSwitch.setPos(2, 4);
  ledSwitch.setSize(1, 1);
  ledSwitch.setColor(RC_ORANGE);
  LRemote.addControl(ledSwitch);

  homeBtn.setText("Home");
  homeBtn.setPos(0, 5);
  homeBtn.setSize(1, 1);
  homeBtn.setColor(RC_PINK);
  LRemote.addControl(homeBtn);

  stiffBtn.setText("Stiff");
  stiffBtn.setPos(1, 5);
  stiffBtn.setSize(1, 1);
  stiffBtn.setColor(RC_PINK);
  LRemote.addControl(stiffBtn);

  walkBtn.setText("Walk");
  walkBtn.setPos(2, 5);
  walkBtn.setSize(1, 1);
  walkBtn.setColor(RC_BLUE);
  LRemote.addControl(walkBtn);

  saveBtn.setText("Save");
  saveBtn.setPos(3, 4);
  saveBtn.setSize(1, 2);
  saveBtn.setColor(RC_GREEN);
  LRemote.addControl(saveBtn);

  LRemote.begin();

}

void loop()
{
  LRemote.process();

  // sliders to calibration the servos 
  if(slideLLEG.isValueChanged())
  {
    trimLLEG = slideLLEG.getValue();
    printTrim();
    myOTTO.setTrims(trimLLEG, trimRLEG, trimLFOOT, trimRFOOT);
    myOTTO.stiff();
  }

  if(sliderRLEG.isValueChanged())
  {
    trimRLEG = sliderRLEG.getValue();
    printTrim();
    myOTTO.setTrims(trimLLEG, trimRLEG, trimLFOOT, trimRFOOT);
    myOTTO.stiff();
  }

  if(slideRLEGF.isValueChanged())
  {
    trimLFOOT = slideRLEGF.getValue();
    printTrim();
    myOTTO.setTrims(trimLLEG, trimRLEG, trimLFOOT, trimRFOOT);
    myOTTO.stiff();
  }

  if(sliderRFOOT.isValueChanged())
  {
    trimRFOOT = sliderRFOOT.getValue();
    printTrim();
    myOTTO.setTrims(trimLLEG, trimRLEG, trimLFOOT, trimRFOOT);
    myOTTO.stiff();
  }

  // Home Button
  if(homeBtn.isValueChanged() && homeBtn.getValue())
  {
    Serial.println("Home");
    myOTTO.setRestState(false); // reset make sure the home action wiLLEG be excuted 
    myOTTO.home();
  }

  // Stiff Button
  if(stiffBtn.isValueChanged() && stiffBtn.getValue())
  {
    Serial.println("Stiff");
    myOTTO.stiff(); 
  }

  // Walk Button
  if(walkBtn.getValue())
  {
    Serial.println("Walk Test");
    myOTTO.walk(1, 1000, FORWARD);   
  }

  // Save Button 
  if (saveBtn.isValueChanged() && saveBtn.getValue())
  {
    Serial.println("Save to EEPROM");
    myOTTO.saveTrimsOnEEPROM();
  }

  // Buzzer Switch
  if(buzSwitch.getValue())
  {
    if (soundID >= OTTO_SOUND_COUNT)
    {
      soundID = 0;
    }

    Serial.print("Sing:");
    Serial.println(soundID);
    myOTTO.sing(soundID++);
    delay(500);
  }

  // LED Matrix Switch
  if (ledSwitch.isValueChanged() && !ledSwitch.getValue())
  {
    Serial.println("clear mouth");
    myOTTO.clearMouth();
  }
  else if (ledSwitch.getValue())
  {
    if (mouthID >= OTTO_MOUTH_COUNT)
    {
      mouthID = 0;
    }

    Serial.print("Mouth:");
    Serial.println(mouthID);
    myOTTO.putMouth(mouthID++);
    delay(500);    
  }

  // Ultrasonice Sensor
  if (usSwitch.getValue())
  {
    Serial.print(myOTTO.getDistance());
    Serial.println(" cm");
    delay(500);
  }

  delay(100);

}

void printTrim()
{
    Serial.print("Left Leg:");
    Serial.print(trimLLEG);

    Serial.print("  Right Leg:");
    Serial.print(trimRLEG);

    Serial.print("  Left Foot:");
    Serial.print(trimLFOOT);

    Serial.print("  Right Foot:");
    Serial.println(trimRFOOT);
}
