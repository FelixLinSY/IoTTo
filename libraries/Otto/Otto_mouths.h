/* 
  this file is modifed from https://github.com/OttoDIY
  modifed : change the mouths to 8x8 matrix representation for better readbility
  modifed : add rotate funtion
 */

#ifndef Otto_mouths_h
#define Otto_mouths_h


typedef const uint8_t* MouthData;

//***********************************************************************************
//*********************************MOUTHS DEFINES************************************
//***********************************************************************************

const static uint8_t zero_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00100100,
  B00100100,
  B00100100,
  B00011000,
};

const static uint8_t one_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00001000,
  B00011000,
  B00001000,
  B00001000,
  B00011100,
};

const static uint8_t two_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00100100,
  B00001000,
  B00010000,
  B00111100,
};

const static uint8_t three_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00100100,
  B00001000,
  B00100100,
  B00011000,
};

const static uint8_t four_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00100100,
  B00100100,
  B00111100,
  B00000100,
  B00000100,
};

const static uint8_t five_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00111100,
  B00100000,
  B00111000,
  B00000100,
  B00111000,
};

const static uint8_t six_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00001000,
  B00010000,
  B00111000,
  B00100100,
  B00011000,
};

const static uint8_t seven_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00111100,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
};

const static uint8_t eight_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00100100,
  B00011000,
  B00100100,
  B00011000,
};

const static uint8_t nine_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00100100,
  B00011100,
  B00000100,
  B00011100,
};

const static uint8_t smile_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01000010,
  B00100100,
  B00011000,
  B00000000,
};

const static uint8_t happyOpen_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01111110,
  B00100100,
  B00011000,
  B00000000,
};

const static uint8_t happyClosed_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01111110,
  B00111100,
  B00000000,
  B00000000,
};

const static uint8_t heart_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00100100,
  B01011010,
  B01000010,
  B00100100,
  B00011000,
};

const static uint8_t bigSurprise_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00100100,
  B01000010,
  B00100100,
  B00011000,
};

const static uint8_t smallSurprise_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
};

const static uint8_t tongueOut_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B01111110,
  B00010010,
  B00010010,
  B00001100,
  B00000000,
};

const static uint8_t vamp1_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B01111110,
  B01011010,
  B01011010,
  B00100100,
  B00000000,
};

const static uint8_t vamp2_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B01111110,
  B01011010,
  B00100100,
  B00000000,
  B00000000,
};

const static uint8_t lineMouth_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01111110,
  B00000000,
  B00000000,
};

const static uint8_t confused_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00010000,
  B00101010,
  B01000100,
  B00000000,
};

const static uint8_t diagonal_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B01000000,
  B00100000,
  B00010000,
  B00001000,
  B00000100,
};

const static uint8_t sad_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00100100,
  B01000010,
  B00000000,
};

const static uint8_t sadOpen_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00100100,
  B01111110,
  B00000000,
};

const static uint8_t sadClosed_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00111100,
  B01100110,
  B00000000,
};

const static uint8_t okMouth_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000010,
  B00000100,
  B00101000,
  B00010000,
  B00000000,
};

const static uint8_t xMouth_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B01000010,
  B00100100,
  B00011000,
  B00100100,
  B01000010,
};

const static uint8_t interrogation_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00100100,
  B00001000,
  B00001000,
  B00001000,
};

const static uint8_t thunder_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00001000,
  B00010000,
  B00111000,
  B00010000,
  B00100000,
};

const static uint8_t culito_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01000010,
  B01011010,
  B00100100,
  B00000000,
};

const static uint8_t angry_code[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00111100,
  B01000010,
  B01000010,
  B00000000,
};


//Mouths sorted by numbers, and after, by happy to sad mouths
#define zero 			   0
#define one  				 1                
#define two     		  2               
#define three         3  
#define four          4
#define five          5  
#define six           6 
#define seven         7  
#define eight         8 
#define nine   		    9
#define smile         10                  
#define happyOpen 	  11  
#define happyClosed   12  
#define heart         13
#define bigSurprise   14  
#define smallSurprise	15
#define tongueOut 		16
#define vamp1         17  
#define vamp2         18  
#define lineMouth    	19
#define confused      20  
#define diagonal    	21          
#define sad         	22
#define sadOpen 	    23 
#define sadClosed 		24
#define okMouth       25 
#define xMouth        26
#define interrogation 27
#define thunder		    28
#define culito       	29
#define angry 				30  
               
               

#endif


