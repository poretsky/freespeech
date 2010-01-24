# General Makefile for Debian packaging system.

DESTDIR =

all:
	$(MAKE) -C src all
	$(MAKE) -C lib all

install:
	$(MAKE) -C src install prefix=$(DESTDIR)/usr
	$(MAKE) -C lib install prefix=$(DESTDIR)/usr

clean:
	$(MAKE) -C src clean
	$(MAKE) -C lib clean

.PHONY: clean install
