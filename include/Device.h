#ifndef __DEVICE__H__
#define __DEVICE__H__

#include "Helper.h"
#include "Configuration.h"
#include "AnalogInput.h"
#include "DigitalInput.h"

DEF_CONFIG(DeviceAutoConfigure, BOOL, SetConfiguration);
DEF_CONFIG_W_INDEX(DeviceTrigger, TRIGSRC, SetConfiguration);

class Device {
    public:
        Device();
        ~Device();
        void reset();
        //Device configurations
        DeviceAutoConfigure autoConfigure;
        std::vector<DeviceTrigger> triggers;
        //Device instruments
        AnalogInput analogIn;
        DigitalInput digitalIn;
    private:
        HDWF device;
        const int numTriggerPins = 16;
};

#endif
