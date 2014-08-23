CC=gcc
CFLAGS=-c -std=c99 -Wall
LDFLAGS=
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

ifeq ($(OS), Windows_NT)
	EXECUTABLE=convert.exe
	CLEAN=del /f
else
	EXECUTABLE=convert
	CLEAN=rm -rf
endif


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(CLEAN) $(OBJECTS)
	$(CLEAN) $(EXECUTABLE)

cleanobj:
	$(CLEAN) $(OBJECTS)

rebuild: clean $(EXECUTABLE) cleanobj
