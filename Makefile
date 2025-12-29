all: termcommands

termcommands: app.c
	gcc -Wall -Wextra -O2 -std=c99 -g -o termcommands app.c -lncursesw -ljansson

clean:
	rm -f termcommands *.o

install: termcommands
	mkdir /usr/local/bin/termcommands-data/
	cp termcommands /usr/local/bin/
	cp commands.json /usr/local/bin/termcommands-data/commands.json

uninstall:
	rm -rf /usr/local/bin/termcommands /usr/local/bin/termcommands-data/

debug: app.c
	gcc -Wall -Wextra -O2 -std=c99 -g -fsanitize=address -o termcommands app.c -lncursesw -ljansson

valgrind: termcommands
	valgrind --leak-check=full --show-leak-kinds=all ./termcommands

.PHONY: all clean install uninstall debug valgrind
