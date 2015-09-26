/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : DigitalInput.cpp

 * Purpose :

 * Creation Date : 26-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "DigitalInput.h"

DigitalInput::DigitalInput(HDWF d)
: device(d) {
}

void DigitalInput::reset() {
    DWF(DigitalInReset(device));
}


