
CFLAGS  = -g -Wall
SRC = $(wildcard Game/Source/*cpp Render/Source/*cpp) 
INCS = $(wildcard Game/Include/*h Render/Include/*.h *.h) 
INCLUDES = -I./Game/Include/ -I./Render/Include/ -I.	


ifeq ($(OS),Windows_NT)
	CC = g++
	SDL_FLAGS = -I../../include/SDL2/ -L../../lib/ -lmingw32 -lSDL2main -lSDL2
else
	OS_NAME = $(shell uname)
	ifeq ($(OS_NAME), Linux)
	CC = g++
	SDL_FLAGS = $(shell pkg-config --cflags --libs  sdl2)
	endif
	ifeq ($(OS_NAME), Darwin)
	CC = clang++
	SDL_FLAGS = -I/Library/Frameworks/SDL2.framework/Headers/ -F/Library/Frameworks -framework SDL2
	endif
endif



all : run

run : $(SRC) $(INCS)
	$(CC) $(CFLAGS) $(INCLUDES) -o run $(SRC) main.cpp $(SDL_FLAGS)

