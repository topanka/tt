/*==========================================================================
 * This is a minimal sketch showing the usage of TeensyStep
 *  
 * STEP Pulses on Pin 2    (can be any pin)
 * DIR  Signall on Pin 3   (can be any pin)
 * 
 * The target position is set to 1000 steps relative to the
 * current position. The move command of the controller 
 * moves the motor to the target position.  
 *  
 * Default parameters are 
 * Speed:          800 steps/s
 * Acceleration:  2500 steps/s^2
 * 
 * (slow, but good to start with since they will work on any normal stepper)
 *
 ===========================================================================*/

#include <SPI.h>
#include <AMIS30543.h>
#include <StepControl.h>


const uint8_t m1_dirPin = 3;
const uint8_t m1_stepPin = 2;
const uint8_t m1_ssPin = 9;

const uint8_t m2_dirPin = 5;
const uint8_t m2_stepPin = 4;
const uint8_t m2_ssPin = 10;

AMIS30543 m1_amis,m2_amis;
Stepper m1_stepper(m1_stepPin,m1_dirPin);         // STEP pin: 2, DIR pin: 3
Stepper m2_stepper(m2_stepPin,m2_dirPin);         // STEP pin: 2, DIR pin: 3
StepControl<> controller;    // Use default settings 

void setup()
{
  Serial.begin(115200);
  
  SPI.begin();

  
  m1_amis.init(m1_ssPin);
  delay(1);
  m1_amis.resetSettings();
  m1_amis.setCurrentMilliamps(1000);
  m1_amis.setStepMode(128);
  m1_amis.enableDriver();
  
  m2_amis.init(m2_ssPin);
  delay(1);
  m2_amis.resetSettings();
  m2_amis.setCurrentMilliamps(1000);
  m2_amis.setStepMode(128);
  m2_amis.enableDriver();
  

  m1_stepper.setMaxSpeed(30000);             // stp/s
  m2_stepper.setMaxSpeed(15000);             // stp/s
  
  m1_stepper.setAcceleration(50000);    // stp/s^2
  m2_stepper.setAcceleration(50000);    // stp/s^2
  
}

void loop() 
{
  uint16_t pos1,pos2;
  static uint16_t l_idx=0;

  m1_stepper.setTargetRel(12800);  // Set target position to 1000 steps from current position
  m2_stepper.setTargetRel(12800);  // Set target position to 1000 steps from current position
/*
  if(l_idx%2 == 0) {
    m1_stepper.setMaxSpeed(500);             // stp/s
    m1_stepper.setTargetRel(3200);  // Set target position to 1000 steps from current position
    m2_stepper.setMaxSpeed(3000);             // stp/s
    m2_stepper.setTargetRel(1600);  // Set target position to 1000 steps from current position
  } else {
    m1_stepper.setMaxSpeed(-1000);             // stp/s
    m1_stepper.setTargetRel(3200);  // Set target position to 1000 steps from current position
  }
*/  
  l_idx++;
  
//  controller.move(m2_stepper);    // Do the move
//  delay(10);
  controller.move(m1_stepper,m2_stepper);    // Do the move
//  delay(10);
  
  pos1=m1_amis.readPosition();
  pos2=m2_amis.readPosition();
  Serial.print(pos1);
  Serial.print(" ");
  Serial.println(pos2);

/*  
  pos1=m1_stepper.getPosition();
  pos2=m2_stepper.getPosition();
  Serial.print(pos1);
  Serial.print("*");
  Serial.println(pos2);
*/  

}

