#ifndef __DEVICE__H__
#define __DEVICE__H__

#include<digilent/waveforms/dwf.h> 

#include "helper.h"
#include "Configuration.h"

class AutoConfiguration : public SetConfiguration<BOOL> {
    public:
        AutoConfiguration() {}
        AutoConfiguration(HDWF d) : SetConfiguration<BOOL>(d){}
    protected:
        void setImpl(BOOL val) {
            DWF(DeviceAutoConfigureSet(device, val));
        }
        BOOL getImpl() {
            BOOL val;
            DWF(DeviceAutoConfigureGet(device, &val));
            return val;
        }
        void initOptionsImpl() {
            options.insert(0);
            options.insert(1);
        }
};

class Device {
    public:
        Device();
        void reset();
        //Device configurations
        AutoConfiguration autoConfigure;
    private:
        HDWF device;
};

#endif
