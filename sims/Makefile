CC=gcc

_INCDIRS=../include
INCDIRS=$(addprefix -I,$(_INCDIRS))

_LIBDIRS=../lib
LIBDIRS=$(addprefix -L,$(_LIBDIRS))

_LIBS=m nb
LIBS=$(addprefix -l,$(_LIBS))

CFLAGS=-O3 -fopenmp -Wall $(INCDIRS)
LDFLAGS=-O3 -fopenmp $(INCDIRS) $(LIBDIRS) $(LIBS) -Wl,-rpath,$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/../lib

_SRCFILES=sim.c
SRCS=$(_SRCFILES)

_OBJFILES=$(_SRCFILES:%.c=%.o)
OBJS=$(_OBJFILES)

EXES=sim.exe

LIBNAME=libnb.so

DIRGUARD=@mkdir -p $(@D)

all: $(EXES)

%.exe: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o : %.c
	$(CC) $< -c -o $@ $(CFLAGS)

.SECONDARY: $(OBJS)
.PHONY: clean

clean:
	rm *.o
	rm *.exe
