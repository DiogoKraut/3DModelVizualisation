TARGET = wireframe
LIBS = -lm -lSDL2 -lSDL2_gfx
CC = gcc
CFLAGS = -Wall -g

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -Wall $(LIBS) -o $@
	
clean:
	-rm -f *.o core

purge: clean
	-rm -f $(TARGET)
