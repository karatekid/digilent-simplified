/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : AnalogInput.cpp

 * Purpose : Implementation of AnalogInput Instrument

 * Creation Date : 25-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "AnalogInput.h"

namespace dwf{
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

void AnalogInput::start() {
    // Configure & start
    DWF(AnalogInConfigure(device, true, true));
}

void AnalogInput::stop() {
    DWF(AnalogInConfigure(device, false, false));
}

void AnalogInput::configure() {
    // Configure w/o starting
    DWF(AnalogInConfigure(device, true, false));
}

std::map<int, std::vector<double>> AnalogInput::read() {
    PERFORM_READ_INTERNALS(AnalogIn, readAnalogDataFromItoJ);
}

std::map<int, std::vector<double>> AnalogInput::readAnalogDataFromItoJ(int i, int j) {
    //Read to the furthest sample needed
    int maxNumSamples = getMaxIdxToReadTo(i, j, bufferSize.get());
    int numSamplesToRead = getNumSamplesToRead(i, j, bufferSize.get());
    double tmpArr[maxNumSamples];

    std::map<int, std::vector<double>> data;
    for(int channel = 0; channel < channelEnable.size(); ++channel) {
        if(channelEnable[channel].get()) {
            DWF(AnalogInStatusData(device, channel, tmpArr, maxNumSamples));
            for(int idx = i, numRead = 0;
                    numRead < numSamplesToRead;
                    idx = (idx + 1) % maxNumSamples, numRead ++) {
                data[channel].push_back(tmpArr[idx]);
            }
        }
    }
    return data;
}
}
