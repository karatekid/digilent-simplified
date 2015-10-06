#Compiler Directives
CXX=g++
CPPFLAGS= -std=c++11 \
		  -fPIC
		  #-v \
		  #-ftime-report
LDFLAGS=
#-L/usr/local/lib
LIBS= -ldwf
#Directories
IDIR=include
LDIR=lib
ODIR=obj
#Files
SRC= helper.cpp \
	 dwf_exceptions.cpp \
	 Device.cpp \
	 AnalogInput.cpp \
	 DigitalInput.cpp \
	 DigitalInputConfigurations.cpp \
	 AnalogInputConfigurations.cpp
_OBJ=$(SRC:.cpp=.o)
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))
_DEPS= helper.h \
	   dwf_exceptions.h \
	   Configuration.h \
	   Device.h \
	   AnalogInput.h \
	   DigitalInput.h \
	   DigitalInputConfigurations.h \
	   AnalogInputConfigurations.h \
	   easylogging++.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))
TEST_DIR=test
SONAME_ROOT=dwfobj
SO_MAJOR=1
SO_MINOR=0
PART_SONAME=lib$(SONAME_ROOT).so
REAL_SONAME=$(PART_SONAME).$(SO_MAJOR)
SO_FILE=$(REAL_SONAME).$(SO_MINOR) 
INSTALL_INC_ROOT= /usr/local/include
INSTALL_INC=$(INSTALL_INC_ROOT)/$(SONAME_ROOT)
INSTALL_LIB= /usr/local/lib

#Flag Handling
ifdef DEBUG
CPPFLAGS := $(CPPFLAGS) -g
endif
ifdef VERBOSE
        Q =
        E = @true 
else
        Q = @
        E = @echo 
endif

.PHONY: all install test help clean

all: $(SO_FILE)
install: $(SO_FILE)
	$(E)Creating symlinks in $(INSTALL_LIB) of $(SO_FILE)
	$(Q)cp $(SO_FILE) $(INSTALL_LIB)/$(SO_FILE)
	$(Q)ln -sf $(INSTALL_LIB)/$(SO_FILE) $(INSTALL_LIB)/$(REAL_SONAME)
	$(Q)ln -sf $(INSTALL_LIB)/$(SO_FILE) $(INSTALL_LIB)/$(PART_SONAME)
	$(Q)mkdir -p $(INSTALL_INC)
	$(Q)cp $(DEPS) $(INSTALL_INC)/
test: install
	$(E)Recursing into $(TEST_DIR) and running make there
	$(Q)$(MAKE) -C $(TEST_DIR)
help:
	$(E)
	$(E)all:     Create a shared object file
	$(E)install: Create symlinks of shared object file in $(INSTALL_LIB), and
	$(E)          symlinks of headers in $(INSTALL_INC)
	$(E)test:    Recurse into $(TEST_DIR) to run make and produce test binary
	$(E)clean:   Removes all created files

$(ODIR)/%.o: $(LDIR)/%.cpp $(DEPS)
	$(E)C++-compiling $<
	$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(Q)$(CXX) -o $@ -c $< $(CPPFLAGS) -I$(IDIR)

$(SO_FILE): $(OBJ) $(DEPS)
	$(E)Creating shared library for $@
	$(Q)$(CXX) -shared -Wl,-soname,$(REAL_SONAME) -o $(SO_FILE) $(OBJ)

clean:
	$(E)Removing Files
	$(Q)rm -f $(ODIR)/*.o $(SO_FILE)
	$(Q)if [ -d $(ODIR) ]; then rmdir $(ODIR); fi

