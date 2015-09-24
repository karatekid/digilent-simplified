#ifndef __CONFIGURATION__H__
#define __CONFIGURATION__H__

#include<set>

#include<digilent/waveforms/dwf.h> 

#include "helper.h"

template<typename T>
class Configuration {
    public:
        Configuration(){}
        Configuration(HDWF d);
        //double checks that set properly
        void set(T val);
        T get();
        virtual bool isValid(T val) = 0;
    protected:
        HDWF device;
        //Digilent calls
        virtual void setImpl(T val) = 0;
        virtual T getImpl() = 0;
};

template<typename T>
class SetConfiguration : public Configuration<T> {
    public:
        SetConfiguration(){}
        SetConfiguration(HDWF d);
        bool isValid(T val);
        //Deep copy of options
        std::set<T> getOptions();
    protected:
        std::set<T> options;
        virtual void initOptionsImpl() = 0;

};

#endif
