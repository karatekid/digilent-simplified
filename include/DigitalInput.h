#ifndef __DIGITAL_INPUT__H__
#define __DIGITAL_INPUT__H__

#include "helper.h"
#include "Configuration.h"

DEF_CONFIG(DigitalInClockSource, DwfDigitalInClockSource, SetConfiguration);
DEF_CONFIG(DigitalInDivider, unsigned int, ContinuousRangeConfiguration);
DEF_CONFIG(DigitalInSampleFormat, int, SetConfiguration);
DEF_CONFIG(DigitalInBufferSize, int, ContinuousRangeConfiguration);
DEF_CONFIG(DigitalInSampleMode, DwfDigitalInSampleMode, SetConfiguration);
DEF_CONFIG(DigitalInAcquisitionMode, ACQMODE, SetConfiguration);
DEF_CONFIG(DigitalInTriggerSource, TRIGSRC, SetConfiguration);
DEF_CONFIG(DigitalInTriggerPosition, unsigned int, ContinuousRangeConfiguration);
DEF_CONFIG(DigitalInTriggerAutoTimeout, double, DiscreteRangeConfiguration);
struct DigitalInTriggerStruct {
    unsigned int levelLow, levelHigh, edgeRise, edgeFall;
};
DEF_CONFIG(DigitalInTrigger, DigitalInTriggerStruct, BitSetConfiguration);

class DigitalInput {
    public:
        DigitalInput() {}
        DigitalInput(HDWF d);
        void reset();
        /*
        void status();
        */
        //DigitalIn Configurations
        DigitalInClockSource clockSource;
        DigitalInDivider divider;
        DigitalInSampleFormat sampleFormat;
        DigitalInBufferSize bufferSize;
        DigitalInSampleMode sampleMode;
        DigitalInAcquisitionMode acquisitionMode;
        DigitalInTriggerSource triggerSource;
        DigitalInTriggerPosition triggerPosition;
        DigitalInTriggerAutoTimeout triggerAutoTimeout;
        DigitalInTrigger trigger;
    private:
        HDWF device;
        double internalClkFreq;
        int numBits;
};

#endif
