#
### Makefile for src
#

### Setup
HOST=$(shell hostname)
PROJ_ROOT = $(PWD)

### Settings
TARGET    := udp
BUILD_DIR := build
CXX       := g++

#THREADED  :=
THREADED  := -j`grep -c '^processor' /proc/cpuinfo`

### Flags
BASEFLAGS =-pedantic -Os -std=c++17 -D_REETRANT
# CXX_EXTRA :=-DTINS_STATIC

### Libs
LIBS := -lmylog -ltins -lpcap -lpthread -lboost_system

### Objects
OBJ_LIST := build/main.o  build/dissect.o

ifneq ("$(wildcard $(PROJ_ROOT)/.local/$(HOST).mk)","")
include $(TOP_DIR).local/$(HOST).mk
else
$(error Please create a folder called ".local" and a file called $(HOST).mk [see example.mk for help])
endif

### Collect
DEFINES   :=-DMYLOG_ENABLED $(LOCAL_DEFINES)
CXXFLAGS  := $(BASEFLAGS) $(CXX_EXTRA)
CPPSRCS   = $(wildcard src/*.cpp) $(wildcard src/*.cpp)
CPPOBJS   = $(patsubst src/%.cpp,%.o, $(CPPSRCS))

### Default targets

default: prebuild
	make $(TARGET) $(THREADED)

.PHONY: prebuild postbuild
prebuild:
	rm -rf build
	@mkdir -p $(BUILD_DIR)

postbuild:
	@true


### Objects

build/%.o: src/%.cpp
	$(CXX) $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INC_DIRS) $(LD_DIRS) -c $<
	mv $*.o build/$*.o


### Apps

.PHONY: $(TARGET)
$(TARGET): $(OBJ_LIST)
	$(CXX) $(DEFINES) $(INC_DIRS) $(CXXFLAGS) $(OBJ_LIST) -o $(TARGET) $(LD_DIRS) $(LIBS)

### Cleanup

clean:
	rm -f src/*.o
	rm -f *.o
	rm -f $(TARGET)





##### end
