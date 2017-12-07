CC=gcc
CFLAGS=-I. -I./include
TARGET=client
SDIR:= ./src
BDIR= ./out
DEPS = functions.h
OBJ= $(SDIR)/*.c
LDFLAGS= -lpthread
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)


print: $(SDIR)/*.c
	lpr -p $?
	touch print
client: $(OBJ)
	gcc  -o $@ $^     $(CFLAGS)  $(LDFLAGS)
.PHONY: clean

clean:
	rm -f *.o 
	rm -f $(TARGET)
