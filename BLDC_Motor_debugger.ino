#define HI_A 3
#define HI_B 4
#define HI_C 5

#define LO_A 9
#define LO_B 10
#define LO_C 11

#define SW1 12

byte bldc_step = 0;
unsigned int i;
unsigned long lastButtonPress = 0;
void setup() {
  //Serial.begin(9600);

  pinMode(HI_A, OUTPUT);
  pinMode(HI_B, OUTPUT);
  pinMode(HI_C, OUTPUT);

  pinMode(LO_A, OUTPUT);
  pinMode(LO_B, OUTPUT);
  pinMode(LO_C, OUTPUT);

  pinMode(SW1, INPUT_PULLUP);

  delay(2000);
}

void bldc_move(){        // BLDC motor commutation function
  switch(bldc_step){
    case 0:
      //AH_BL();
      digitalWrite(HI_A, HIGH);
      digitalWrite(LO_B, HIGH);

     
      //write low HI_B, HI_C, LO_A, LO_C
      digitalWrite(HI_B, LOW);
      digitalWrite(HI_C, LOW);
      digitalWrite(LO_A, LOW);
      digitalWrite(LO_C, LOW);
      break;
    case 1:
      //AH_CL();
      digitalWrite(HI_A, HIGH);
      digitalWrite(LO_C, HIGH);
      
      //write low HI_B, HI_C, LO_A, LO_B
      digitalWrite(HI_B, LOW);
      digitalWrite(HI_C, LOW);
      digitalWrite(LO_A, LOW);
      digitalWrite(LO_B, LOW);
      break;
    case 2:
      //BH_CL();
      digitalWrite(HI_B, HIGH);
      digitalWrite(LO_C, HIGH);
      
      //write low HI_A, HI_C, LO_A, LO_B
      digitalWrite(HI_A, LOW);
      digitalWrite(HI_C, LOW);
      digitalWrite(LO_A, LOW);
      digitalWrite(LO_B, LOW);
      break;
    case 3:
      //BH_AL();
      digitalWrite(HI_B, HIGH);
      digitalWrite(LO_A, HIGH);
     
      //write low HI_A, HI_C, LO_B, LO_C
      digitalWrite(HI_A, LOW);
      digitalWrite(HI_C, LOW);
      digitalWrite(LO_B, LOW);
      digitalWrite(LO_C, LOW);
      break;
    case 4:
      //CH_AL();
      digitalWrite(HI_C, HIGH);
      digitalWrite(LO_A, HIGH);
      
      //write low HI_A, HI_B, LO_B, LO_C
      digitalWrite(HI_A, LOW);
      digitalWrite(HI_B, LOW);
      digitalWrite(LO_B, LOW);
      digitalWrite(LO_C, LOW);
      break;
    case 5:
      //CH_BL();
      digitalWrite(HI_C, HIGH);
      digitalWrite(LO_B, HIGH);
     
      //write low HI_A, HI_B, LO_A, LO_C
      digitalWrite(HI_A, LOW);
      digitalWrite(HI_B, LOW);
      digitalWrite(LO_A, LOW);
      digitalWrite(LO_C, LOW);
      break;
  }
}

void loop() {
  /*
  //SET_PWM_DUTY(PWM_START_DUTY);    // Setup starting PWM with duty cycle = PWM_START_DUTY
  i = 5000;
  // Motor start
  while(i > 100) {
    delayMicroseconds(i);
    //Serial.println(bldc_step);
    bldc_move();
    bldc_step++;
    bldc_step %= 6;
    i = i - 20;
    delay(1000);
    */
    /*
    bldc_move();
    bldc_step++;
    bldc_step %= 6;
    i = i - 20;
    Serial.println(bldc_step);
    delay(1000);
    */
  unsigned long currentTime = millis();
  
  int btnState = digitalRead(SW1); 
  if (btnState == LOW) {
    if (currentTime - lastButtonPress > 50) {
      //Serial.println(bldc_step);
      bldc_move();
      bldc_step++;
      bldc_step %= 6;
    }
    lastButtonPress = currentTime;
  }
  delay(5);
}
