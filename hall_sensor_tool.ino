/* Title: Hall Sensor Check Tool
 * Author: Aleksi Hieta
 * Date: 5/3/2023
 * Purpose: The 3 values A_hall, B_hall, and C_hall are connected to the
 * Hall Effect sensor on the BLDC motor to ensure functionality. Using 
 * pull-up resistors, the three values are read and printed to the serial
 * monitor. As the motor position changes, these values change. This will
 * allow for the final motor driver to know the position and optimal 
 * sequence.
 * 
*/

#define A_hall 2
#define B_hall 3
#define C_hall 4

int A_hall_value = 0;
int B_hall_value = 0;
int C_hall_value = 0;


void setup() {
  pinMode(A_hall, INPUT);
  pinMode(B_hall, INPUT);
  pinMode(C_hall, INPUT);
  Serial.begin(9600) ;
}

void loop() {
  A_hall_value = digitalRead(A_hall);
  B_hall_value = digitalRead(B_hall);
  C_hall_value = digitalRead(C_hall);

  Serial.print("A: ");
  Serial.print(A_hall_value);
  Serial.print(" B: ");
  Serial.print(B_hall_value);
  Serial.print(" C: ");
  Serial.println(C_hall_value);
}
