CC= gcc 
CFLAGS=-lpthread
OBJS=socket_io.o  time_server.o
TARGET=server
$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)
$(OBJS):%o:%c
	$(CC) -c $(CFLAGS) $< -o $@  # $< the first dependency file:socket_io.o:socket_io.c socket_io.h
	#$< = socket_io.c  $@ the target obj  $^ all the dependency files 
clean: 
	rm -rf $(OBJS)