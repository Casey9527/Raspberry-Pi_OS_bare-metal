CC = gcc
CFLAGS = -Wall



all : $(TARGET)


clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.auto
	rm -f *.exe

SRC := $(wildcard *.c ./src/*.c )
OBJECTS := $(patsubst %.c,%.o,$(SRC))

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o a.exe

%: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


$(TARGET) : $(OBJECTS)
	
	$(SRC)
	gcc $(OBJECTS) -o kernel7.exe


