#ifndef __DEVICE__H__
#define __DEVICE__H__

#include<digilent/waveforms/dwf.h> 

#include "helper.h"

class Device {
    public:
        Device();

        //Device configurations
    private:
        HDWF device;
};

#endif
