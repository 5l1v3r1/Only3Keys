# MakeFile for only3keys

# Declaration of variables
CC = gcc
C_FLAGS = -Wall -Werror --pedantic
LIBS = -lncurses

# File names
EXEC = run
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(LIBS) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.c
	$(CC) -c $(C_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
