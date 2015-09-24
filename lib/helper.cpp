/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : helper.cpp

 * Purpose : Helper and utilities

 * Creation Date : 23-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "helper.h"

//Logging
void initializeLogging(int argc, char *argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    el::Configurations conf(LOGGING_CONFIG);
    el::Loggers::reconfigureAllLoggers(conf);
    el::Loggers::configureFromGlobal(LOGGING_LVL_CONFIG);
}
