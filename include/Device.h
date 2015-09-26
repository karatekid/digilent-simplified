#ifndef __DEVICE__H__
#define __DEVICE__H__

#include<digilent/waveforms/dwf.h> 

#include "helper.h"
#include "Configuration.h"

DEF_SET_CONFIG(AutoConfiguration, BOOL);

class DeviceTriggerConfiguration : public SetConfiguration<TRIGSRC> {
    public:
        DeviceTriggerConfiguration() : SetConfiguration<TRIGSRC>() {}
        DeviceTriggerConfiguration(HDWF d, int idx)
            : SetConfiguration<TRIGSRC>(d), index(idx) {
            int triggerMask;
            DWF(DeviceTriggerInfo(device, &triggerMask));
            for(TRIGSRC i = 0; i < sizeof(int); ++i) {
                if(IsBitSet(triggerMask,i)) {
                    options.insert(i);
                }
            }
        }
    protected:
        void setImpl(TRIGSRC val) {
            DWF(DeviceTriggerSet(device, index, val));
        }
        TRIGSRC getImpl() {
            TRIGSRC val;
            DWF(DeviceTriggerGet(device, index, &val));
            return val;
        }
    private:
        int index;
};

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
