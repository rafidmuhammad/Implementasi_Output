#include <TimerOne.h>

#define LED1 5
#define LED2 6

int Van_buck;
int Van_boost;
double PWM_buck;
double PWM_boost;
double Vout_buck;
double Vout_boost;
double setpoint_buck = 7;
double setpoint_boost = 10.5;
double Kp = 0.5;

/*
void sampling(void){
  Van_buck = (int) analogRead (A4);
  Van_boost = (int) analogRead (A3);
}
*/
void setup() {
  // put your setup code here, to run once:
  //Timer1.initialize(64);
  //Timer1.attachInterrupt(sampling); 
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode (A4, INPUT);
  pinMode (A3, INPUT);
  TCCR0B = TCCR0B & B11111000 | B00000010; // set timer 0 divisor to 8 for PWM frequency of  7812.50 Hz
  PWM_buck = 0;
  PWM_boost = 0;
  analogWrite (LED1, PWM_buck);
  analogWrite (LED2, PWM_boost);
  Serial.begin (9600);
  delay (1000);
}


void loop() {
  // put your main code here, to run repeatedly:
  Van_buck = (int) analogRead (A4);
  Van_boost = (int) analogRead (A3);
  analogWrite (LED1, PWM_buck);
  analogWrite (LED2, PWM_boost);
  //Serial.print (Van_buck);
  Vout_buck = 4.9 * ((double) Van_buck) * 5 / 1023;
  Vout_boost = 4.9 * ((double) Van_boost) * 5 / 1023;
  //Serial.print ("PWM buck: ");
  //Serial.print (PWM_buck);
  //Serial.print (" PWM boost: ");
  //Serial.print (PWM_boost);
  Serial.print (" Vout buck: ");
  Serial.print (Vout_buck, 5);
  Serial.print (" Vout boost: ");
  Serial.print (Vout_boost, 5);
  Serial.println (",");
  PWM_buck = PWM_buck + Kp * (setpoint_buck - Vout_buck);
  PWM_boost = PWM_boost + Kp * (setpoint_boost - Vout_boost);
  if (PWM_buck > 200){
    PWM_buck = 200;
  }
  else if (PWM_buck < 0){
    PWM_buck = 0;
  }
  if (PWM_boost > 100){
    PWM_boost = 100;
  }
  else if (PWM_boost < 0){
    PWM_boost = 0;
  }
  //delay (1000);
}
