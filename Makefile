# Makefile for tlgu
# 111205 dm

#SHELL = /bin/sh

INCPATH=-I .
INSTDIR=/usr/local/bin
CC = gcc
#CPP =
#LN = ln
#RANLIB = ranlib
CFLAGS = -O2 -g $(INCPATH)
#CPPFLAGS =
#LDFLAGS =
#LIBS =
SOURCE=tlgu.c
#OBJECT=
TARGET= tlgu

#----------------------------------------------------------------------------------
all: $(TARGET)

clean:
	rm -f $(OBJECT) $(TARGET)

cleaner: clean
	rm -f core *.out *~ *.bak *.old

.c:
	$(CC) -c $(CFLAGS) -o $@ $<

$(TARGET): tlgu.c
	$(CC) -o $(TARGET) $(LDFLAGS) $(SOURCE)

install: clean all
	cp -f $(TARGET) $(INSTDIR)

