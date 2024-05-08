# Arkadroid Makefile
# Compiles all .cpp files in the workspace and links against SFML.

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra

# Source files and object files
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = Arkadroid

# Linker flags for SFML libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Default build target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove object files and executable
clean:
	rm -f *.o $(TARGET) $(TARGET).exe
