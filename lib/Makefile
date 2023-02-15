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
# Select the appropriate Makefile options for your system. then type make.
############################################################################
# Sun users
# CC = gcc
# CFLAGS = -O2 -s
# LIBS = -lm
############################################################################
# FreeBSD users
# CC = gcc
# CFLAGS = -O2 -DFBSD_DATABASE -s
# LIBS = -lm
############################################################################
# Linux users
CC = gcc
CFLAGS = -O2 -DBERKELEYDB -s
LIBS = -lm -ldb-3
############################################################################


all: lexicon 

lexicon: text710.edin dbm_prog
	./dbm_prog -o lexicon -i text710.edin

#text710.edin: text710.dat read_ox_dict
#	read_ox_dict text710.dat > text710.edin

dbm_prog: dbm_prog.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f dbm_prog *.o core gmon.out lexicon 

distribution:
	echo "This needs written."

# dependencies

