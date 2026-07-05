CC = gcc
CFLAGS = -std=c99 -Wall -Wextra #error flags
LDFLAGS = -lm #linking math library(from google)

TARGET = fp_parse
SRCS = fp_parse.c

all: $(TARGET)

$(TARGET) :$(SRCS)
    $(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
    rm -f $(TARGET)
