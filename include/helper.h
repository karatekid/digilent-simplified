#ifndef __HELPER__H__
#define __HELPER__H__

//Logging
#include "easylogging++.h"
#define LOGGING_CONFIG "configs/general.conf"
#define LOGGING_LVL_CONFIG "configs/level.conf"
void initializeLogging(int argc, char *argv[]);

//DWF Calls
#include<digilent/waveforms/dwf.h> 

//Prepend with FDwf and wrap
#define DWF(fxn) \
    WRAP_DWF(FDwf ## fxn)
//Optional logging of dwf
//Using do-while because can let user use ';' as referenced here:
//https://gcc.gnu.org/onlinedocs/cpp/Swallowing-the-Semicolon.html
#define WRAP_DWF(fxn) \
    do {\
        CVLOG(9, "dwf") << "Called: " << #fxn; \
        HANDLE_DWF(fxn); \
    } while(0)

//Error handling
#include "dwf_exceptions.h"
#define HANDLE_DWF(fxn) \
    do {\
        if(!fxn) DWF_ERROR(fxn); \
    } while(0)

#define DWF_ERROR(fxn) \
    do {\
        DWFERC error; \
        FDwfGetLastError(&error); \
        CLOG(ERROR, "dwf") << #fxn << " errored out with code " << error; \
        throwDwfException(error); \
        CLOG(ERROR, "dwf") << "Apparently, there was no error."; \
    } while(0)

#endif
