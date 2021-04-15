CC=g++
CFLAG=-Wall -std=gnu++17
LFLAG=-lSDL2 -lGLESv2

lesson-2: lesson-2.o Window.o
	$(CC) $(CFLAG) $(LFLAG) -o lesson-2 lesson-2.o Window.o

lesson-2.o: lesson-2.cpp
	$(CC) $(CFLAG) -c lesson-2.cpp

Window.o: Window.cpp Window.h
	$(CC) $(CFLAG) -c Window.cpp

clean: 
	rm *.o lesson-2
