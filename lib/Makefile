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
# CFLAGS = -g -Wall -pedantic
# LIBS = -lm
############################################################################
# FreeBSD users
# CC = gcc
# CFLAGS = -O2 -Wall -pedantic -DFBSD_DATABASE
# LIBS = -lm
############################################################################
# Linux users
CC = gcc
CFLAGS = -g -Wall -pedantic
LIBS = -lm -lgdbm
############################################################################

OBJ = dbm_prog.c


all: lexicon 

lexicon: text710.edin dbm_prog
	/bin/rm -i lexicon*
	./dbm_prog -o lexicon -i text710.edin
	touch lexicon

text710.edin: text710.dat read_ox_dict
	read_ox_dict text710.dat > text710.edin

dbm_prog: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

clean:
	rm -f dbm_prog *.o core gmon.out lexicon 

distribution:
	echo "This needs written."

# dependencies

