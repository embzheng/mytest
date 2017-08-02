CXX = g++
LD 	= g++


CXXFLAGS	+= -g	
CXXFLAGS  	+= -rdynamic 
CXXFLAGS  	+= -fexceptions 


CXXFLAGS 	+= $(INCLUDES)

LDFLAGS = $(INCLUDES) $(LIBDIR) 

LDFLAGS += -lpthread

TARGET 	= learn_cxx
SRCS	= $(wildcard *.cpp)
OBJS	= $(SRCS:.cpp=.o) 

all: $(TARGET)
# make all *.c to *.o
%.o: %.c
	$(CXX) -c -o $@ $(CXXFLAGS) $<

$(TARGET): $(OBJS) 
	$(CXX) -o $(TARGET) $^ $(LDFLAGS) 	

clean:
	rm -f *.o
	rm -f $(TARGET)
    

