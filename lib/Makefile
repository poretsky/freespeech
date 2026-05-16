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
docdir = ${prefix}/share/doc/enlex-data
mandir = ${prefix}/share/man/man1

# Installed database filename
DBF = enlex.db

# Installed utility name
UTILITY = lexholder-en

# Select the appropriate Makefile options for your system. then type make.
############################################################################
# FreeBSD users
# CC = gcc
# CFLAGS = -O2 -DFBSD_DATABASE
# LIBS = -lm
############################################################################
# Linux users
CC ?= gcc
CFLAGS ?= -g -Wall -O2
LIBS = -lgdbm_compat
############################################################################


all: lexicon

lexicon: text710.edin lexholder
	./lexholder -qf $< $@ && touch $@

#text710.edin: text710.dat read_ox_dict
#	read_ox_dict text710.dat > text710.edin

lexholder: lexholder.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

.PHONY: install
install: lexholder lexicon
	install -d ${bindir} ${datadir} ${docdir} ${mandir}
	install -m 0755 -p lexholder ${bindir}/${UTILITY}
	install -m 0644 -p lexicon.dir ${datadir}/enlex.dir
	install -m 0644 -p lexicon.pag ${datadir}/enlex.pag
	install -m 0644 -p text710.doc ${docdir}
	install -m 0644 -p lexholder.1 ${mandir}/lexholder-en.1

.PHONY: clean
clean:
	rm -f lexholder *.o lexicon*
