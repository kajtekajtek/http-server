server: src/main.c include/webserv.h include/webserv.c include/networking.h \
	include/networking.c include/communication.h include/communication.c
	gcc -s -o webserv src/main.c include/webserv.h include/webserv.c \
		include/networking.h include/networking.c \
		include/communication.h include/communication.c
debug: src/main.c include/webserv.h include/webserv.c include/networking.h \
	include/networking.c include/communication.h include/communication.c
	gcc -g -o webserv src/main.c include/webserv.h include/webserv.c \
		include/networking.h include/networking.c \
		include/communication.h	include/communication.c
clean: webserv
	rm webserv
