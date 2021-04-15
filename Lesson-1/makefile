CC=g++
CFLAG=-Wall -std=gnu++17
LFLAG=-lSDL2 -lGLESv2

lesson-1: lesson-1.o Window.o
	$(CC) $(CFLAG) $(LFLAG) -o lesson-1 lesson-1.o Window.o

lesson-1.o: lesson-1.cpp
	$(CC) $(CFLAG) -c lesson-1.cpp

Window.o: Window.cpp Window.h
	$(CC) $(CFLAG) -c Window.cpp

clean: 
	rm *.o lesson-1
