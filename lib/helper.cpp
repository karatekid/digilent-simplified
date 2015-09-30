/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : helper.cpp

 * Purpose : Helper and utilities

 * Creation Date : 23-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "helper.h"

//Helper Functions
bool isEquivalent(double a, double b) {
    return abs(a - b) <= DBL_CLOSE_ENOUGH;
}

int getMaxIdxToReadTo(int i, int j, int bufferSize) {
    if(j < i) {
        //Reversed:
        //We need to read until the end of the buffer
        return bufferSize;
    } else {
        return std::max(i, j);
    }
}
int getNumSamplesToRead(int i, int j, int bufferSize) {
    if(j < i) {
        //Reversed:
        //We need to read until the end of the buffer
        return (bufferSize - i) + j;
    } else {
        return j - i;
    }
}

//Logging
void initializeLogging(int argc, char *argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    el::Configurations conf(LOGGING_CONFIG);
    el::Loggers::reconfigureAllLoggers(conf);
    el::Loggers::configureFromGlobal(LOGGING_LVL_CONFIG);
}
