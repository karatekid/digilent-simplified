#ifndef __ANALOG_INPUT__H__
#define __ANALOG_INPUT__H__

#include "helper.h"
#include "Configuration.h"

DEF_CONFIG(AnalogFrequencyConfiguration, double, ContinuousRangeConfiguration);
DEF_CONFIG(AnalogBufferSize, int, ContinuousRangeConfiguration);
DEF_CONFIG(AnalogInAcquisitionMode, ACQMODE, SetConfiguration);

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
        AnalogBufferSize bufferSize;
        AnalogInAcquisitionMode acquisitionMode;
    private:
        HDWF device;
        int bitResolution;
};

#endif
