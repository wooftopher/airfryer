CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20

TARGET = airfryer

SRC = main.cpp keypad.cpp 
# heater.cpp clock.cpp protocol.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)

re: clean all

run: all
	./$(TARGET)