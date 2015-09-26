#Compiler Directives
CXX=g++
CPPFLAGS= -std=c++11
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
BINFILE= run
MAIN_SRC= main.cpp
_MAIN_OBJ=$(MAIN_SRC:.cpp=.o)
MAIN_OBJ=$(patsubst %,$(ODIR)/%,$(_MAIN_OBJ))
TEST_BINFILE= run_test
TEST_SRC= test.cpp
_TEST_OBJ=$(TEST_SRC:.cpp=.o)
TEST_OBJ=$(patsubst %,$(ODIR)/%,$(_TEST_OBJ))
SRC= helper.cpp \
	 dwf_exceptions.cpp \
	 Device.cpp \
	 AnalogInput.cpp \
	 DigitalInput.cpp
_OBJ=$(SRC:.cpp=.o)
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))
_DEPS= helper.h \
	   dwf_exceptions.h \
	   Configuration.h \
	   Device.h \
	   AnalogInput.h \
	   DigitalInput.h \
	   easylogging++.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

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

.PHONY: all help clean

all: $(BINFILE)
test: $(TEST_BINFILE)
help:
	$(E)
	$(E)Helpful Comments
	$(E)

$(ODIR)/%.o: $(LDIR)/%.cpp $(DEPS)
	$(E)C++-compiling $<
	$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(Q)$(CXX) -o $@ -c $< $(CPPFLAGS) -I$(IDIR)

$(BINFILE):	$(MAIN_OBJ) $(OBJ) $(DEPS)
	$(E)Linking $@
	$(Q)$(CXX) -o $@ -I$(IDIR) $^ $(CPPFLAGS) $(LIBS) $(LDFLAGS)

$(TEST_BINFILE): $(TEST_OBJ) $(OBJ) $(DEPS)
	$(E)Linking $@
	$(Q)$(CXX) -o $@ -I$(IDIR) $^ $(CPPFLAGS) $(LIBS) $(LDFLAGS)

clean:
	$(E)Removing Files
	$(Q)rm -f $(ODIR)/*.o $(BINFILE)
	$(Q)if [ -d $(ODIR) ]; then rmdir $(ODIR); fi

