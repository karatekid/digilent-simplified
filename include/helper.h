#ifndef __HELPER__H__
#define __HELPER__H__

#include<cmath>
//Helper Functions

#define DBL_CLOSE_ENOUGH 0.0001
bool isEquivalent(double a, double b);

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

//Configuration helper macros
#define DEF_CONFIG(name, type, config_type) \
    class name : public config_type<type> { \
        public: \
                name() : config_type<type>(){} \
                name(HDWF); \
        protected: \
                void setImpl(type); \
                type getImpl(); \
    }

#define DEF_CONFIG_W_INDEX(name, type, config_type) \
    class name : public config_type<type> { \
        public: \
                name() : config_type<type>(){} \
                name(HDWF, int idx); \
        protected: \
                void setImpl(type); \
                type getImpl(); \
        private: \
                int index; \
    }

#define IMPL_CONFIG_GETNSET_W_CALL(name, call, type) \
    void name::setImpl(type val) { \
        DWF( call ## Set(device, val)); \
    } \
    type name::getImpl() { \
        type val; \
        DWF(call ## Get(device, &val)); \
        return val; \
    }

//If name same as name of call, shortens up macro signature
#define IMPL_CONFIG_GETNSET(name, type) \
    IMPL_CONFIG_GETNSET_W_CALL(name, name, type)

#define IMPL_CONFIG_GETNSET_W_INDEX_W_CALL(name, call, type) \
    void name::setImpl(type val) { \
        DWF( call ## Set(device, index, val)); \
    } \
    type name::getImpl() { \
        type val; \
        DWF(call ## Get(device, index, &val)); \
        return val; \
    }

//If name same as name of call, shortens up macro signature
#define IMPL_CONFIG_GETNSET_W_INDEX(name, type) \
    IMPL_CONFIG_GETNSET_W_INDEX_W_CALL(name, name, type)

#endif
