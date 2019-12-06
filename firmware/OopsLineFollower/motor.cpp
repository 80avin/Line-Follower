#include "motor.hpp"
#include <Arduino.h>
/**
 * @brief Construct a new Motor:: Motor object
 * 
 * @param _pin1 direction pin, or HIGH->fwd pin
 * @param _pin2 pwm pin, or LOW->fwd pin
 * @param _isDirType Driver is direction/pwm type
 * @param _isInverted invert the polarity
 */
Motor::Motor(int _pin1, int _pin2, bool _isDirType=true, bool _isInverted=false):
        pin1(_pin1), pin2(_pin2), isDirType(_isDirType), isInverted(_isInverted){

   // set the pin modes to outputs
   pinMode(pin1, OUTPUT);
   pinMode(pin2, OUTPUT);
}
/**
 * @brief 
 * 
 * @param _speed -255 <= _speed <= 255
 */
void Motor::write(int _speed){
  // write speed and direction to pins
  _speed = constrain(_speed, -255, 255);
  if((_speed > 0 && !isInverted) || (_speed<0 && isInverted)){
      if(isDirType){
          digitalWrite(pin1, HIGH);
          analogWrite(pin2, abs(_speed));
      }
      else{
          analogWrite(pin1, abs(_speed));
          analogWrite(pin2, 0);
      }
  }
  else{
      if(isDirType){
          digitalWrite(pin1, LOW);
          analogWrite(pin2, abs(_speed));
      }
      else{
          analogWrite(pin1, 0);
          analogWrite(pin2, abs(_speed));
      }
  }
}

void Motor::invert(){
    isInverted = !isInverted;
}