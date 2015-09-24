#ifndef __CONFIGURATION__H__
#define __CONFIGURATION__H__

#include<digilent/waveforms/dwf.h> 

class Configuration{
    public:
        Configuration(HDWF d);
    protected:
        HDWF device;
};

#endif
