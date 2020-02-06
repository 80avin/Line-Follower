#ifndef LINESENSOR_HPP
#define LINESENSOR_HPP

#include "configs.hpp"

class LineSensor {
  private:
      int pitch=IR_PITCH;
      uint8_t pins[IR_PINS_COUNT]=IR_PINS_ARRAY;
      uint16_t calib_vals_min[IR_PINS_COUNT];
      uint16_t calib_vals_max[IR_PINS_COUNT];
      uint16_t irVal[IR_PINS_COUNT];
      uint16_t irValMax;
      uint8_t pin_calib=IR_CALIB_PIN;
      
  public:
      LineSensor();
      LineSensor(const uint8_t _pins[], const int& _pitch);
      bool isOnLine();
      float interpolate();
      void read();
      void oldRead();
      void readSamples();
      bool shouldCalibrate();
      void calibrate();
      void saveCalib();
      bool loadCalib();
};

#endif
