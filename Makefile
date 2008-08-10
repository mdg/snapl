CC = g++
INC_DIR = -Isrc

INC += acceptor.h
INC += request.h
INC += request_reader.h
INC += shession_control.h

SRC += acceptor.cpp
# SRC += main.cpp
SRC += request_reader.cpp
SRC += shession_control.cpp

OBJ += acceptor.o
# OBJ += main.o
OBJ += request_reader.o
OBJ += shession_control.o

# TEST_SRC += test.cpp

# TEST_OBJ += test.o

all : shessiond

$(INC) :

$(SRC) : $(INC)

$(OBJ) : $(SRC)
	$(CC) -g -c src/$*.cpp -o $@

$(TEST_SRC) : $(INC)

$(TEST_OBJ) : $(SRC) $(TEST_SRC)
	$(CC) -g -c test/$*.cpp -o $@

shessiond : $(OBJ)
	$(CC) $(INC_DIR) -g -o shessiond $(OBJ) src/main.cpp

test : $(OBJ) $(TEST_OBJ)
	$(CC) $(INC_DIR) -g -o test_shessiond $(OBJ) test/test.cpp

clean :
	rm *.o

