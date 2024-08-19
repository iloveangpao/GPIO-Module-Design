CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

TARGET = gpio_test

SRCS = src/gpio.c test_gpio.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c include/gpio.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

