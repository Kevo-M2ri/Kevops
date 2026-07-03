CC = gcc
CFLAGS = -std=c99 -Wall -g

TARGET = typing_word_game
SRC = typing_word_game.c

all: $(TARGET)

$(TARGET): $(SRC)
        $(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
        rm -f $(TARGET)