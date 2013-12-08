/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13. 
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead(). 
 
 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground
 
 * Note: because most Arduinos have a built-in LED attached 
 to pin 13 on the board, the LED is optional.
 
 
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe
 
 This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/AnalogInput
 
 */

int sensor1Pin = A0;    // select the input pin for the potentiometer
int sensor2Pin = A1;      // select the pin for the LED

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);  
}

void loop() {
  // read the value from the sensor:
  analogReference(INTERNAL1V1);
  analogRead(sensor1Pin);
  delay(20);
  float sensor1Value = 0;
  for(int i = 0; i < 10; i++)
  {
    sensor1Value += analogRead(sensor1Pin);
    delay(10);
  }
  sensor1Value /= 10;
  sensor1Value = (1.1 * sensor1Value * 100.0) / 1023.0;
  
  analogReference(DEFAULT);
  analogRead(sensor2Pin);
  delay(20);
  float sensor2Value = 0;
  for(int i = 0; i < 10; i++)
  {
    sensor2Value += analogRead(sensor2Pin);
    delay(10);
  }
  sensor2Value /= 10;
  sensor2Value = (5.0 * sensor2Value * 100.0) / 1023.0 - 273.0; 
  // turn the ledPin on
  Serial.print("Sensor 1: ");
  Serial.print(sensor1Value);
  Serial.print(" C, Sensor 2: ");
  Serial.print(sensor2Value);
  Serial.println(" C");
  // stop the program for <sensorValue> milliseconds:
  delay(1000);          
}

