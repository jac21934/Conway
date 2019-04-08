TARGET = conway

RM = rm -f

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
LDFLAGS = -lncurses


SRCS = main.cpp 
DEPS = board.h game.h 
SRCS += $(DEPS:.h=.cpp)
OBJS = $(SRCS:.cpp=.o)




%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLAGS)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS)  -o $@ $^ $(LDFLAGS)


all: $(TARGET)



clean:
	$(RM) $(TARGET) $(OBJS)

.PHONY: all clean
