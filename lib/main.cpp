/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : main.cpp

 * Purpose : Run Device and configurations through their paces 

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

//External logging library
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#define LOGGING_CONFIG "configs/general.conf"
#define LOGGING_LVL_CONFIG "configs/level.conf"

el::Logger* mainLogger = el::Loggers::getLogger("main");

int main(int argc, char *argv[]) {
    //Logging setup
    START_EASYLOGGINGPP(argc, argv);
    el::Configurations conf(LOGGING_CONFIG);
    el::Loggers::reconfigureAllLoggers(conf);
    el::Loggers::configureFromGlobal(LOGGING_LVL_CONFIG);

    mainLogger->debug("Hey there");
    CLOG(INFO, "main") << "HEY CLOG";

    Device d;
    return 0;
}
