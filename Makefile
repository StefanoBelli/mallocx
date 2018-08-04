SHELL = /bin/sh
CC = gcc
CFLAGS = -fPIC -c -Wall -std=c99 -fno-stack-protector -O3
OBJS = mallocx.o
OUT = libmallocx.so

debug: CFLAGS += -DENABLE_DEBUG_PRINTFS
	
all: $(OBJS)
	$(CC) $(OBJS) -shared -o $(OUT)  

debug: all

clean:
	rm -rfv $(OBJS)

.PHONY: all,debug,clean
