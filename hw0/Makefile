CC = gcc
CFLAGS = -Wall -Wextra
TARGET = main
SRCS = main.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

.PHONY: clean
clean:
	rm -f $(TARGET)
