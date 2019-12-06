#include "LineSensor.hpp"
#include <Arduino.h>
#include "configs.hpp"

LineSensor::LineSensor(){
    for(int i = 0; i < IR_PINS_COUNT; i++) {
        pinMode(pins[i], INPUT);
    }
    irValMax=IR_CALIB_MIN;
}

LineSensor::LineSensor(const uint8_t _pins[], int _pitch):pitch(_pitch) {
    for(int i = 0; i < IR_PINS_COUNT; i++) {
        pins[i] = _pins[i];
        pinMode(pins[i], INPUT);
    }
    irValMax=IR_CALIB_MIN;
}

bool LineSensor::isOnLine(){
    return irValMax>IR_NOLINE_THRESH;
}

void LineSensor::calibrate() {

    digitalWrite(LED_BUILTIN, HIGH);
    #if DEBUG
    Serial.println("LineSensor::callibration start");
    #endif

    unsigned long startTime = millis();
    unsigned long currentTime = millis();

    // initialize values in the calibration "from" array
    for(int i = 0; i < IR_PINS_COUNT; i++) {
        calib_vals_min[i] = analogRead(pins[i]);
        calib_vals_max[i] = calib_vals_min[i];
    }

    // generate calibration "from" values
    uint16_t current_value;
    while((currentTime - startTime) < IR_CALIB_TIME) {
        for(int i = 0; i < IR_PINS_COUNT; i++) {
            current_value = analogRead(pins[i]);
            if(current_value < calib_vals_min[i]) {
                calib_vals_min[i] = current_value;
            } else if(current_value > calib_vals_max[i]) {
                calib_vals_max[i] = current_value;
            }
        }
        currentTime = millis();
    }

    #if DEBUG
    Serial.println("LineSensor::callibration end");
    #endif
    digitalWrite(LED_BUILTIN, LOW);
}


void LineSensor::read() {
    // read from the IRs and map them according to the calibration values
    irValMax=IR_CALIB_MIN;
    for(int i = 0; i < IR_PINS_COUNT; i++) {
        irVal[i] = analogRead(pins[i]);
        irVal[i] = constrain(irVal[i], calib_vals_min[i], calib_vals_max[i]);
        irVal[i] = map(irVal[i], calib_vals_min[i], calib_vals_max[i], IR_CALIB_MIN, IR_CALIB_MAX);
        irValMax = (irValMax>=irVal[i])?irValMax:irVal[i];
        #if DEBUG&0
        Serial.print(irVal[i]);
        Serial.print(',');
        #endif
    }
        #if DEBUG&0
        Serial.println(' ');
        #endif
}
void LineSensor::readSamples() {
    // read from the IRs and map them according to the calibration values
    uint16_t tmp=0;
    int j=0;
    for(j=0; j<SAMPLES-1; j++){
    for(int i = 0; i < IR_PINS_COUNT; i++) {
        tmp = analogRead(pins[i]);
        tmp = constrain(tmp, calib_vals_min[i], calib_vals_max[i]);
        irVal[i] = ((SAMPLE_FADE*irVal[i]*j) + tmp)/(j+1.0);
    }
    }
    for(int i = 0; i < IR_PINS_COUNT; i++) {
        tmp = analogRead(pins[i]);
        irVal[i] = constrain(tmp, calib_vals_min[i], calib_vals_max[i]);
        irVal[i] = map(((SAMPLE_FADE*irVal[i]*j) + tmp)/(j+1.0), calib_vals_min[i], calib_vals_max[i], IR_CALIB_MIN, IR_CALIB_MAX);
        #if DEBUG&0
        Serial.print(irVal[i]);
        Serial.print(',');
        #endif
    }
    for(int i = 0; i < IR_PINS_COUNT; i++) {
        irValMax = (irValMax>=irVal[i])?irValMax:irVal[i];
    }
				   
							
			  
        #if DEBUG&0
        Serial.println(' ');
        #endif
}
/**
 * @brief 
 * 
 * @return float position of line wrt central IR
 */
float LineSensor::interpolate() {
   
    double num = 0; // numerator
    double den = 0; // denominator

    // uses weighted average to produce one value that is indicative of where the robot is in relation to the line
    for(int i = 0; i < IR_PINS_COUNT; i++) {
        den += irVal[i];
    }
//    if(IR_PINS_COUNT&1)
//        den -= irVal[int(IR_PINS_COUNT/2)];     // don't consider central IR if odd number of IR's are used.

    for(int i = 0; i < int(IR_PINS_COUNT/2); i++){
        num += (int(IR_PINS_COUNT/2)-i)*(int(irVal[IR_PINS_COUNT-i-1])-int(irVal[i]));
    }
    #if DEBUG&0
    Serial.print(num);
    Serial.print(',');
    Serial.print(den);
    Serial.print(',');
    #endif
   
   return pitch*num/den;
}

void LineSensor::saveCalib(){
    EEPROM.put(IR_CALIB_VALUES_ADDR, calib_vals_min);
    EEPROM.put(IR_CALIB_VALUES_ADDR + sizeof(calib_vals_min), calib_vals_max);
    EEPROM.put(IR_CALIB_FLAG_ADDR, "OK");
}

bool LineSensor::loadCalib(){
    char ok[2+1] = "";
    EEPROM.get(IR_CALIB_FLAG_ADDR, ok);
    if(ok[0] == 'O' && ok[1] == 'K'){
        EEPROM.get(IR_CALIB_VALUES_ADDR, calib_vals_min);
        EEPROM.get(IR_CALIB_VALUES_ADDR + sizeof(calib_vals_min), calib_vals_max);
        return true;
    }
    return false;
}