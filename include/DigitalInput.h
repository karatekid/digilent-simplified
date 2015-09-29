#ifndef __DIGITAL_INPUT__H__
#define __DIGITAL_INPUT__H__

#include "DigitalInputConfigurations.h"

class DigitalInput {
    public:
        DigitalInput() {}
        DigitalInput(HDWF d);
        void reset();
        /*
        void status();
        */
        //DigitalIn Configurations
        DigitalInClockSource        clockSource;
        DigitalInDivider            divider;
        DigitalInSampleFormat       sampleFormat;
        DigitalInBufferSize         bufferSize;
        DigitalInSampleMode         sampleMode;
        DigitalInAcquisitionMode    acquisitionMode;
        DigitalInTriggerSource      triggerSource;
        DigitalInTriggerPosition    triggerPosition;
        DigitalInTriggerAutoTimeout triggerAutoTimeout;
        DigitalInTrigger            trigger;
    private:
        HDWF device;
        double internalClkFreq;
        int numBits;
};

#endif
