//#Includes

	#include <Wire.h>
//#Defines
	#define PCF857X B00100000  // Adresse des PCF8574 hier: PCF8574P mit allen 3 Adress-Pins nach Masse
	#define AN B00000000
	#define AUS B11111111
		//		 |||||||^  --- Pin0 LEDRotBig
		//		 ||||||^   --- Pin1 LEDRot1
		//		 |||||^    --- Pin2 LEDRot2
		//		 ||||^     --- Pin3 LEDBlau 
		//		 |||^      --- Pin4 LEDGruenBig 
		//		 ||^       --- Pin5 LEDGruen2 
		//		 |^        --- Pin6 LEDGruen1
		//		 ^         --- Pin7 LEDOrange

	#define LEDBlau 
	#define LEDOrange 
	#define	LEDGruenBig 
	#define	LEDRotBig 
	#define LEDRot1 
	#define	LEDRot2 
	#define	LEDGruen1 
	#define LEDGruen2 
//Setup
	void setup(void) {
		Serial.begin(74880);
		Serial.println("SerialBegin at 74880");
		Wire.begin(); 
		Serial.print("Wire Begin to ");
		Serial.println(PCF857X);
		Wire.beginTransmission(PCF857X); 
		Wire.write(AN); 
		Wire.endTransmission();
		delay(1000);
		Wire.beginTransmission(PCF857X); 
		Wire.write(AUS);
		Wire.endTransmission(); 
	}
//loop
	void loop(void) {
		for ( int iBitCNT = 0; iBitCNT < 8 ; iBitCNT++ ) {
			LedOn(iBitCNT);
			delay(500);
		}
		for ( int iBitCNT = 0; iBitCNT < 8 ; iBitCNT++ ) {
			LedOff(iBitCNT);
			delay(500);
		}
		delay(5000);
		LedOn(5);
		delay(500);
		LedOn(3);
		delay(500);
		LedOn(7);
		delay(500);
		LedOn(0);
		delay(5000);
	}
//LED ON
byte bLed = 0xFF;  // oll off 

void LedOn(int pos){
	bLed = bLed & ~(1 << pos);
	Wire.beginTransmission(PCF857X); 
	Wire.write(bLed); 
	Wire.endTransmission();
}
//LED OFF

void LedOff(int pos){
	bLed = bLed | (1 << pos);
	Wire.beginTransmission(PCF857X); 
	Wire.write(bLed); 
	Wire.endTransmission();
}