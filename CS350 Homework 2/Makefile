# <Ezgi Nur Alisan, S021308>
CC = gcc
CPPFLAGS += -MD -MP
LIB=-pthread
TARGET= kitchen

kitchen: kitchen.o
	$(CC) -o $(TARGET) kitchen.o $(LIB)

kitchen.o: kitchen.c meal.h
	$(CC) -c kitchen.c

all: $(TARGET)

clean:
	rm -f *.o $(TARGET)
