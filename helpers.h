#ifndef V02_RELEASE_HELPERS_H
#define V02_RELEASE_HELPERS_H

#include <Arduino.h>


void printDouble(double val, unsigned int precision) {
// prints val with number of decimal places determine by precision
// NOTE: precision is 1 followed by the number of zeros for the desired number of decimal places
// example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)
// https://forum.arduino.cc/t/printing-a-double-variable/44327/4

    Serial.print (int(val));  //prints the int part
    Serial.print("."); // print the decimal point
    unsigned int frac;
    if(val >= 0)
        frac = (val - int(val)) * precision;
    else
        frac = (int(val)- val ) * precision;
    int frac1 = frac;
    while( frac1 /= 10 )
        precision /= 10;
    precision /= 10;
    while(  precision /= 10)
        Serial.print("0");

    Serial.println(frac,DEC) ;
}


#endif //V02_RELEASE_HELPERS_H
