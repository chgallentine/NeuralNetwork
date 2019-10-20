CC=g++
CFLAGS=-Wall -std=c++11

TARGET=main

all : $(TARGET) test

run : $(TARGET)
	./$(TARGET)

$(TARGET) : main.o matrix.o convert.o dataset.o neuralnet.o
	$(CC) $(CFLAGS) $^ -o $@

test : matrix_test.o matrix.o
	$(CC) $(CFLAGS) $^ -o $@

neuralnet.o : ./NeuralNet/neuralnet.cpp ./NeuralNet/neuralnet.h ./Matrix/matrix.h
	$(CC) $(CFLAGS) $< -c		

convert.o : ./Convert/convert.cpp ./Convert/convert.h
	$(CC) $(CFLAGS) $< -c	

dataset.o : ./Dataset/dataset.cpp ./Dataset/dataset.h
	$(CC) $(CFLAGS) $< -c	

main.o : main.cpp
	$(CC) $(CFLAGS) $< -c

matrix.o : ./Matrix/matrix.cpp ./Matrix/matrix.h
	$(CC) $(CFLAGS) $< -c

matrix_test.o : ./Matrix/matrix_test.cpp
	$(CC) $(CFLAGS) $< -c

clean :
	rm -rf *.o $(TARGET)