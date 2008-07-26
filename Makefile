CC = g++

INC += acceptor.h

SRC += acceptor.cpp
SRC += main.cpp

OBJ += acceptor.o
OBJ += main.o

all : shessiond

obj :
	mkdir -p obj

$(INC) :

$(SRC) : $(INC)

$(OBJ) : obj $(SRC) $(SRC_H)
	$(CC) -c src/$*.cpp -o $@

shessiond : $(OBJ)
	$(CC) -o shessiond $(OBJ)


