CC = g++
CFLAGS = -Wall

SRC_FILES := $(wildcard *.cc)
OBJ_FILES := $(patsubst %.cc, %.o, $(SRC_FILES))

.PHONY: all clean

all: a.out

a.out: $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ -lprotobuf 

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@ -std=c++11

clean:
	rm -f *.o a.out