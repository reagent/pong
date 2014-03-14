CFLAGS=-Wall -g
LDFLAGS=-lncurses

SOURCES=$(wildcard *.c src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TARGET=pong

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

clean:
	rm -rf pong *.o *.dSYM
