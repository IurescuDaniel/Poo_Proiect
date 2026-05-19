CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = motor_cautare
SRCS = $(wildcard SRC/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f SRC/*.o $(TARGET)