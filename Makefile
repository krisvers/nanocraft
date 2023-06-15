CC = clang
CCFLAGS = -std=c99
CCWARNINGS = -Wall -Wextra -Wpedantic -Weverything -Wno-padded -Wno-declaration-after-statement
CFILES = $(shell find . -type f -name "*.c")
OUTDIR = ./bin
OUTFILE = exe

all:
	echo $(CFILES)
	$(CC) $(CFILES) -o $(OUTDIR)/$(OUTFILE) $(CCFLAGS) $(CCWARNINGS)

clean:
	rm -rf $(OUTDIR)
	mkdir $(OUTDIR)
