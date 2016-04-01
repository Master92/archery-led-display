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
SERV_OBJECTS=main.o displayView.o TimerRunner.o InetServer.o
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

led-server : $(SERV_OBJECTS) $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) $(SERV_OBJECTS) -o $@ $(LDFLAGS)
	
install:
	cp archery-led-display /etc/init.d/archery-led-display
	cp led-server /usr/sbin/led-server
	if [ ! -d /etc/archery-led-display ]; then mkdir /etc/archery-led-display; mkdir /etc/archery-led-display/fonts; mkdir /etc/archery-led-display/sounds; fi
	cp matrix/fonts/5x8.bdf /etc/archery-led-display/fonts/
	cp matrix/fonts/10x20.bdf /etc/archery-led-display/fonts/
	cp res/sounds/* /etc/archery-led-display/sounds/
	chmod +x /etc/init.d/archery-led-display
	update-rc.d archery-led-display defaults

%.o : %.cpp
	$(CXX) $(INCLUDE) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(SERV_OBJECTS) $(BINARIES)
	$(MAKE) -C matrix/lib clean
	
uninstall:
	rm -rf /etc/archery-led-display/
	update-rc.d -f archery-led-display remove
	rm -f /etc/init.d/archery-led-display
	rm -f /usr/sbin/led-server

FORCE:
.PHONY: FORCE