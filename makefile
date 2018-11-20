CC       = gcc
TARGET   = greedy
CFLAGS   = -Iprimeraparte -Wall -Werror -Wextra -pedantic -std=gnu99 -g -O3
VALGRIND = valgrind --leak-check=full --show-reachable=yes
SOURCES  = primeraparte/graph.c primeraparte/readline.c primeraparte/hashtable.c primeraparte/cola.c

HEADERS  = $(wildcard *.h)
OBJECTS  = $(SOURCES:.c=.o)
GCH		 = $(wildcard *.h.gch)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) mains/main.c

-include .depend

.depend : $(SOURCES) $(HEADERS)
	$(CC) -MM $(SOURCES) > .depend

.PHONY : run valgrind indent clean

run : $(TARGET)
	./$(TARGET) $(IN)

valgrind : $(TARGET)
	$(VALGRIND) ./$(TARGET) $(IN)

indent :
	mkdir _original _indent
	cp $(SOURCES) $(HEADERS) main.c _original
	cp $(SOURCES) $(HEADERS) main.c _indent
	indent -kr -nut -brf -cli4 -l79 _indent/*
	meld _original _indent

clean :
	rm -f .depend $(TARGET) $(OBJECTS) $(GCH)
	rm -rf _original _indent
