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
datadir = ${prefix}/share/freespeech
docdir = ${prefix}/share/doc/enlex

# Installed database filename
DBF = enlex.db

# Installed utility name
UTILITY = lexholder-en

# Select the appropriate Makefile options for your system. then type make.
############################################################################
# FreeBSD users
# CC = gcc
# CFLAGS = -O2 -DFBSD_DATABASE
# LFLAGS = -s
# LIBS = -lm
# GROUP = wheel
############################################################################
# Linux users
CC = gcc
CFLAGS += -Wall -O2
LFLAGS = $(LDFLAGS) -s
LIBS = -ldb
GROUP = root
############################################################################


all: lexicon

lexicon: text710.edin lexholder
	./lexholder -qf $< $@

text710.edin: text710.dat text710.edin.patch read_ox_dict
	./read_ox_dict $< > $@ 2>/dev/null
	patch -Esup0 < text710.edin.patch

lexholder: lexholder.c
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $< $(LIBS)

.PHONY: install
install: lexholder lexicon
	install -d ${bindir} ${datadir} ${docdir}
	install -g ${GROUP} -o root -m 0755 -p lexholder ${bindir}/${UTILITY}
	install -g ${GROUP} -o root -m 0644 -p lexicon ${datadir}/${DBF}
	install -g ${GROUP} -o root -m 0644 -p text710.doc ${docdir}

.PHONY: clean
clean:
	rm -f lexholder *.o text710.edin lexicon
