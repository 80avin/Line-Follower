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
      
  public:
      LineSensor();
      LineSensor(const uint8_t _pins[], int _pitch);
      bool isOnLine();
      float interpolate();
      void read();
      void readSamples();
      void calibrate();
      void saveCalib();
      bool loadCalib();
};

#endif
