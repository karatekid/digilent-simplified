/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : DigitalInput.cpp

 * Purpose :

 * Creation Date : 26-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "DigitalInput.h"

DigitalInput::DigitalInput(HDWF d)
: device(d) {
    DWF(DigitalInInternalClockInfo(device, &internalClkFreq));
    DWF(DigitalInBitsInfo(device, &numBits));
    clockSource = DigitalInClockSource(d);
    divider = DigitalInDivider(d);
    sampleFormat = DigitalInSampleFormat(d);
    bufferSize = DigitalInBufferSize(d);
    sampleMode = DigitalInSampleMode(d);
    acquisitionMode = DigitalInAcquisitionMode(d);
    triggerSource = DigitalInTriggerSource(d);
    triggerPosition = DigitalInTriggerPosition(d);
    triggerAutoTimeout = DigitalInTriggerAutoTimeout(d);
}

void DigitalInput::reset() {
    DWF(DigitalInReset(device));
}

IMPL_SET_CONFIG_ALL(DigitalInClockSource, DwfDigitalInClockSource);

DigitalInDivider::DigitalInDivider(HDWF d)
: ContinuousRangeConfiguration<unsigned int>(d) {
    range.min = 1;
    DWF(DigitalInDividerInfo(device, &(range.max)));
}
IMPL_CONFIG_GETNSET(DigitalInDivider, unsigned int);

DigitalInSampleFormat::DigitalInSampleFormat(HDWF d)
: SetConfiguration<int>(d) {
    options.insert(8);
    options.insert(16);
    options.insert(32);
}
IMPL_CONFIG_GETNSET(DigitalInSampleFormat, int);

DigitalInBufferSize::DigitalInBufferSize(HDWF d)
: ContinuousRangeConfiguration<int>(d) {
    range.min = 1;
    DWF(DigitalInBufferSizeInfo(device, &(range.max)));
}
IMPL_CONFIG_GETNSET(DigitalInBufferSize, int);


IMPL_SET_CONFIG_ALL(DigitalInSampleMode, DwfDigitalInSampleMode);
IMPL_SET_CONFIG_ALL(DigitalInAcquisitionMode, ACQMODE);
IMPL_SET_CONFIG_ALL(DigitalInTriggerSource, TRIGSRC);

DigitalInTriggerPosition::DigitalInTriggerPosition(HDWF d)
: ContinuousRangeConfiguration<unsigned int>(d) {
    range.min = 0;
    DWF(DigitalInTriggerPositionInfo(device, &(range.max)));
}
IMPL_CONFIG_GETNSET(DigitalInTriggerPosition, unsigned int);

IMPL_DR_CONFIG_ALL(DigitalInTriggerAutoTimeout, double);
