//#Includes

	#include <Wire.h>
//#Defines
	#define PCF857X B00100000  	// Adresse des PCF8574 hier: PCF8574P mit allen 3 Adress-Pins nach Masse
	#define AN B00000000		// 0 on
	#define AUS B11111111 		// 1 off
		//		 |||||||^  --- Pin0 LEDRotBig
		//		 ||||||^   --- Pin1 LEDRot1
		//		 |||||^    --- Pin2 LEDRot2
		//		 ||||^     --- Pin3 LEDBlau 
		//		 |||^      --- Pin4 LEDGruenBig 
		//		 ||^       --- Pin5 LEDGruen2 
		//		 |^        --- Pin6 LEDGruen1
		//		 ^         --- Pin7 LEDOrange

	static const int LEDBlau = 3;
	static const int LEDOrange = 7;
	static const int LEDGruenBig = 4;
	static const int LEDRotBig = 0;
	static const int LEDRot1 = 1;
	static const int LEDRot2 = 2;
	static const int LEDGruen1 = 6;
	static const int LEDGruen2 = 5;
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