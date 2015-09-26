#ifndef __ANALOG_INPUT__H__
#define __ANALOG_INPUT__H__

#include "helper.h"
#include "Configuration.h"

DEF_CONFIG(        AnalogInFrequency,              double,   ContinuousRangeConfiguration);
DEF_CONFIG(        AnalogInBufferSize,             int,      ContinuousRangeConfiguration);
DEF_CONFIG(        AnalogInAcquisitionMode,        ACQMODE,  SetConfiguration);
DEF_CONFIG_W_INDEX(AnalogInChannelEnable,          BOOL,     SetConfiguration);
DEF_CONFIG_W_INDEX(AnalogInChannelFilter,          FILTER,   SetConfiguration);
DEF_CONFIG_W_INDEX(AnalogInChannelRange,           double,   DiscreteRangeConfiguration);
DEF_CONFIG_W_INDEX(AnalogInChannelOffset,          double,   DiscreteRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerSource,          TRIGSRC,  SetConfiguration);
DEF_CONFIG(        AnalogInTriggerPosition,        double,   DiscreteRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerAutoTimeout,     double,   DiscreteRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerHoldOff,         double,   DiscreteRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerType,            TRIGTYPE, SetConfiguration);
DEF_CONFIG(        AnalogInTriggerChannel,         int,      ContinuousRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerFilter,          FILTER,   SetConfiguration);
DEF_CONFIG(        AnalogInTriggerCondition,       TRIGCOND, SetConfiguration);
DEF_CONFIG(        AnalogInTriggerLevel,           double,   DiscreteRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerHysteresis,      double,   DiscreteRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerLengthCondition, TRIGLEN,  SetConfiguration);
DEF_CONFIG(        AnalogInTriggerLength,          double,   DiscreteRangeConfiguration);

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
