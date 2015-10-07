/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : Exceptions.cpp

 * Purpose : Define dwf exception classes

 * Creation Date : 23-09-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include "Exceptions.h"

namespace dwf{
DwfException::DwfException(DWFERC errCode) {
    FDwfGetLastErrorMsg(errorMessage);
}

const char *DwfException::what() const throw() {
    return errorMessage;
}

void throwDwfException(DWFERC errCode) {
    switch(errCode) {
        case dwfercNoErc:
            // Don't throw, since no exception.
            CLOG(DEBUG, "dwf") << "No exception occured";
            break;
        case dwfercUnknownError:
            throw DwfUnknownException(errCode);
        case dwfercApiLockTimeout:
            throw DwfApiLockTimeout(errCode);
        case dwfercAlreadyOpened:
            throw DwfDeviceAlreadyOpened(errCode);
        case dwfercNotSupported:
            throw DwfDeviceNotSupported(errCode);
        case dwfercInvalidParameter0:
        case dwfercInvalidParameter1:
        case dwfercInvalidParameter2:
        case dwfercInvalidParameter3:
        case dwfercInvalidParameter4:
            throw DwfInvalidParameter(errCode);
        default:
            throw "Not a valid error code";
    }
}
}
