CC=gcc

_INCDIRS=include
INCDIRS=$(addprefix -I,$(_INCDIRS))

_LIBDIRS=lib
LIBDIRS=$(addprefix -L,$(_LIBDIRS))

_LIBS=m
LIBS=$(addprefix -l,$(_LIBS))

CFLAGS=-O3 -fopenmp -Wall $(INCDIRS)
LDFLAGS=-O3 -shared -fopenmp $(INCDIRS) $(LIBDIRS) $(LIBS)

SRCDIR=src
_SRCFILES=body.c gravity.c config.c
SRCS=$(addprefix $(SRCDIR)/,$(_SRCFILES))

OBJDIR=build
_OBJFILES=$(_SRCFILES:%.c=%.o)
OBJS=$(addprefix $(OBJDIR)/,$(_OBJFILES))

LIBDIR=lib
LIBNAME=libnb.so

DIRGUARD=@mkdir -p $(@D)

all: $(LIBDIR)/$(LIBNAME)

$(LIBDIR)/$(LIBNAME): $(OBJS)
	$(DIRGUARD)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(DIRGUARD)
	$(CC) $< -c -o $@ $(CFLAGS)

.SECONDARY: $(OBJS)
.PHONY: clean

clean:
	rm $(OBJDIR)/*.o
	rm $(LIBDIR)/*.so
	rmdir $(OBJDIR) $(LIBDIR)
