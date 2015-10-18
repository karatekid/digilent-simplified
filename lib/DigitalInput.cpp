/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : DigitalInput.cpp

 * Purpose :

 * Creation Date : 26-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "DigitalInput.h"

namespace dwf{
DigitalInput::DigitalInput(HDWF d)
: device(d) {
    setDefaults();
}

void DigitalInput::reset() {
    DWF(DigitalInReset(device));
    setDefaults();
}

void DigitalInput::setDefaults() {
    DWF(DigitalInInternalClockInfo(device, &internalClkFreq));
    DWF(DigitalInBitsInfo(device, &numBits));
    //Set inputStatus to defaults
    inputStatus.state = DwfStateReady;
    inputStatus.samplesLeft =
        inputStatus.samplesValid =
        inputStatus.indexWrite = 0;
    //Set sampleFormat to default
    sampleFormat = DigitalInSampleFormat(device);
    sampleFormat.set(DIGITAL_DATA_SIZE);
    //Set sampleMode to default
    sampleMode = DigitalInSampleMode(device);
    sampleMode.set(DwfDigitalInSampleModeSimple);
    //Set clockSource to default
    clockSource = DigitalInClockSource(device);
    //TODO: there are no clockSources available
    //clockSource.set(DwfDigitalInClockSourceInternal);

    //Generic public configurations
    divider = DigitalInDivider(device);
    bufferSize = DigitalInBufferSize(device);
    sampleMode = DigitalInSampleMode(device);
    acquisitionMode = DigitalInAcquisitionMode(device);
    triggerSource = DigitalInTriggerSource(device);
    triggerPosition = DigitalInTriggerPosition(device);
    triggerAutoTimeout = DigitalInTriggerAutoTimeout(device);
    trigger = DigitalInTrigger(device);
}

void DigitalInput::start() {
    // Configure & start
    DWF(DigitalInConfigure(device, true, true));
}

void DigitalInput::stop() {
    DWF(DigitalInConfigure(device, false, false));
}

void DigitalInput::configure() {
    // Configure w/o starting
    DWF(DigitalInConfigure(device, true, false));
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
}
