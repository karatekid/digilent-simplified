#ifndef __DWF_EXCEPTIONS__H__
#define __DWF_EXCEPTIONS__H__

#include<exception>

#include<digilent/waveforms/dwf.h> 

#include "easylogging++.h"

namespace dwf{
class DwfException : public std::exception {
    public:
        explicit DwfException(DWFERC errCode);
        const char * what() const throw();
    protected:
        char errorMessage[512];
};

// Creates separate exception types that use DwfException
#define DwfExceptionCreator(name) \
    class name : public DwfException { \
        using DwfException::DwfException; \
    }

DwfExceptionCreator(DwfUnknownException);
DwfExceptionCreator(DwfApiLockTimeout);
DwfExceptionCreator(DwfDeviceAlreadyOpened);
DwfExceptionCreator(DwfDeviceNotSupported);
DwfExceptionCreator(DwfInvalidParameter);

void throwDwfException(DWFERC errCode);

class DeviceMissingException : public std::exception {
    const char * what() const throw() {
        return "No Digilent Discovery Attached";
    }
};

class VariableInvalidException : public std::exception {
    const char * what() const throw() {
        return "Variable to set is out of range";
    }
};

class NotSetExactlyException : public std::exception {
    const char * what() const throw() {
        return "No Digilent Discovery Attached";
    }
};

class AcquisitionModeNotImplementedException : public std::exception {
    const char * what() const throw() {
        return "An acquisitionMode is set that we don't read";
    }
};

class DataMissedDuringStreamException : public std::exception {
    const char * what() const throw() {
        return "Data was lost during scanScreen Acquisition";
    }
};
}
#endif
