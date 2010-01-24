############################################################################
#
#   Copyright (C) 1996 Alistair Conkie
#
#   You may distribute under the terms of the GNU General Public
#   Licence as specified in the README file.
#
#
############################################################################
#
#
############################################################################

# Installation paths
prefix = /usr/local
bindir = ${prefix}/bin

# Select the appropriate Makefile options for your system. then type make.
############################################################################
# FreeBSD users
# CC = gcc
# CFLAGS = -O2 -DFBSD_DATABASE
# LFLAGS = -s
# LIBS = -lm
# GROUP =wheel
############################################################################
# Linux users
CC = gcc
CFLAGS = -O2
LFLAGS = -s
LIBS = -lm -ldb
GROUP = root
############################################################################


OBJS = go.o t2s.o space.o tags.o grammar.o \
	transcribe.o conv1.o conv2.o durpros.o prosody.o \
	syllab.o utils.o buffer.o \
	fw.o broad_cats.o durs.o load_diphs.o spnio.o \
	durations.o pitch.o audio.o \
	phon_rules.o edin2sampa.o

RULE_OBJS = rule_engine.o read_rules.o

NRL_OBJS = interface.o english.o nrl_edin.o phoneme.o saynum.o spellwor.o

MAIN = main.o

all: freephone

freephone: $(OBJS) $(NRL_OBJS) $(RULE_OBJS) $(MAIN)
	$(CC) $(LFLAGS) -o $@ $^ $(LIBS)

.PHONY: install
install: freephone
	install -d ${bindir}
	install -g ${GROUP} -o root -m 0755 -p $^ ${bindir}

.PHONY: clean
clean:
	rm -f freephone *.o

%.o:%.c
	$(CC) -c ${CFLAGS} -o $@ $<

# dependencies
audio.o: audio.c t2s.h prototypes.h
broad_cats.o: broad_cats.c t2s.h prototypes.h
buffer.o: buffer.c t2s.h prototypes.h
conv1.o: conv1.c t2s.h prototypes.h
conv2.o: conv2.c t2s.h prototypes.h
durations.o: durations.c t2s.h prototypes.h
durpros.o: durpros.c t2s.h prototypes.h
durs.o: durs.c t2s.h prototypes.h
edin2sampa.o: edin2sampa.c t2s.h prototypes.h
english.o: english.c t2s.h prototypes.h
fw.o: fw.c t2s.h prototypes.h
go.o: go.c t2s.h prototypes.h
grammar.o: grammar.c t2s.h prototypes.h
interface.o: interface.c t2s.h prototypes.h
load_diphs.o: load_diphs.c t2s.h prototypes.h
main.o: main.c t2s.h prototypes.h
nrl_edin.o: nrl_edin.c t2s.h prototypes.h
phoneme.o: phoneme.c t2s.h prototypes.h
phon_rules.o: phon_rules.c t2s.h prototypes.h
pitch.o: pitch.c t2s.h prototypes.h
prosody.o: prosody.c t2s.h prototypes.h
read_rules.o: read_rules.c t2s.h prototypes.h
rule_engine.o: rule_engine.c t2s.h prototypes.h
saynum.o: saynum.c t2s.h prototypes.h
space.o: space.c t2s.h prototypes.h
spellwor.o: spellwor.c t2s.h prototypes.h
spnio.o: spnio.c t2s.h prototypes.h
syllab.o: syllab.c t2s.h prototypes.h
t2s.o: t2s.c t2s.h prototypes.h
tags.o: tags.c t2s.h prototypes.h
transcribe.o: transcribe.c t2s.h prototypes.h
utils.o: utils.c t2s.h prototypes.h
