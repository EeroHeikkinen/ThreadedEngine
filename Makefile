# Makefile for Threaded Engine

CC = i686-w64-mingw32-g++.exe
CFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic
LDFLAGS= -static-libgcc -static-libstdc++ -lsfml-system -lsfml-window -lsfml-graphics -lglew32 -lopengl32
SOURCEDIR := src
OBJDIR := obj
SOURCES := $(wildcard $(SOURCEDIR)/*.cc)
OBJECTS := $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cc=.o)))
EXECUTABLE= bin/ThreadedEngine.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SOURCEDIR)/%.cc
	$(CC) $(CFLAGS) -o $@ $<


clean:
	rm $(OBJECTS) $(EXECUTABLE)

print:
	echo = $(SOURCES)
	echo = $(OBJECTS)


# CC = g++.exe
# CFLAGS= -g -std=c++0x -Wall -Wextra -pedantic
# LDFLAGS= -L -l -lglew32 -lglut -lglu32 -lopengl32 
# SOURCEDIR := src
# SOURCES := $(wildcard src/*.cc)
# OBJECT := obj/engine.o
# EXECUTABLE= ThreadedEngine.exe

# all: $(SOURCES) $(EXECUTABLE)

# $(EXECUTABLE): $(OBJECT)
# 	$(CC) $(OBJECT) $(LDFLAGS) -o $@ $^

# $(OBJECT): $(SOURCES)
# 	$(CC) $(CFLAGS) -o $(OBJECT) $(SOURCES)

# clean:
# 	rm $(OBJECTS) $(EXECUTABLE)

# print:
# 	echo = $(SOURCES)
# 	echo lerssi
# 	echo = $(OBJECTS)