CC= gcc 
CFLAGS=-lpthread
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
TARGET=time_server time_cli sserver
all:$(TARGET)
	 @echo  $(filter-out time_cli.o sserver.o, $(OBJS))
time_server: $(filter-out time_cli.o sserver.o, $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^
time_cli:$(filter-out time_server.o sserver.o,$(OBJS))
	$(CC) $(CFLAGS) -o $@ $^
sserver:$(filter-out time_server.o time_cli.o,$(OBJS))
	$(CC) $(CFLAGS) -o $@ $^

# all:$(TARGET)	
$(OBJS):%o:%c
	$(CC) -c $(CFLAGS) $< -o $@  # $< the first dependency file:socket_io.o:socket_io.c socket_io.h
	#$< = socket_io.c  :$@ the target obj  $^ all the dependency files 
# $(OBJS2):%o:%c
# 	$(CC) -c $(CFLAGS) $< -o $@
# server:
# 	$(CC) -o server $(OBJS1)
# client:
# 	$(CC) -o client $(OBJS2)
clean: 
	rm -rf $(OBJS) $(TARGET)
