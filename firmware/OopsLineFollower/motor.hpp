#ifndef MOTOR_HPP
#define MOTOR_HPP

class Motor {
  private:
    int pin1;
    int pin2;
    bool isDirType;
    bool isInverted;
  public:
    Motor(int _pin1, int _pin2, bool _isDirType=true, bool _isInverted=false);
    void write(int _spd);
    void invert();
};

#endif
