#ifndef V02_RELEASE_OSCILLATOR_H
#define V02_RELEASE_OSCILLATOR_H


class Oscillator {
private:
    double speed;
    double stepDelta;
    double phase;
    double value;
public:
    void setSpeed(double s);
    void step();
    double getValue();
};


#endif //V02_RELEASE_OSCILLATOR_H
