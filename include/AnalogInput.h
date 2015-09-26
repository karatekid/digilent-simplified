#ifndef __ANALOG_INPUT__H__
#define __ANALOG_INPUT__H__

#include "helper.h"
#include "Configuration.h"

DEF_CONFIG(AnalogFrequencyConfiguration, double, ContinuousRangeConfiguration);

class AnalogInput {
    public: 
        AnalogInput() {}
        AnalogInput(HDWF d);
        void reset();
        /*
        void status();
        */
        //AnalogIn Configurations
        AnalogFrequencyConfiguration frequency;
    private:
        HDWF device;
};

#endif
