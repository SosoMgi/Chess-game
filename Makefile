CC=g++
CFLAGS=-std=c++11 -Wall -g -DDEBUG

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

TARGET=echecs
BINDIR=bin
SRCDIR=src
INCLUDEDIR=include
OBJDIR=build

SOURCES  := $(call rwildcard,$(SRCDIR)/,*.cc)
INCLUDES := $(call rwildcard,$(INCLUDEDIR)/,*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -I$(INCLUDEDIR) -o $@

.PHONY: clean test

clean:
	rm -f $(BINDIR)/$(TARGET)
	rm -rf $(OBJDIR)/*
	rm -rd html


docs:
	@doxygen ./Doxyfile
	xdg-open html/index.html 

test:
	cd test && ./test-level.sh 4 && ./test-level.sh 5 && ./test-level.sh 6 && cd ..
