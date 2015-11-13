# vim: set noexpandtab:

CC=g++
CFLAGS=-std='c++0x'
CFLAGSPOST=-lGL -lglut
MDEPS=main.o vec2.o vec3.o vectormath.o sphere.o hitinfo.o

all: main

hitinfo.o: hitinfo.h hitinfo.cpp vec3.h
	$(CC) $(CFLAGS) -c hitinfo.cpp

vectormath.o: vectormath.h vectormath.cpp vec2.h vec3.h sphere.h hitinfo.h
	$(CC) $(CFLAGS) -c vectormath.cpp

sphere.o: sphere.h sphere.cpp vec3.h
	$(CC) $(CFLAGS) -c sphere.cpp

vec2.o: vec2.h vec2.cpp
	$(CC) $(CFLAGS) -c vec2.cpp

vec3.o: vec3.h vec3.cpp
	$(CC) $(CFLAGS) -c vec3.cpp

main: $(MDEPS)
	$(CC) $(CFLAGS) $(MDEPS) -o main $(CFLAGSPOST)

.PHONY: run
.PHONY: clean

run: main
	@./main

clean:
	rm -f *.o main
