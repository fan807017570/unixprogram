CC= gcc 
CFLAGS=-lpthread
OBJS1=socket_io.o	time_server.o 
OBJS2=socket_io.o	time_cli.o
all:server client	
server:
	$(CC) -o server $(OBJS1)
client:
	$(CC) -o client $(OBJS2)
$(OBJS1):%o:%c
	$(CC) -c $(CFLAGS) $< -o $@  # $< the first dependency file:socket_io.o:socket_io.c socket_io.h
	#$< = socket_io.c  $@ the target obj  $^ all the dependency files 
$(OBJS2):%o:%c
	$(CC) -c $(CFLAGS) $< -o $@
clean: 
	rm -rf $(OBJS1)