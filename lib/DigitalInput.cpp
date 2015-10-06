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
    //Set inputStatus to defaults
    inputStatus.state = DwfStateReady;
    inputStatus.samplesLeft =
        inputStatus.samplesValid =
        inputStatus.indexWrite = 0;
    //Set sampleFormat to default
    sampleFormat = DigitalInSampleFormat(d);
    sampleFormat.set(DIGITAL_DATA_SIZE);

    clockSource = DigitalInClockSource(d);
    divider = DigitalInDivider(d);
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

void DigitalInput::start() {
    DWF(DigitalInConfigure(device, true, true));
}

void DigitalInput::stop() {
    DWF(DigitalInConfigure(device, false, false));
}

std::vector<DigitalData> DigitalInput::read() {
    PERFORM_READ_INTERNALS(DigitalIn, readDigitalDataFromItoJ);
}

double DigitalInput::getInternalClkFreq() {
    return internalClkFreq;
}

std::vector<DigitalData> DigitalInput::readDigitalDataFromItoJ(int i, int j) {
    //Read to the furthest sample needed
    int maxNumSamples = getMaxIdxToReadTo(i, j, bufferSize.get());
    int numSamplesToRead = getNumSamplesToRead(i, j, bufferSize.get());
    
    //IndexWrite & samplesValid deals with samples, we need to get it in terms
    //of bytes
    int numBytes = DIGITAL_NUM_BYTES_IN_SAMPLE * maxNumSamples;
    int16_t tmpArr[maxNumSamples];
    DWF(DigitalInStatusData(device, tmpArr, numBytes));
    std::vector<DigitalData> data;
    //Wrap index around if necessary, and count until numRead is good
    for(int idx = i, numRead = 0;
            numRead < numSamplesToRead;
            idx = (idx + 1) % maxNumSamples, numRead ++) {
        data.push_back(DigitalData(tmpArr[idx]));
    }
    return data;
}
