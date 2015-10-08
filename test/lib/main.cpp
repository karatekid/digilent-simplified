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

#include <dwfobj/Device.h>
#include <dwfobj/Configuration.h>
#include <dwfobj/Helper.h>
#include <dwfobj/easylogging++.h>


//Must call this only once, so doing it here
INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
    //Logging setup
    initializeLogging(argc, argv);

    CLOG(DEBUG, "main") << "Beginning Testing";
    dwf::Device dev;
    CLOG(INFO, "main") << "DIN divider: " << dev.digitalIn.divider.getRange().toString();
    CLOG(INFO, "main") << "DIN bufSize: " << dev.digitalIn.bufferSize.getRange().toString();
    CLOG(INFO, "main") << "DIN acqMode: " << dev.digitalIn.acquisitionMode.optionsAsString();
    CLOG(INFO, "main") << "DIN TRIGSRC: " << dev.digitalIn.triggerSource.optionsAsString();
    CLOG(INFO, "main") << "DIN TRIGPOS: " << dev.digitalIn.triggerPosition.getRange().toString();
    CLOG(INFO, "main") << "DIN TRIGAUTOTO: " << dev.digitalIn.triggerAutoTimeout.getRange().toString();
    //CLOG(INFO, "main") << "DIN TRIGGER: " << dev.digitalIn.trigger.optionsAsString();
    dev.digitalIn.reset();
    dev.digitalIn.divider.set(1);
    dev.digitalIn.bufferSize.set(4096);
    dev.digitalIn.acquisitionMode.set(acqmodeScanShift);
    dev.digitalIn.start();
    std::vector<dwf::DigitalData> tmpData;
    for(;;) {
        tmpData = dev.digitalIn.read();
        std::cout << "new_read\n";
        for(int i = 0; i < tmpData.size(); ++i) {
            std::cout << i << ": " << tmpData[i] << std::endl;
        }
    }
    return 0;
}
