## -*- Makefile -*-
##
## User: nils
## Time: 04.03.2016 09:57:51
## Makefile created by Oracle Solaris Studio.
##


#### Compiler and tool definitions shared by all build targets #####
CCC = g++
CXX = g++
BASICOPTS =  -std=c++11 -Wall -O3 -g
CCFLAGS = $(BASICOPTS)
CXXFLAGS = $(BASICOPTS)
OBJECTS=main.o displayView.o TimerRunner.o
INC=include $(RGB_INCDIR)
BINARIES=led-server

RGB_INCDIR=matrix/include
RGB_LIBDIR=matrix/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a

INCLUDE=$(foreach d, $(INC), -I$d)
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

all : $(BINARIES)

$(RGB_LIBRARY): FORCE
	$(MAKE) -C $(RGB_LIBDIR)

led-server : $(OBJECTS) $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

%.o : %.cpp
	$(CXX) $(INCLUDE) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(BINARIES)
	$(MAKE) -C matrix/lib clean

FORCE:
.PHONY: FORCE