CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99 -g
LIBS = -lncursesw -ljansson
TARGET = termcommands
SRC = app.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET) *.o

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
	cp commands.json /usr/local/share/termcommands.json

uninstall:
	rm -f /usr/local/bin/$(TARGET) /usr/local/share/termcommands.json

debug: $(SRC)
	$(CC) $(CFLAGS) -fsanitize=address -o $(TARGET) $(SRC) $(LIBS)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

.PHONY: all clean install uninstall debug valgrind
