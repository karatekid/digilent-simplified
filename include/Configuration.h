#ifndef __CONFIGURATION__H__
#define __CONFIGURATION__H__

#include<set>

#include<digilent/waveforms/dwf.h> 

#include "helper.h"

template<typename T>
class Configuration {
    public:
        explicit Configuration() : ready(false) {}
        explicit Configuration(HDWF d) : device(d), ready(true) {}
        //double checks that set properly
        void set(T val) {
            assertValid(val);
            setImpl(val);
            T actualVal = getImpl();
            //TODO: might need to adjust for doubles
            if(actualVal != val) {
                CLOG(WARNING, "dwf") << "Value didn't get set to desired value." <<
                    "Actual = " << actualVal << ", desired = " << val;
                throw NotSetExactlyException();
            }
        }
        T get() {
            return getImpl();
        }
        bool isReady() {
            return ready;
        }
        virtual bool isValid(T val) = 0;
        virtual void assertValid(T val) = 0;
    protected:
        HDWF device;
        bool ready;
        //Digilent calls
        virtual void setImpl(T val) = 0;
        virtual T getImpl() = 0;
};

template<typename T>
class SetConfiguration : public Configuration<T> {
    public:
        explicit SetConfiguration() : Configuration<T>(){}
        explicit SetConfiguration(HDWF d) : Configuration<T>(d) {}
        bool isValid(T val) { 
            return options.find(val) != options.end();
        }
        void assertValid(T val) {
            if(!isValid(val)) {
                CLOG(WARNING, "dwf") << "Value(" << val << ") not valid.\n" <<
                    "could have chosen any of these values: ";// << options;
                for(auto it = options.begin(); it != options.end(); ++it) {
                    CLOG(WARNING, "dwf") << *it;
                }
                throw VariableInvalidException();
            }
        }
        //Deep copy of options
        std::set<T> getOptions() { 
            return std::set<T>(options);
        }
    protected:
        std::set<T> options;

};

template<typename T>
struct ContinuousRange {
    T min, max;
    bool inRange(T val) {
        return val >= min && val <= max;
    }
};

template<typename T>
class ContinuousRangeConfiguration : public Configuration<T> {
    public: 
        explicit ContinuousRangeConfiguration() : Configuration<T>(){}
        explicit ContinuousRangeConfiguration(HDWF d) : Configuration<T>(d) {}
        bool isValid(T val) { 
            return range.inRange(val);
        }
        void assertValid(T val) {
            if(!isValid(val)) {
                CLOG(WARNING, "dwf") << "Value(" << val << ") not valid.\n" <<
                    "could have chosen b/t [" << range.min << ", " <<
                    range.max << "]";
                throw VariableInvalidException();
            }
        }
        ContinuousRange<T> getRange() {
            return range;
        }
    protected:
        ContinuousRange<T> range;
};

template<typename T>
struct DiscreteRange {
    T min, max, stepSize;
    bool inRange(T val) {
        double numSteps = (val-min+0.0)/stepSize;
        return ((val >= min && val <= max) &&
                isEquivalent(numSteps, (int) numSteps));
    }
};

template<typename T>
class DiscreteRangeConfiguration : public Configuration<T> {
    public: 
        explicit DiscreteRangeConfiguration() : Configuration<T>(){}
        explicit DiscreteRangeConfiguration(HDWF d) : Configuration<T>(d) {}
        bool isValid(T val) { 
            return range.inRange(val);
        }
        void assertValid(T val) {
            if(!isValid(val)) {
                CLOG(WARNING, "dwf") << "Value(" << val << ") not valid.\n" <<
                    "could have chosen b/t [" << range.min << ", " <<
                    range.max << "] w/ a step of " << range.stepSize;
                throw VariableInvalidException();
            }
        }
        DiscreteRange<T> getRange() {
            return range;
        }
    protected:
        DiscreteRange<T> range;
};

//Only works with DigitalInTriggerStruct
template<typename T>
class BitSetConfiguration : public Configuration<T> {
    public:
        explicit BitSetConfiguration() : Configuration<T>(){}
        explicit BitSetConfiguration(HDWF d) : Configuration<T>(d) {}
        bool isValid(T val) { 
            //If bitmask covers val, then you're ok
            return (((val.levelLow  & bitmask.levelLow)  == val.levelLow) &&
                    ((val.levelHigh & bitmask.levelHigh) == val.levelHigh) &&
                    ((val.edgeRise  & bitmask.edgeRise)  == val.edgeRise) &&
                    ((val.edgeFall  & bitmask.edgeFall)  == val.edgeFall));
        }
        void assertValid(T val) {
            if(!isValid(val)) {
                CLOG(WARNING, "dwf") << "Value not valid.";
                throw VariableInvalidException();
            }
        }
        T getBitmask() { 
            //TODO: might want to ensure copying, instead of just giving access
            return bitmask;
        }
    protected:
        T bitmask;

};

#endif
