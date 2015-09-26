#ifndef __DEVICE__H__
#define __DEVICE__H__

#include<digilent/waveforms/dwf.h> 

#include "helper.h"
#include "Configuration.h"

DEF_SET_CONFIG(AutoConfiguration, BOOL);
DEF_SET_CONFIG_W_INDEX(DeviceTriggerConfiguration, TRIGSRC);

class Device {
    public:
        Device();
        ~Device();
        void reset();
        //Device configurations
        AutoConfiguration autoConfigure;
        std::vector<DeviceTriggerConfiguration> triggers;
        //Device instruments
    private:
        HDWF device;
        const int numTriggerPins = 16;
};

#endif
