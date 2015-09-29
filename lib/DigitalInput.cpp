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
    trigger = DigitalInTrigger(d);
}

void DigitalInput::reset() {
    DWF(DigitalInReset(device));
}
