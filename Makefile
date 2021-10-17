# Makefile
cc=gcc

LDFLAGS=-lncurses

SRCS := $(wildcard *.c)
TARGET := $(SRCS:%.c=%)

$(TARGET):$(SRCS)
	$(cc) $(LDFLAGS) $(SRCS) -o $(TARGET) 

clean:
	rm $(TARGET)


