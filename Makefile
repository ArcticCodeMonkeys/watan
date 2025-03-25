# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++14 -Wall -Wextra

# Source files
SRCS = board.cc player.cc criterion.cc goal.cc tile.cc dice.cc subject.cc main.cc

# Header files
HEADERS = board.h player.h criterion.h goal.h tile.h dice.h subject.h observer.h

# Object files
OBJS = $(SRCS:.cc=.o)

# Executable name
EXEC = watan

# Default target
all: $(EXEC) clean_objs

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files after building the executable
clean_objs:
	rm -f $(OBJS)

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean clean_objs