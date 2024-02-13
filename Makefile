server: src/main.c include/webserv.h include/networking.h include/comm.h
	gcc -s -o webserv src/main.c include/webserv.h \
		include/networking.h include/comm.h
debug: src/main.c include/webserv.h include/networking.h include/comm.h
	gcc -g -o webserv src/main.c include/webserv.h \
		include/networking.h include/comm.h
clean: webserv
	rm webserv
