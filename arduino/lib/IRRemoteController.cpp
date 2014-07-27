/* 
 * File:   IRRemoteController.cpp
 * Author: wladimiiir
 * 
 * Created on July 25, 2014, 6:42 PM
 */

#include "IRRemoteController.h"

IRRemoteController::IRRemoteController(int irRecvPin)
: lcdOn(false) {
    pinMode(irRecvPin, INPUT);
    receiver = new IRrecv(irRecvPin);
    receiver->enableIRIn();
}

void IRRemoteController::setLCD(LiquidCrystal_I2C* lcd) {
    this->lcd = lcd;
}

void dump(decode_results *results) {
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  } 
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");
  } 
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  } 
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  } 
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {	
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->panasonicAddress,HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {
     Serial.print("Decoded LG: ");
  }
  else if (results->decode_type == JVC) {
     Serial.print("Decoded JVC: ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  for (int i = 0; i < count; i++) {
    if ((i % 2) == 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    } 
    else {
      Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println("");
}

void IRRemoteController::process() {
    decode_results results;
    if (receiver->decode(&results)) {
        
        long int decCode = results.value;
        switch (decCode) {
            case 16753245:
                if (lcd != NULL) {
                    lcdOn = !lcdOn;
                    if (lcdOn) {
                        lcd->on();
                    } else {
                        lcd->off();
                    }
                }
                Serial.println("On/Off");
                break;
            case 16736925:
                Serial.println("Mode");
                break;
            case 16769565:
                Serial.println("Mute");
                break;
            case 16720605:
                Serial.println("Play/Pause");
                break;
            case 16712445:
                Serial.println("Previous");
                break;
            case 16761405:
                Serial.println("Next");
                break;
            case 16769055:
                Serial.println("EQ");
                break;
            case 16754775:
                Serial.println("Minus");
                break;
            case 16748655:
                Serial.println("Plus");
                break;
            case 16750695:
                Serial.println("Loop");
                break;
            case 16756815:
                Serial.println("U/SD");
                break;
            case 16738455:
                Serial.println("0");
                break;
            case 16724175:
                Serial.println("1");
                break;
            case 16718055:
                Serial.println("2");
                break;
            case 16743045:
                Serial.println("3");
                break;
            case 16716015:
                Serial.println("4");
                break;
            case 16726215:
                Serial.println("5");
                break;
            case 16734885:
                Serial.println("6");
                break;
            case 16728765:
                Serial.println("7");
                break;
            case 16730805:
                Serial.println("8");
                break;
            case 16732845:
                Serial.println("9");
                break;
            case 4294967295:
                //pressed
                break;
            default:
                Serial.print("Uknown:");
                Serial.println(results.value, HEX);
                dump(&results);
                break;
        }
        receiver->resume(); // Receive the next value
    }
}
