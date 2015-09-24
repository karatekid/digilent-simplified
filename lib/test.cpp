/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : test.cpp

 * Purpose : Test library

 * Creation Date : 23-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

#include "Device.h"
#include "Configuration.h"
#include "helper.h"

//Must call this only once, so doing it here
INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
    //Logging setup
    initializeLogging(argc, argv);

    CLOG(DEBUG, "main") << "Beginning Testing";
    HDWF device;
    DWF(DeviceOpen(0, &device));
    return 0;
}
