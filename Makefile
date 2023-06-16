CC = clang
WINCC = i686-w64-mingw32-gcc
CCFLAGS = -std=c99 -Iinclude
WINCCFLAGS = -std=c99 -Iinclude -Iwinclude 
CCLIBS = -lSDL2
WINCCLIBS = -Llib -lSDL2 -lSDL2main -Wl,-subsystem,windows -lgdi32 -lkernel32 -lmingw32
CCWARNINGS = -Wall -Wextra -Wpedantic -Weverything -Wno-padded -Wno-declaration-after-statement -Wno-missing-variable-declarations -Wno-missing-prototypes -Wno-implicit-int-conversion -Wno-implicit-int-float-conversion -Wno-sign-conversion
WINCCWARNINGS = -Wall -Wextra -Wpedantic -Wno-padded -Wno-declaration-after-statement -Wno-missing-prototypes -Wno-sign-conversion
CFILES = $(shell find . -type f -name "*.c")
OUTDIR = ./bin
OUTFILE = exe

all:
	$(CC) $(CFILES) -o $(OUTDIR)/$(OUTFILE) $(CCFLAGS) $(CCLIBS) $(CCWARNINGS)

win:
	$(WINCC) $(CFILES) -o $(OUTDIR)/$(OUTFILE).exe $(WINCCFLAGS) $(WINCCLIBS) $(WINCCWARNINGS)

clean:
	rm -rf $(OUTDIR)
	mkdir $(OUTDIR)
	cp SDL2.dll $(OUTDIR)/
