#ifndef __HELPER__H__
#define __HELPER__H__
//External logging library
#include "easylogging++.h"
#define LOGGING_CONFIG "configs/general.conf"
#define LOGGING_LVL_CONFIG "configs/level.conf"

void initializeLogging(int argc, char *argv[]);

#endif
