CC = gcc
CFLAGS = -g -Wall
LIBS= -lcommons

BIN = bin
OBJ = obj
SRC = src

TARGET = $(BIN)/consola
SRCS = $(wildcard $(SRC)/*.c)
HEADERS = $(wildcard $(SRC)/*.h)
OBJS = $(patsubst $(SRC)/%.c, obj/%.o, $(SRCS))

.PHONY: default all clean

all: $(TARGET)

release: CFLAGS = -Wall -O2 -DNDEBUG
release: clean
release: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@ $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BIN)/* $(OBJ)/*