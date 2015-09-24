/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : Configuration.cpp

 * Purpose : Implementation of the Configuration class

 * Creation Date : 23-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "Configuration.h"

template<typename T>
Configuration<T>::Configuration(HDWF d) {
    device = d;
}

template<typename T>
void Configuration<T>::set(T val) {
    if(!isValid(val)) {
        CLOG(WARNING, "dwf") << "Value not valid.";
        throw VariableInvalidException();
    }
    setImpl(val);
    T actualVal = getImpl();
    //TODO: might need to adjust for doubles
    if(actualVal != val) {
        CLOG(WARNING, "dwf") << "Value didn't get set to desired value." <<
            "Actual = " << actualVal << ", desired = " << val;
        throw NotSetExactlyException();
    }
} 

template<typename T>
T Configuration<T>::get() {
    return getImpl();
}

//SetConfiguration
template<typename T>
SetConfiguration<T>::SetConfiguration(HDWF d)
    : Configuration<T>(d){
        initOptionsImpl();
}

template<typename T>
bool SetConfiguration<T>::isValid(T val) {
    return options.find(val) != options.end();
}

template<typename T>
std::set<T> SetConfiguration<T>::getOptions() {
    //Deep copy, don't want user to have access to actual data
    return std::set<T>(options);
}
