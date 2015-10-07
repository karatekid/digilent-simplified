#ifndef __ANALOG_INPUT__H__
#define __ANALOG_INPUT__H__

#include<map>
#include<vector>

#include "AnalogInputConfigurations.h"

namespace dwf{
class AnalogInput {
    public: 
        AnalogInput() {}
        AnalogInput(HDWF d);
        void reset();
        void start();
        void stop();
        std::map<int, std::vector<double>> read();
        /*
        void status();
        */
        //AnalogIn Configurations
        AnalogInFrequency                  frequency;
        AnalogInBufferSize                 bufferSize;
        AnalogInAcquisitionMode            acquisitionMode;
        std::vector<AnalogInChannelEnable> channelEnable;
        std::vector<AnalogInChannelFilter> channelFilter;
        std::vector<AnalogInChannelRange>  channelRange;
        std::vector<AnalogInChannelOffset> channelOffset;
        AnalogInTriggerSource              triggerSource;
        AnalogInTriggerPosition            triggerPosition;
        AnalogInTriggerAutoTimeout         triggerAutoTimeout;
        AnalogInTriggerHoldOff             triggerHoldOff;
        AnalogInTriggerType                triggerType;
        AnalogInTriggerChannel             triggerChannel;
        AnalogInTriggerFilter              triggerFilter;
        AnalogInTriggerCondition           triggerCondition;
        AnalogInTriggerLevel               triggerLevel;
        AnalogInTriggerHysteresis          triggerHysteresis;
        AnalogInTriggerLengthCondition     triggerLengthCondition;
        AnalogInTriggerLength              triggerLength;
    protected:
        HDWF device;
        int bitResolution;
        int numChannels;
        //Updated after calling read
        InputStatusStruct inputStatus;
        std::map<int, std::vector<double>> readAnalogDataFromItoJ(int i, int j);
};
}

#endif
