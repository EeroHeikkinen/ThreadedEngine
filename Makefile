# Makefile for Threaded Engine

CC := i686-w64-mingw32-g++.exe
CFLAGS := -c -g -std=c++0x -Wall -Wextra -pedantic
LDFLAGS := -static-libgcc -static-libstdc++ \
		   -lsfml-system -lsfml-window -lsfml-graphics \
		   -lglew32 -lopengl32 \
		   -Wl,-Bstatic -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath
SOURCEDIR := src
OBJDIR := obj
SOURCES := $(wildcard $(SOURCEDIR)/*.cc)
OBJECTS := $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.cc=.o)))
EXECUTABLE := bin/ThreadedEngine.exe


all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o : $(SOURCEDIR)/%.cc
	$(CC) $(CFLAGS) -o $@ $<

$(SOURCES) : $(SOURCEDIR)/*.hh
	touch $(SOURCES)

clean:
	rm $(OBJECTS) $(EXECUTABLE)

print:
	echo = $(SOURCES)
	echo = $(OBJECTS)
