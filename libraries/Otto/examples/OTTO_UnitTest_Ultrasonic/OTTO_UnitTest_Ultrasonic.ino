/* Unit test for Ultrasonice , will detect range and output to serial monitor */
/* Please refer to otto.h for API usage */
/* Linkit 7697's working valtage is 3V3, please use HC-SR04P (3V~5.5V) instead HC_SR04 (5V) */

#include <Otto.h>

#define OTTO_US_TRIGGER_PIN 2
#define OTTO_US_ECHO_PIN 3

Otto myOTTO;

void setup()
{  
  Serial.begin(115200);

  /* init Ultrasonice */
  myOTTO.initUltrasonic(OTTO_US_TRIGGER_PIN, OTTO_US_ECHO_PIN);
}

void loop()
{
  /* print distance to serial monitor every 0.5 sec */
  float dist = myOTTO.getDistance();
  Serial.print(dist);
  Serial.println(" cm");
  delay(500);
}


