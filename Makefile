CC = g++

INC += acceptor.h
INC += request.h
INC += request_reader.h
INC += shession_control.h

SRC += acceptor.cpp
SRC += main.cpp
SRC += request_reader.cpp
SRC += shession_control.cpp

OBJ += acceptor.o
OBJ += main.o
OBJ += request_reader.o
OBJ += shession_control.o

all : shessiond

obj :
	mkdir -p obj

$(INC) :

$(SRC) : $(INC)

$(OBJ) : obj $(SRC) $(SRC_H)
	$(CC) -g -c src/$*.cpp -o $@

shessiond : $(OBJ)
	$(CC) -g -o shessiond $(OBJ)

clean :
	rm *.o

