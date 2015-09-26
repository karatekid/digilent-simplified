#ifndef __DIGITAL_INPUT__H__
#define __DIGITAL_INPUT__H__

#include "helper.h"
#include "Configuration.h"

class DigitalInput {
    public:
        DigitalInput() {}
        DigitalInput(HDWF d);
        void reset();
        /*
        void status();
        */
        //DigitalIn Configurations
    private:
        HDWF device;
        int numBits;
};

#endif
