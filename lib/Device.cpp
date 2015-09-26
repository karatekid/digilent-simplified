/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : Device.cpp

 * Purpose : Main interface for device

 * Creation Date : 23-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "Device.h"

Device::Device() {
    char s[32];
    DWF(GetVersion(s));
    CLOG(INFO, "dwf") << s;
    //Discover devices
    int numDevices = 0;
    DWF(Enum(enumfilterDiscovery, &numDevices));
    if(numDevices < 1) {
        CLOG(WARNING, "dwf") << "No device attached";
        throw DeviceMissingException();
    } else if (numDevices > 1) {
        CLOG(WARNING, "dwf") << "More than 1 discovery attached." <<
            " Device chosen is random.";
    }
    DEVID devId;
    DEVVER devVer;
    DWF(EnumDeviceType(0, &devId, &devVer));
    CLOG(INFO, "dwf") << "Device Id: " << devId;
    CLOG(INFO, "dwf") << "Device Version: " << devVer;
    DWF(EnumUserName(0, s));
    CLOG(INFO, "dwf") << "Device User Name: " << s;
    DWF(EnumDeviceName(0, s));
    CLOG(INFO, "dwf") << "Device Name: " << s;
    DWF(EnumSN(0, s));
    CLOG(INFO, "dwf") << "Device SN: " << s;
    DWF(DeviceOpen(0, &device));
    //Initalize configurations
    autoConfigure = DeviceAutoConfigure(device);
    for(int i = 0; i < numTriggerPins; ++i) {
        triggers.push_back(DeviceTrigger(device, i));
    }
    //Initialize instruments
    analogIn = AnalogInput(device);
}

Device::~Device() {
    DWF(DeviceCloseAll());
}

void Device::reset() {
    DWF(DeviceReset(device));
}


DeviceAutoConfigure::DeviceAutoConfigure(HDWF d) : SetConfiguration<BOOL>(d) {
    options.insert(0);
    options.insert(1);
}
IMPL_CONFIG_GETNSET(DeviceAutoConfigure, BOOL);

IMPL_SET_CONFIG_ALL_W_INDEX(DeviceTrigger, TRIGSRC);
