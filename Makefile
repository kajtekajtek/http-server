server: main.c server.h
	gcc -s -o server main.c server.h
debug:
	gcc -g -o server main.c server.h 
clean:
	rm server
