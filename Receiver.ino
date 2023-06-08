/* Title: Bluetooth Receiver Code
 * Author: Aleksi Hieta
 * Date: 4/25/2023
 * Purpose: Receiver portion of two way communications between
 * remote and board for skateboard project. Utilizing a pair
 * of NRF24L01+ chips (datasheet below). Code allows for a button
 * press to be sent from both 'receiver' and 'transmitter' with a receiving 
 * LED on the opposite board.
 * Reference: Dejan Nedelkovski, www.HowToMechatronics.com
 * Datasheet: https://www.mouser.com/datasheet/2/297/nRF24L01_Product_Specification_v2_0-9199.pdf
 * Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define led 3
#define button 2

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean buttonState1 = 0;
boolean buttonState2 = 0;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(2, INPUT);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(5);
  radio.startListening();
  if(radio.available()){
    radio.read(&buttonState1, sizeof(buttonState1));
  }
  //while (!radio.available());
  if (buttonState1 == HIGH) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
  
  delay(5);
  radio.stopListening();
  buttonState2 = digitalRead(button);
  radio.write(&buttonState2, sizeof(buttonState2));
  /*
  if (buttonState2 == HIGH) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
  */
}
