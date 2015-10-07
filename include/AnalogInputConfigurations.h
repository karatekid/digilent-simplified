#ifndef __ANALOG_INPUT_CONFIGURATIONS__H__
#define __ANALOG_INPUT_CONFIGURATIONS__H__

#include "Helper.h"
#include "Configuration.h"

namespace dwf{
DEF_CONFIG(        AnalogInFrequency,              double,   ContinuousRangeConfiguration);
DEF_CONFIG(        AnalogInBufferSize,             int,      ContinuousRangeConfiguration);
DEF_CONFIG(        AnalogInAcquisitionMode,        ACQMODE,  SetConfiguration);
DEF_CONFIG_W_INDEX(AnalogInChannelEnable,          BOOL,     SetConfiguration);
DEF_CONFIG_W_INDEX(AnalogInChannelFilter,          FILTER,   SetConfiguration);
DEF_CONFIG_W_INDEX(AnalogInChannelRange,           double,   DiscreteRangeConfiguration);
DEF_CONFIG_W_INDEX(AnalogInChannelOffset,          double,   DiscreteRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerSource,          TRIGSRC,  SetConfiguration);
DEF_CONFIG(        AnalogInTriggerPosition,        double,   DiscreteRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerAutoTimeout,     double,   DiscreteRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerHoldOff,         double,   DiscreteRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerType,            TRIGTYPE, SetConfiguration);
DEF_CONFIG(        AnalogInTriggerChannel,         int,      ContinuousRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerFilter,          FILTER,   SetConfiguration);
DEF_CONFIG(        AnalogInTriggerCondition,       TRIGCOND, SetConfiguration);
DEF_CONFIG(        AnalogInTriggerLevel,           double,   DiscreteRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerHysteresis,      double,   DiscreteRangeConfiguration);
DEF_CONFIG(        AnalogInTriggerLengthCondition, TRIGLEN,  SetConfiguration);
DEF_CONFIG(        AnalogInTriggerLength,          double,   DiscreteRangeConfiguration);
}



#endif
