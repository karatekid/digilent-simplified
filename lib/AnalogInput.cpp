/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : AnalogInput.cpp

 * Purpose : Implementation of AnalogInput Instrument

 * Creation Date : 25-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "AnalogInput.h"

AnalogInput::AnalogInput(HDWF d) 
: device(d) {
    DWF(AnalogInBitsInfo(device, &bitResolution));
    DWF(AnalogInChannelCount(device, &numChannels));
    frequency       = AnalogInFrequency(device);
    bufferSize      = AnalogInBufferSize(device);
    acquisitionMode = AnalogInAcquisitionMode(device);
    for(int i = 0; i < numChannels; ++i) {
        channelEnable.push_back(AnalogInChannelEnable(device, i));
        channelFilter.push_back(AnalogInChannelFilter(device, i));
        channelRange.push_back(AnalogInChannelRange(device, i));
        channelOffset.push_back(AnalogInChannelOffset(device, i));
    }
    triggerSource          = AnalogInTriggerSource(device);
    triggerPosition        = AnalogInTriggerPosition(device);
    triggerAutoTimeout     = AnalogInTriggerAutoTimeout(device);
    triggerHoldOff         = AnalogInTriggerHoldOff(device);
    triggerType            = AnalogInTriggerType(device);
    triggerChannel         = AnalogInTriggerChannel(device);
    triggerFilter          = AnalogInTriggerFilter(device);
    triggerCondition       = AnalogInTriggerCondition(device);
    triggerLevel           = AnalogInTriggerLevel(device);
    triggerHysteresis      = AnalogInTriggerHysteresis(device);
    triggerLengthCondition = AnalogInTriggerLengthCondition(device);
    triggerLength          = AnalogInTriggerLength(device);
}

void AnalogInput::reset() {
    DWF(AnalogInReset(device));
}
