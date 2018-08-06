SHELL = /bin/sh
CC = gcc
CFLAGS = -fPIC -c -Wall -Wextra -Wshadow -Wpadded \
	 -std=c99 -fno-stack-protector -O2 \
	 -funroll-loops 
OBJS = mallocx.o
OUT = libmallocx.so

debug: CFLAGS += -DENABLE_DEBUG_PRINTFS
	
all: $(OBJS)
	@$(CC) $(OBJS) -shared -o $(OUT) && \
	    echo "BUILD: libmallocx.so" || \
	    echo "FAIL: libmallocx.so"

debug: all

install: all
	@cp libmallocx.so $(PREFIX)/lib && \
	    echo "INSTALL: $(PREFIX)/lib/libmallocx.so" || \
	    echo "FAIL: $(PREFIX)/lib/libmallocx.so"
	@cp mallocx.h $(PREFIX)/include && \
	    echo "INSTALL: $(PREFIX)/include/mallocx.h" || \
	    echo "FAIL: $(PREFIX)/lib/mallocx.h"

clean:
	@rm -rf $(OBJS) && echo "CLEANUP: $(OBJS)"

help:
	@echo -e 'rule\tdesc'
	@echo -e '----\t----'
	@echo -e 'all\tbuild the project'
	@echo -e 'debug\tenable debug printfs (no debug syms)'
	@echo -e 'install\tinstall the project (specify PREFIX)'
	@echo -e 'clean\tcleanup the object files in build directory'
	@echo -e 'help\tprint this help'
	
.PHONY: all,debug,clean,install
