#include <Arduino.h>
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP


class Controller {
  private:
    float kp_, ki_, kd_;
    float i_lowerBound_, i_upperBound_;
    float i_term;
    int speedDifference;
    float errorSum;
    float lastError;
    
  public:
    Controller(float kp, float ki, float kd, float i_lowerBound, float i_upperBound);
    int calc_speedDiff(float current_position);
};

#endif
