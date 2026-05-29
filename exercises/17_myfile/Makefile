CC = gcc
CFLAGS = -Wall -g -O2 -fPIE

TARGET := 17_myfile
SRCS := 17_myfile.c
OBJS := $(SRCS:.c=.o)

all: $(TARGET) 17_myfile.o

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

17_myfile.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o 17_myfile.o $(SRCS)

clean:
	rm -f $(TARGET) $(OBJS) 17_myfile.o

.PHONY: all clean