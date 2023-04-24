#ifndef V02_RELEASE_OSCILLATOR_H
#define V02_RELEASE_OSCILLATOR_H


class Oscillator {
private:
    double speed;
    double phase;
    double stepDelta;
    double currentPhase;
    double value;
    unsigned long lastTimestamp;
public:
    Oscillator();
    void setSpeed(double s);
    void setPhase(double p);
    void step();
    double getValue();
};


#endif //V02_RELEASE_OSCILLATOR_H
