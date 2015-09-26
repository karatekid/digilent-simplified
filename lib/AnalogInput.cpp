/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : AnalogInput.cpp

 * Purpose : Implementation of AnalogInput Instrument

 * Creation Date : 25-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "AnalogInput.h"

AnalogInput::AnalogInput(HDWF d) 
: device(d) {
    frequency = AnalogInFrequency(device);
    DWF(AnalogInBitsInfo(device, &bitResolution));
}

void AnalogInput::reset() {
    DWF(AnalogInReset(device));
}

AnalogInFrequency::AnalogInFrequency(HDWF d)
: ContinuousRangeConfiguration<double>(d) {
    DWF(AnalogInFrequencyInfo(device, &(range.min), &(range.max)));
}
IMPL_CONFIG_GETNSET(AnalogInFrequency, double);

AnalogInBufferSize::AnalogInBufferSize(HDWF d)
: ContinuousRangeConfiguration<int>(d) {
    DWF(AnalogInBufferSizeInfo(device, &(range.min), &(range.max)));
}
IMPL_CONFIG_GETNSET(AnalogInBufferSize, int);

AnalogInAcquisitionMode::AnalogInAcquisitionMode(HDWF d)
: SetConfiguration<ACQMODE>(d) {
    int triggerMask;
    DWF(AnalogInAcquisitionModeInfo(device, &triggerMask));
    for(ACQMODE i = 0; i < sizeof(int); ++i) {
        if(IsBitSet(triggerMask, i)) {
            options.insert(i);
        }
    }
}
IMPL_CONFIG_GETNSET(AnalogInAcquisitionMode, BOOL);


