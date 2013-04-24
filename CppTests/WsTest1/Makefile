##############################################################################
# Application specific info.  Specify the object target basename, object
# files to be created, and any precompiled libraries here.
##############################################################################

TARGET = WsRobot2009

CSRC = 

CPPSRC = \
	WsDrive2Motors.cpp \
	WsRobot.cpp \
	WsControllerButton.cpp

ASRC =

LIBS = C:/windriver/vxworks-6.3/target/lib/WPILib.a

OBJS = $(ASRC:.S=.o) $(CSRC:.c=.o) $(CPPSRC:.cpp=.o)

##############################################################################
# Compiler settings.  Specify compiler/linker flags here, as well as default
# directories for system headers/libraries.
##############################################################################
export WIND_BASE="C:/windriver/vxworks-6.3"
export WIND_HOME="C:/windriver"

CFLAGS = -g -mcpu=603 -mstrict-align -mno-implicit-fp -ansi -Wall -MD -MP 
LINKSCRIPT = -T C:/windriver/vxworks-6.3/target/h/tool/gnu/ldscripts/link.OUT

COPTS = -DCPU=PPC603 -DTOOL_FAMILY=gnu -DTOOL=gnu -D_WRS_KERNEL
LDFLAGS = -r -nostdlib -Wl,-X
LIBDIRS = 

INCLUDEDIRS = -IC:/windriver/vxworks-6.3/target/h/WPILib -IC:/windriver/vxworks-6.3/target/h -IC:/windriver/vxworks-6.3/target/h/wrn/coreip

##############################################################################
# Executable defines & rules - shouldn't need to change anything below here.
##############################################################################
CC  = /cygdrive/c/windriver/gnu/3.4.4-vxworks-6.3/x86-win32/bin/ccppc.exe
NM  = /cygdrive/c/windriver/gnu/3.4.4-vxworks-6.3/x86-win32/bin/nmppc.exe
RM  = rm
TCLSH = tclsh

.SUFFIXES: .o .c .i

all: $(TARGET).out

$(TARGET).out: $(TARGET)Partial.o ctdt.o
	$(CC) $(LDFLAGS) $(LINKSCRIPT) -o $(TARGET).out ctdt.o $(TARGET)Partial.o $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDEDIRS) $(COPTS) -c $*.c -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDEDIRS) $(COPTS) -c $*.cpp -o $@

$(TARGET)Partial.o: $(OBJS)
	$(CC) -r -nostdlib -Wl,-X  -o $(TARGET)Partial.o $(OBJS)

ctdt.o: $(TARGET)Partial.o
	$(NM) $(TARGET)Partial.o $(LIBS) | $(TCLSH) $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > ctdt.c
	$(CC) -g -mcpu=603 -mstrict-align -mno-implicit-fp -fdollars-in-identifiers -Wall $(INCLUDEDIRS) $(COPTS) -o ctdt.o ctdt.c

clean:
	@echo "Cleaning build directory..."
	-@$(RM) *.o *.out ctdt.c

