#ifndef __DIGITAL_INPUT__H__
#define __DIGITAL_INPUT__H__

#include<bitset>
#include<algorithm>

#include "DigitalInputConfigurations.h"

namespace dwf{
typedef std::bitset<DIGITAL_DATA_SIZE> DigitalData;

class DigitalInput {
    public:
        DigitalInput() {}
        DigitalInput(HDWF d);
        void reset();
        void start();
        void stop();
        void configure();
        //Sets inputStatus, & returns data if applicable
        std::vector<DigitalData> read();
        //Information about DigitalInput
        double getInternalClkFreq();
        //DigitalIn Configurations
        DigitalInDivider            divider;
        DigitalInBufferSize         bufferSize;
        DigitalInAcquisitionMode    acquisitionMode;

        DigitalInTriggerSource      triggerSource;
        DigitalInTriggerPosition    triggerPosition;
        DigitalInTriggerAutoTimeout triggerAutoTimeout;
        DigitalInTrigger            trigger;
    protected:
        HDWF device;
        double internalClkFreq;
        int numBits;
        //Private function calls
        std::vector<DigitalData> readDigitalDataFromItoJ(int i, int j);
        void setDefaults();
        //Updated after calling read
        InputStatusStruct inputStatus;
        //Configurations that we don't want exposed
        DigitalInSampleFormat       sampleFormat;
        DigitalInSampleMode         sampleMode;
        DigitalInClockSource        clockSource;
};
}

#endif
