CC = gcc
LD 	= gcc

CFLAGS	+= -g	
CFLAGS  += -rdynamic 
CFLAGS  += -fexceptions 

INCLUDES += -I ./tools
CFLAGS 	+= $(INCLUDES)
LDFLAGS = $(INCLUDES) $(LIBDIR) 
LDFLAGS += -lpthread

TARGET 	= ctest
SRCS	= $(wildcard *.c)
OBJS	= $(SRCS:.c=.o) 
OBJS    += mytools/mytools.o mytools/log.o

all: $(TARGET)
# make all *.c to *.o
%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $<

$(TARGET): $(OBJS) 
	$(CC) -o $(TARGET) $^ $(LDFLAGS) 	

clean:
	rm -f *.o
	rm -f $(TARGET)
	rm -f ./mytools/*.o
    

