/* Title: Bluetooth Receiver Code for Skateboard
 * Author: Aleksi Hieta
 * Date: 6/7/2023
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <LiquidCrystal.h>

int Xval;
int Yval;

//Bluetooth Setup
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

//LCD Setup
LiquidCrystal lcd(10, 9, 5, 4, 3, 2);

void setup() {
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);

  //LCD setup
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");
}

void loop() {
  delay(5);
  radio.startListening();
  if(radio.available()){
    radio.read(&Xval, sizeof(Xval));
    //Xval = int(Xval/102) - 5;
    lcd.setCursor(0, 0);
    lcd.print("Connected    ");
    lcd.setCursor(0,1);
    lcd.print("X Value: " + String(Xval) + "   ");
  }
  

}
