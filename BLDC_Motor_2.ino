/* Author: Aleksi Hieta
 * Purpose: Sensorless brushless DC (BLDC) motor control with Arduino Nano
 * 
 * Adapted: https://simple-circuit.com/
 */
 
 
#define SPEED_UP          A0          // BLDC motor speed-up button
#define SPEED_DOWN        A1          // BLDC motor speed-down button
#define PWM_MAX_DUTY      255
#define PWM_MIN_DUTY      50
#define PWM_START_DUTY    100

#define HI_A 3
#define HI_B 4
#define HI_C 5

#define LO_A 9
#define LO_B 10
#define LO_C 11

byte bldc_step = 0, motor_speed;
unsigned int i;
void setup() {

  pinMode(HI_A, OUTPUT);
  pinMode(HI_B, OUTPUT);
  pinMode(HI_C, OUTPUT);

  pinMode(LO_A, OUTPUT);
  pinMode(LO_B, OUTPUT);
  pinMode(LO_C, OUTPUT);
  
  pinMode(SPEED_UP,   INPUT_PULLUP);
  pinMode(SPEED_DOWN, INPUT_PULLUP);
}

void bldc_move(){        // BLDC motor commutation function
  switch(bldc_step){
    case 0:
      AH_BL();
      break;
    case 1:
      AH_CL();
      break;
    case 2:
      BH_CL();
      break;
    case 3:
      BH_AL();
      break;
    case 4:
      CH_AL();
      break;
    case 5:
      CH_BL();
      break;
  }
}
 
void loop() {
  SET_PWM_DUTY(PWM_START_DUTY);    // Setup starting PWM with duty cycle = PWM_START_DUTY
  i = 5000;
  // Motor start
  while(i > 100) {
    delayMicroseconds(i);
    bldc_move();
    bldc_step++;
    bldc_step %= 6;
    i = i - 20;
  }
}

void AH_BL(){
  PORTD &= ~0x28;         //00101000
  PORTD |=  0x10;         //00010000
  TCCR1A =  0;            // Turn pin 11 (OC2A) PWM ON (pin 9 & pin 10 OFF)
  TCCR2A =  0x81;         //10000001
}
void AH_CL(){
  PORTD &= ~0x30;         //00110000
  PORTD |=  0x08;         //00001000
  TCCR1A =  0;            // Turn pin 11 (OC2A) PWM ON (pin 9 & pin 10 OFF)
  TCCR2A =  0x81;         //10000001
}
void BH_CL(){
  PORTD &= ~0x30;
  PORTD |=  0x08;
  TCCR2A =  0;            // Turn pin 10 (OC1B) PWM ON (pin 9 & pin 11 OFF)
  TCCR1A =  0x21;         //
}
void BH_AL(){
  PORTD &= ~0x18;
  PORTD |=  0x20;
  TCCR2A =  0;            // Turn pin 10 (OC1B) PWM ON (pin 9 & pin 11 OFF)
  TCCR1A =  0x21;         //
}
void CH_AL(){
  PORTD &= ~0x18;
  PORTD |=  0x20;
  TCCR2A =  0;            // Turn pin 9 (OC1A) PWM ON (pin 10 & pin 11 OFF)
  TCCR1A =  0x81;         //
}
void CH_BL(){
  PORTD &= ~0x28;
  PORTD |=  0x10;
  TCCR2A =  0;            // Turn pin 9 (OC1A) PWM ON (pin 10 & pin 11 OFF)
  TCCR1A =  0x81;         //
}
 
void SET_PWM_DUTY(byte duty){
  if(duty < PWM_MIN_DUTY)
    duty  = PWM_MIN_DUTY;
  if(duty > PWM_MAX_DUTY)
    duty  = PWM_MAX_DUTY;
  OCR1A  = duty;                   // Set pin 9  PWM duty cycle
  OCR1B  = duty;                   // Set pin 10 PWM duty cycle
  OCR2A  = duty;                   // Set pin 11 PWM duty cycle
}
