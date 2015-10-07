#ifndef __DIGITAL_INPUT_CONFIGURATIONS__H__
#define __DIGITAL_INPUT_CONFIGURATIONS__H__

#include "Helper.h"
#include "Configuration.h"

//Data format is 16 bits by default
#define DIGITAL_DATA_SIZE 16
#define DIGITAL_NUM_BYTES_IN_SAMPLE (DIGITAL_DATA_SIZE / 8)

namespace dwf{
DEF_CONFIG(DigitalInClockSource, DwfDigitalInClockSource, SetConfiguration);
DEF_CONFIG(DigitalInDivider, unsigned int, ContinuousRangeConfiguration);
DEF_CONFIG(DigitalInSampleFormat, int, SetConfiguration);
DEF_CONFIG(DigitalInBufferSize, int, ContinuousRangeConfiguration);
DEF_CONFIG(DigitalInSampleMode, DwfDigitalInSampleMode, SetConfiguration);
DEF_CONFIG(DigitalInAcquisitionMode, ACQMODE, SetConfiguration);
DEF_CONFIG(DigitalInTriggerSource, TRIGSRC, SetConfiguration);
DEF_CONFIG(DigitalInTriggerPosition, unsigned int, ContinuousRangeConfiguration);
DEF_CONFIG(DigitalInTriggerAutoTimeout, double, DiscreteRangeConfiguration);
struct DigitalInTriggerStruct {
    unsigned int levelLow, levelHigh, edgeRise, edgeFall;
};
DEF_CONFIG(DigitalInTrigger, DigitalInTriggerStruct, BitSetConfiguration);
}


#endif
