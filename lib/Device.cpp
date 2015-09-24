/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : Device.cpp

 * Purpose : Main interface for device

 * Creation Date : 23-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "Device.h"

Device::Device() {
    char s[32];
    FDwfGetVersion(s);
    CLOG(INFO, "system") << s;
    //Discover devices
}
