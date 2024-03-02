
CC = g++
CFLAGS = -Wall
LIBS = -lX11
TARGET = main.out
SOURCE = main.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

clean:
	rm -f $(TARGET)

