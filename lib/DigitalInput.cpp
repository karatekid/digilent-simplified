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
    //Cache previous status values that we'll need
    int lastIndexWrite = inputStatus.indexWrite;
    //Call read
    DWF(DigitalInStatus(device, true, &(inputStatus.state)));
    //Populate InputStatusStruct
    DWF(DigitalInStatusSamplesLeft(device, &(inputStatus.samplesLeft)));
    DWF(DigitalInStatusSamplesValid(device, &(inputStatus.samplesValid)));
    DWF(DigitalInStatusIndexWrite(device, &(inputStatus.indexWrite)));
    DWF(DigitalInStatusAutoTriggered(device, &(inputStatus.autoTriggered)));
    //Get data depending on acquisitionMode
    //Read from beginIndex until endIndex [beginIndex, endIndex)
    //ie) begin:0, end: 1 --> we would read just index 0
    int beginIndex = 0, endIndex = 0;
    switch(acquisitionMode.get()) {
        case acqmodeSingle:
            //Only read when complete
            if(inputStatus.state == DwfStateDone) {
                endIndex = bufferSize.get();
            }
            break;
        case acqmodeScanShift:
            endIndex = std::min(
                    inputStatus.samplesValid,
                    bufferSize.get());
            break;
        case acqmodeScanScreen:
            beginIndex = lastIndexWrite;
            //Index Write keeps going, must wrap with bufferSize
            endIndex = inputStatus.indexWrite % bufferSize.get();
            break;
        default:
            throw AcquisitionModeNotImplementedException();
            break;
    }
    return readDigitalDataFromItoJ(beginIndex, endIndex);
}

std::vector<DigitalData> DigitalInput::readDigitalDataFromItoJ(int i, int j) {
    //Read to the furthest sample needed
    int maxNumSamples;
    int numSamplesToRead;
    if(j < i) {
        //Reversed:
        //We need to read until the end of the buffer
        maxNumSamples = bufferSize.get();
        numSamplesToRead = (maxNumSamples - i) + j;
    } else {
        maxNumSamples = std::max(i, j);
        numSamplesToRead = j - i;
    }
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
