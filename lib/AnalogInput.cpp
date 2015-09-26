/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : AnalogInput.cpp

 * Purpose : Implementation of AnalogInput Instrument

 * Creation Date : 25-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "AnalogInput.h"

AnalogInput::AnalogInput(HDWF d) 
: device(d) {
    frequency = AnalogFrequencyConfiguration(device);
}

void AnalogInput::reset() {
    DWF(AnalogInReset(device));
}

AnalogFrequencyConfiguration::AnalogFrequencyConfiguration(HDWF d)
: ContinuousRangeConfiguration<double>(d) {
    DWF(AnalogInFrequencyInfo(device, &(range.min), &(range.max)));
}
IMPL_CONFIG_GETNSET(AnalogFrequencyConfiguration, AnalogInFrequency, double);
