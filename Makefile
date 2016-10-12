CC = g++
CFLAGS=-I. -std=c++11 -Wall
DEPS = texture.h easylogging++.h
OBJS = main.o texture.o 
LDLIBS =-lSDL2 -lSDL2_image
RUNTIME = main

all : main

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@  $^ $(LDLIBS)

%.o: %.cpp  $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 
clean:
	rm -rf *.o *.out *.gcno *.gcda $(OBJS) $(RUNTIME)
