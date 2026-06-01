CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = aplicatie_motor
SRCS = $(wildcard motor_cautare/src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f src/*.o $(TARGET)