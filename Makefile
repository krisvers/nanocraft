CC = clang
CCFLAGS = -std=c99 -Iinclude
CCLIBS = -lSDL2
CCWARNINGS = -Wall -Wextra -Wpedantic -Weverything -Wno-padded -Wno-declaration-after-statement -Wno-missing-variable-declarations -Wno-missing-prototypes -Wno-implicit-int-conversion -Wno-implicit-int-float-conversion -Wno-sign-conversion
CFILES = $(shell find . -type f -name "*.c")
OUTDIR = ./bin
OUTFILE = exe

all:
	$(CC) $(CFILES) -o $(OUTDIR)/$(OUTFILE) $(CCFLAGS) $(CCLIBS) $(CCWARNINGS)

clean:
	rm -rf $(OUTDIR)
	mkdir $(OUTDIR)
