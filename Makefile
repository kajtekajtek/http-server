server: src/main.c include/webserv.h include/webserv.c include/networking.h \
	include/networking.c include/comm.h include/comm.c
	gcc -s -o webserv src/main.c include/webserv.h include/webserv.c \
		include/networking.h include/networking.c include/comm.h \
		include/comm.c
debug: src/main.c include/webserv.h include/webserv.c include/networking.h \
	include/networking.c include/comm.h include/comm.c
	gcc -g -o webserv src/main.c include/webserv.h include/webserv.c \
		include/networking.h include/networking.c include/comm.h \
		include/comm.c
clean: webserv
	rm webserv
