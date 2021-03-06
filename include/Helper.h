#ifndef __HELPER__H__
#define __HELPER__H__

#include<algorithm>
#include<iostream>
#include<cmath>
#include<digilent/waveforms/dwf.h> 

#include "easylogging++.h"
#include "Exceptions.h"
//Helper Functions

#define DBL_CLOSE_ENOUGH 0.0001
bool isEquivalent(double a, double b);

//Logging
#define LOGGING_CONFIG "configs/general.conf"
#define LOGGING_LVL_CONFIG "configs/level.conf"
void initializeLogging(int argc, char *argv[]);


//DWF Calls
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

//Instrument specific types
struct InputStatusStruct {
    DwfState state;
    int samplesLeft, samplesValid, indexWrite;
    BOOL autoTriggered;
};
//Status macro
#define PERFORM_READ_INTERNALS(PREFIX, READ_FXN) \
    int lastIndexWrite = inputStatus.indexWrite;\
    DWF(PREFIX ## Status(device, true, &(inputStatus.state))); \
    DWF(PREFIX ## StatusSamplesLeft(device, &(inputStatus.samplesLeft))); \
    DWF(PREFIX ## StatusSamplesValid(device, &(inputStatus.samplesValid))); \
    DWF(PREFIX ## StatusIndexWrite(device, &(inputStatus.indexWrite))); \
    DWF(PREFIX ## StatusAutoTriggered(device, &(inputStatus.autoTriggered))); \
    int beginIndex = 0, endIndex = 0; \
    switch(acquisitionMode.get()) { \
        case acqmodeSingle: \
            if(inputStatus.state == DwfStateDone) { \
                endIndex = bufferSize.get(); \
            } \
            break; \
        case acqmodeScanShift: \
            endIndex = std::min( \
                     inputStatus.samplesValid,\
                    bufferSize.get()); \
            break; \
        case acqmodeScanScreen: \
            beginIndex = lastIndexWrite; \
            endIndex = inputStatus.indexWrite % bufferSize.get(); \
            break; \
        default: \
            throw dwf::AcquisitionModeNotImplementedException(); \
            break; \
    } \
    return READ_FXN(beginIndex, endIndex)

int getMaxIdxToReadTo(int i, int j, int bufferSize);
int getNumSamplesToRead(int i, int j, int bufferSize);

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

#define IMPL_CR_CONFIG_ALL(name, type) \
    name::name(HDWF d) : ContinuousRangeConfiguration<type>(d) { \
        DWF(name ## Info(device, &(range.min), &(range.max))); \
    } \
    IMPL_CONFIG_GETNSET(name, type)

#define IMPL_CR_CONFIG_ALL_W_INDEX(name, type) \
    name::name(HDWF d, int idx) \
    : ContinuousRangeConfiguration<type>(d), index(idx) { \
        DWF(name ## Info(device, &(range.min), &(range.max))); \
    } \
    IMPL_CONFIG_GETNSET_W_INDEX(name, type)

#define SAVE_SET_INFO_FROM_BITMASK(name, type) \
    int mask; \
    DWF(name ## Info(device, &mask)); \
    for(type i = 0; i < sizeof(int); ++i) { \
        if(IsBitSet(mask, i)) { \
            options.insert(i); \
        } \
    }

#define IMPL_SET_CONFIG_ALL(name, type) \
    name::name(HDWF d) : SetConfiguration<type>(d) { \
        SAVE_SET_INFO_FROM_BITMASK(name, type); \
    } \
    IMPL_CONFIG_GETNSET(name, type)

#define IMPL_SET_CONFIG_ALL_W_INDEX(name, type) \
    name::name(HDWF d, int idx) : SetConfiguration<type>(d), index(idx) { \
        SAVE_SET_INFO_FROM_BITMASK(name, type); \
    } \
    IMPL_CONFIG_GETNSET_W_INDEX(name, type)

#define SAVE_DR_INFO(name, type) \
    double numSteps; \
    DWF(name ## Info(device, &(range.min), &(range.max), &numSteps)); \
    if(numSteps <= 1) { \
        range.stepSize = 0; \
    } else { \
        range.stepSize = (range.max - range.min) / (numSteps - 1); \
    }

#define IMPL_DR_CONFIG_ALL(name, type) \
    name::name(HDWF d) : DiscreteRangeConfiguration<type>(d) { \
        SAVE_DR_INFO(name, type); \
    } \
    IMPL_CONFIG_GETNSET(name, type);

#define IMPL_DR_CONFIG_ALL_W_INDEX(name, type) \
    name::name(HDWF d, int idx) \
    : DiscreteRangeConfiguration<type>(d), index(idx) { \
        SAVE_DR_INFO(name, type); \
    } \
    IMPL_CONFIG_GETNSET_W_INDEX(name, type);


#endif
