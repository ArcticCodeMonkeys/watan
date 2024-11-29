# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source files
SRCS = subject.cc board.cc player.cc criterion.cc goal.cc tile.cc dice.cc main.cc

# Header files
HEADERS = observer.h subject.h board.h player.h criterion.h goal.h tile.h dice.h

# Object files
OBJS = $(SRCS:.cc=.o)

# Executable name
EXEC = mygame

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)
	

# Phony targets
.PHONY: all clean
