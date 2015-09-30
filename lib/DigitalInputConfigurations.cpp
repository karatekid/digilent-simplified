/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : DigitalInputConfigurations.cpp

 * Purpose :

 * Creation Date : 28-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "DigitalInputConfigurations.h"

IMPL_SET_CONFIG_ALL(DigitalInClockSource, DwfDigitalInClockSource);

DigitalInDivider::DigitalInDivider(HDWF d)
: ContinuousRangeConfiguration<unsigned int>(d) {
    range.min = 1;
    DWF(DigitalInDividerInfo(device, &(range.max)));
}
IMPL_CONFIG_GETNSET(DigitalInDivider, unsigned int);

DigitalInSampleFormat::DigitalInSampleFormat(HDWF d)
: SetConfiguration<int>(d) {
    //options.insert(8);
    options.insert(DIGITAL_DATA_SIZE);
    //options.insert(32);
}
IMPL_CONFIG_GETNSET(DigitalInSampleFormat, int);

DigitalInBufferSize::DigitalInBufferSize(HDWF d)
: ContinuousRangeConfiguration<int>(d) {
    //BufferSize info changes with sampleFormat, so don't change format
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

DigitalInTrigger::DigitalInTrigger(HDWF d)
: BitSetConfiguration<DigitalInTriggerStruct>(d) {
    DWF(DigitalInTriggerInfo(device, 
                &(bitmask.levelLow),
                &(bitmask.levelHigh),
                &(bitmask.edgeRise),
                &(bitmask.edgeFall)));
}
void DigitalInTrigger::setImpl(DigitalInTriggerStruct val) {
    DWF(DigitalInTriggerSet(device,
                val.levelLow,
                val.levelHigh,
                val.edgeRise,
                val.edgeFall));
}
DigitalInTriggerStruct DigitalInTrigger::getImpl() {
    DigitalInTriggerStruct val;
    DWF(DigitalInTriggerGet(device,
                &(val.levelLow),
                &(val.levelHigh),
                &(val.edgeRise),
                &(val.edgeFall)));
    return val;
}
