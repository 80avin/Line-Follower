#include <Arduino.h>
#include "LineSensor.hpp"
#include "configs.hpp"
#include "controller.hpp"
#include "motor.hpp"

// create left and right motor objects
Motor left_motor(MOTOR_PINL1, MOTOR_PINL2, false);
Motor right_motor(MOTOR_PINR1, MOTOR_PINR2, false);

// declare variables
const uint8_t ir_pins[] = IR_PINS_ARRAY;

float current_position = 0;
float speed_diff = 0;
float speed_left = 0;
float speed_right = 0;
uint16_t last_read_ms = 0;
// create IR array board object
LineSensor ir_array(ir_pins, IR_PITCH);

// create controller object
Controller ctrl(CONTROL_KP, CONTROL_KI, CONTROL_KD, CONTROL_I_MIN, CONTROL_I_MAX);

void setup() {
#if DEBUG
    Serial.begin(115200);
#endif
    if(ir_array.shouldCalibrate()){
        ir_array.calibrate();
        ir_array.saveCalib();
    }
}

void loop() {
    ir_array.read();
    if (ir_array.isOnLine()) {
        current_position = ir_array.interpolate();

#if DEBUG
        Serial.println(current_position);
#endif
        speed_diff = ctrl.calc_speedDiff(current_position);

        speed_left = constrain(MAX_SPEED_L + speed_diff, 0, 255);
        speed_right = constrain(MAX_SPEED_R - speed_diff, 0, 255);
    }
    else if(last_read_ms + IR_MISS_DELAY_MS > millis()){
        left_motor.write(MAX_SPEED_L);
        right_motor.write(MAX_SPEED_R);
        return;
    }

#if DEBUG
    Serial.print(current_position);
    Serial.print(',');
    Serial.print(speed_diff);
    Serial.print(',');
    Serial.print(speed_left);
    Serial.print(',');
    Serial.println(speed_right);
#endif
    left_motor.write(speed_left);
    right_motor.write(speed_right);
}
