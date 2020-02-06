#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#include <Arduino.h>

#define DEBUG   true
#define DEBUG_ALL_IRS (DEBUG & true)

#define SAMPLES 100
#define SAMPLE_FADE 0.8

#define IR_PINS_ARRAY {A0, A1, A2, A3, A4, A5}
#define IR_PINS_COUNT 6   // length of IR_PINS_ARRAY
#define IR_CALIB_PIN 2    // Add jumper between this pin and ground & press reset to callibrate
#define IR_PITCH 15       // distance between IR sensors in mm 
#define IR_CALIB_MIN    1
#define IR_CALIB_MAX    50    // TODO test with 10
#define IR_CALIB_TIME   5000    // callibration time in ms
#define IR_INVERTED false        // TODO not implemented. not intended to implement.
#define IR_NOLINE_THRESH ((IR_CALIB_MIN+IR_CALIB_MAX)/2)
#define IR_CALIB_FLAG_ADDR 10
#define IR_CALIB_VALUES_ADDR (IR_CALIB_FLAG_ADDR + 5)
#define IR_MISS_DELAY_MS 50   // go straight for this number of milliseconds, then start rotating to find line

#define CONTROL_KP          8.8
#define CONTROL_KI          0
#define CONTROL_KD          2
#define CONTROL_I_MIN       -40
#define CONTROL_I_MAX       40
#define CONTROL_SETPOINT    0

#define MOTOR_PINL1 3
#define MOTOR_PINL2 4
#define MOTOR_PINR1 6
#define MOTOR_PINR2 5


#define MAX_SPEED_R 110 // = 1.16*25
#define MAX_SPEED_L 110 

#endif
