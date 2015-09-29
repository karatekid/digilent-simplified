#ifndef __ANALOG_INPUT__H__
#define __ANALOG_INPUT__H__

#include "AnalogInputConfigurations.h"

class AnalogInput {
    public: 
        AnalogInput() {}
        AnalogInput(HDWF d);
        void reset();
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
    private:
        HDWF device;
        int bitResolution;
        int numChannels;
};

#endif
