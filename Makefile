server: src/main.c include/webserv.h include/webserv.c include/networking.h \
	include/networking.c include/http.h include/http.c include/include.h
	gcc -s -o webserv src/main.c include/webserv.h include/webserv.c \
		include/networking.h include/networking.c include/http.h \
		include/http.c include/include.h
debug: src/main.c include/webserv.h include/webserv.c include/networking.h \
	include/networking.c include/http.h include/http.c include/include.h
	gcc -g -o webserv src/main.c include/webserv.h include/webserv.c \
		include/networking.h include/networking.c include/http.h \
		include/http.c include/include.h
clean: webserv
	rm webserv
