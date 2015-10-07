#ifndef __CONFIGURATION__H__
#define __CONFIGURATION__H__

#include<set>
#include<sstream>
#include<string>

#include<digilent/waveforms/dwf.h> 

#include "Helper.h"

namespace dwf{
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
                CLOG(ERROR, "dwf") << "Value didn't get set to desired value." <<
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
                CLOG(ERROR, "dwf") << "Value(" << val << ") not valid.\n" <<
                    "Valid options: " << optionsAsString();
                throw VariableInvalidException();
            }
        }
        //Deep copy of options
        std::set<T> getOptions() { 
            return std::set<T>(options);
        }
        std::string optionsAsString() {
            std::ostringstream convert;
            bool first = true;
            for(auto it = options.begin(); it != options.end(); ++it) {
                if(!first) {
                    convert << ", ";
                }
                convert << *it;
                first = false;
            }
            return convert.str();
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
    std::string toString() {
        std::ostringstream convert;
        convert << "[" << min << ", " << max << "]";
        return convert.str();
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
                CLOG(ERROR, "dwf") << "Value(" << val << ") not valid.\n" <<
                    "Valid options: " << range.toString();
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
    std::string toString() {
        std::ostringstream convert;
        convert << "[" << min << ", " << max << 
            "] @ step: " << stepSize;
        return convert.str();
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
                CLOG(ERROR, "dwf") << "Value(" << val << ") not valid.\n" <<
                    "Valid options: " << range.toString();
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
                CLOG(ERROR, "dwf") << "Value not valid.";
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
}

#endif
