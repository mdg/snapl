CC = g++

INC += acceptor.h
INC += request.h
INC += request_reader.h

SRC += acceptor.cpp
SRC += main.cpp
SRC += request_reader.cpp

OBJ += acceptor.o
OBJ += main.o
OBJ += request_reader.o

all : shessiond

obj :
	mkdir -p obj

$(INC) :

$(SRC) : $(INC)

$(OBJ) : obj $(SRC) $(SRC_H)
	$(CC) -g -c src/$*.cpp -o $@

shessiond : $(OBJ)
	$(CC) -g -o shessiond $(OBJ)


