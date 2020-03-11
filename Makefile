PROGRAM   = Marble_maze
CC        = g++
CFLAGS    = -g -Wall
LDFLAGS   = -lGL -lGLU -lglut

$(PROGRAM): main.o marble.o
	$(CC) -o $(PROGRAM) $^ $(LDFLAGS)

main.o: main.cpp marble.hpp
	$(CC) -c $< $(LDFLAGS)

marble.o: marble.cpp marble.hpp
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
