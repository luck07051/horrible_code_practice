all: a.out


a.out: main.o snake.o
	g++ -o a.out main.o snake.o -lcurses

main.o: main.cpp snake.h
	g++ -lcurses -c main.cpp

snake.o: snake.cpp snake.h
	g++ -c snake.cpp

clean:
	rm -f main.o snake.o a.out
