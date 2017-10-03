/* Unit test for LED Matrix, display all mouths sequentially*/
/* Please refer to otto.h & ott_mouths.h for API usage */

#include <Otto.h>

#define OTTO_PIN_LED_DIN      7
#define OTTO_PIN_LED_CS_PIN   8
#define OTTO_PIN_LED_CLK_PIN  9

Otto myOTTO;

void setup()
{  
  Serial.begin(115200);
  
  Serial.println ("Init LED Matrix");
  /* you may change the the direction to 0, 90, 180, 270 degree depends on how you mount your hardware */
  myOTTO.initLEDMatrix(OTTO_PIN_LED_DIN, OTTO_PIN_LED_CS_PIN, OTTO_PIN_LED_CLK_PIN, MATRIX_DIR_270);

}

void loop()
{
  /* show all 31 mouths, 1 sec each */
  for (int i = 0 ; i < 31; i++)
  {
    Serial.print("mouth:");
    Serial.println(i);
    myOTTO.putMouth(i);
    delay(1000);
  } 
}

/*
  mouth definitions within Otto_mouths.h 

  #define zero          0
  #define one           1                
  #define two           2               
  #define three         3  
  #define four          4
  #define five          5  
  #define six           6 
  #define seven         7  
  #define eight         8 
  #define nine          9
  #define smile         10                  
  #define happyOpen     11  
  #define happyClosed   12  
  #define heart         13
  #define bigSurprise   14  
  #define smallSurprise 15
  #define tongueOut     16
  #define vamp1         17  
  #define vamp2         18  
  #define lineMouth     19
  #define confused      20  
  #define diagonal      21          
  #define sad           22
  #define sadOpen       23 
  #define sadClosed     24
  #define okMouth       25 
  #define xMouth        26
  #define interrogation 27
  #define thunder       28
  #define culito        29
  #define angry         30  
*/

