#ifndef __DEVICE__H__
#define __DEVICE__H__

#include "helper.h"
#include "Configuration.h"
#include "AnalogInput.h"

DEF_CONFIG(AutoConfiguration, BOOL, SetConfiguration);
DEF_CONFIG_W_INDEX(DeviceTriggerConfiguration, TRIGSRC, SetConfiguration);

class Device {
    public:
        Device();
        ~Device();
        void reset();
        //Device configurations
        AutoConfiguration autoConfigure;
        std::vector<DeviceTriggerConfiguration> triggers;
        //Device instruments
        AnalogInput analogIn;
    private:
        HDWF device;
        const int numTriggerPins = 16;
};

#endif
