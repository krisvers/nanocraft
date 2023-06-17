CC = clang
WINCC = i686-w64-mingw32-gcc
CCFLAGS = -std=c99 -Iinclude
LIBCCFLAGS = -O -shared -fPIC -rdynamic
WINCCFLAGS = -std=c99 -Iinclude -Iwinclude 
CCLIBS = -lSDL2
WINCCLIBS = -Llib -lSDL2 -lSDL2main -Wl,-subsystem,windows -lgdi32 -lkernel32 -lmingw32
CCWARNINGS = -Wall -Wextra -Wpedantic -Weverything -Wno-padded -Wno-declaration-after-statement -Wno-missing-variable-declarations -Wno-missing-prototypes -Wno-implicit-int-conversion -Wno-implicit-int-float-conversion -Wno-sign-conversion -Wno-unused-command-line-argument
WINCCWARNINGS = -Wall -Wextra -Wpedantic -Wno-padded -Wno-declaration-after-statement -Wno-missing-prototypes -Wno-sign-conversion -Wno-unused-command-line-argument
CFILES = $(shell find . -type f -name "*.c")
OFILES = $(CFILES:.c=.o)
OUTDIR = ./bin
OUTFILE = exe
OUTLIB = exe
LIBEXT = so
OBJDIR = ./obj

all: $(subst ./dynamic.o,,$(OFILES)) link

win: set-vars-win $(subst ./dynamic.o,,$(OFILES)) link

set-vars-win:
	$(eval CC = $(WINCC))
	$(eval CCFLAGS = $(WINCCFLAGS))
	$(eval CCLIBS = $(WINCCLIBS))
	$(eval CCWARNINGS = $(WINCCWARNINGS))

set-vars-lib:
	$(eval CCFLAGS = $(LIBCCFLAGS) $(CCFLAGS))

lib: set-vars-lib compile-lib link-lib

compile-lib: $(subst ./main.o,,$(OFILES))

link:
	$(CC) $(OBJDIR)/*.o -o $(OUTDIR)/$(OUTFILE) $(CCFLAGS) $(CCLIBS) -v

link-lib:
	$(CC) $(subst $(OBJDIR)/main.o,,$(OBJDIR)/*.o) -o $(OUTLIB).$(LIBEXT) $(CCFLAGS) $(CCLIBS) -v

%.o: %.c
	$(CC) -c $? -o $(OBJDIR)/$(notdir $@) $(CCFLAGS) $(CCLIBS) $(CCWARNINGS)

clean:
	rm -rf $(OUTDIR)
	rm -rf $(OBJDIR)
	mkdir $(OBJDIR)
	mkdir $(OUTDIR)
	cp SDL2.dll $(OUTDIR)/
