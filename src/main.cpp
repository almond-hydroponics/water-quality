/*
# This sample codes is for testing the pH meter V1.0.
 # Editor : YouYou
 # Date   : 2013.10.12
 # Ver    : 0.1
 # Product: pH meter
 # SKU    : SEN0161
*/

#include "Arduino.h"

#define SensorPin 0          //pH meter Analog output to Arduino Analog Input 0

unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;

int buf[10], temp;

void setup()
{
	pinMode(13, OUTPUT);
	Serial.begin(115200);
	Serial.println("Ready");    //Test the serial monitor
}
void loop()
{
	//Get 10 sample value from the sensor for smooth the value
	for (int i = 0; i < 10; i++) {
		buf[i] = analogRead(SensorPin);
		delay(10);
	}

	//sort the analog from small to large
	for (int i = 0; i < 9; i++) {
		for (int j = i + 1; j < 10; j++) {
			if (buf[i] > buf[j]) {
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}

	avgValue = 0;

	//take the average value of 6 center sample
	for (int i = 2; i < 8; i++)
		avgValue += buf[i];

	//convert the analog into milli volt
	float phValue = (float)avgValue * 5.0 / 1024 / 6;

	//convert the milli volt into pH value
	phValue = 3.5 * phValue;

	Serial.print("    pH:");
	Serial.print(phValue, 2);
	Serial.println(" ");
	digitalWrite(13, HIGH);
	delay(1000);
	digitalWrite(13, LOW);
}
