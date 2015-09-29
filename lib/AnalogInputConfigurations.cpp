/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : AnalogInputConfigurations.cpp

 * Purpose :

 * Creation Date : 28-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "AnalogInputConfigurations.h"

IMPL_CR_CONFIG_ALL(AnalogInFrequency, double);
IMPL_CR_CONFIG_ALL(AnalogInBufferSize, int);
IMPL_SET_CONFIG_ALL(AnalogInAcquisitionMode, ACQMODE);

AnalogInChannelEnable::AnalogInChannelEnable(HDWF d, int idx)
: SetConfiguration<BOOL>(d), index(idx) {
    options.insert(0);
    options.insert(1);
}
IMPL_CONFIG_GETNSET_W_INDEX(AnalogInChannelEnable, BOOL);

IMPL_SET_CONFIG_ALL_W_INDEX(AnalogInChannelFilter, FILTER);
//Right now only 2 steps (5, 50). If have more, might need to use
//FDwfChannelRangeSteps, and change this to SetConfiguration
//TODO: Possibly
IMPL_DR_CONFIG_ALL_W_INDEX(AnalogInChannelRange,           double);
IMPL_DR_CONFIG_ALL_W_INDEX(AnalogInChannelOffset,          double);
IMPL_SET_CONFIG_ALL(       AnalogInTriggerSource,          TRIGSRC);
IMPL_DR_CONFIG_ALL(        AnalogInTriggerPosition,        double);
IMPL_DR_CONFIG_ALL(        AnalogInTriggerAutoTimeout,     double);
IMPL_DR_CONFIG_ALL(        AnalogInTriggerHoldOff,         double);
IMPL_SET_CONFIG_ALL(       AnalogInTriggerType,            TRIGTYPE);
IMPL_CR_CONFIG_ALL(        AnalogInTriggerChannel,         int);
IMPL_SET_CONFIG_ALL(       AnalogInTriggerFilter,          FILTER);
IMPL_SET_CONFIG_ALL(       AnalogInTriggerCondition,       TRIGCOND);
IMPL_DR_CONFIG_ALL(        AnalogInTriggerLevel,           double);
IMPL_DR_CONFIG_ALL(        AnalogInTriggerHysteresis,      double);
IMPL_SET_CONFIG_ALL(       AnalogInTriggerLengthCondition, TRIGLEN);
IMPL_DR_CONFIG_ALL(        AnalogInTriggerLength,          double);
