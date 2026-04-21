#variables
CC = gcc
CFLAGS = -Iinclude -Wall -g
SOURCE = src/main.c src/mainMenu.c src/student.c
OBJECTS = $(SOURCE:.c=.o)
TARGET = bin/StudentData

all: $(TARGET)

$(TARGET): $(SOURCE)
		$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
		rm -f $(TARGET) $(OBJECTS)