CC = g++
TARGET = tetris
SOURCES = main_t.cpp \
	  screen_t.cpp \
	  tetromino_t.cpp

LDFLAGS = -lncurses

all:
	$(CC) -o $(TARGET) $(SOURCES) $(LDFLAGS)

clean:
	rm -rf *.o $(TARGET)
