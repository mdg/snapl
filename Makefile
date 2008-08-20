CC = g++
INC_DIR = -Isrc

INC += acceptor.h
INC += request.h
INC += request_reader.h
INC += shession_control.h

INC += testpp.h

SRC += acceptor.cpp
SRC += request.cpp
SRC += request_reader.cpp
SRC += shession_control.cpp

TEST_SRC += request_reader_test.cpp
TEST_SRC += request_test.cpp
TEST_SRC += testpp.cpp

OBJ += acceptor.o
OBJ += request.o
OBJ += request_reader.o
OBJ += shession_control.o

TEST_OBJ += request_reader_test.o
TEST_OBJ += request_test.o
TEST_OBJ += testpp.o

all : shessiond

# regular build
#
$(INC) :

$(SRC) : $(INC)

$(OBJ) : $(SRC)
	$(CC) -g -c src/$*.cpp -o $@

shessiond : $(OBJ)
	$(CC) $(INC_DIR) -g -o shessiond $(OBJ) src/main.cpp

# test
#
$(TEST_INC) :

$(TEST_SRC) : $(INC) $(TEST_INC)

$(TEST_OBJ) : $(SRC) $(TEST_SRC)
	$(CC) $(INC_DIR) -g -c test/$*.cpp -o $@

test : $(OBJ) $(TEST_OBJ)
	$(CC) $(INC_DIR) -g -o test_shessiond $(OBJ) $(TEST_OBJ) test/test.cpp

clean :
	rm *.o

