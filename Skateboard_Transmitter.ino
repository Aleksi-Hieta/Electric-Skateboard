/* Title: Bluetooth Transmitter Code for Skateboard
 * Author: Aleksi Hieta
 * Date: 6/27/2023
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define Xpin A1
//#define Ypin A2

int Xval;
int Yval;

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

void setup() {
  pinMode(Xpin, INPUT);
  //pinMode(Ypin, INPUT);
  pinMode(2, INPUT);
  
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  
  //Send Data
  delay(5);
  //radio.stopListening();
  Xval = analogRead(Xpin);
  radio.write(&Xval, sizeof(Xval));


  
}
