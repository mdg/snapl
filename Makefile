CC = g++
INC_DIR = -Isrc

INC += connection_acceptor.h
INC += connection_factory.h
INC += request.h
INC += request_parser.h
INC += request_processor.h
INC += request_reader.h
INC += shession_client.h
INC += shession_control.h

TEST_INC += testpp.h

SRC += connection_acceptor.cpp
SRC += request.cpp
SRC += request_parser.cpp
SRC += request_processor.cpp
SRC += request_reader.cpp
SRC += shession_client.cpp
SRC += shession_control.cpp

TEST_SRC += request_parser_test.cpp
TEST_SRC += request_processor_test.cpp
TEST_SRC += request_reader_test.cpp
TEST_SRC += request_test.cpp
TEST_SRC += testpp.cpp

LOAD_SRC += main.cpp

OBJ += connection_acceptor.o
OBJ += request.o
OBJ += request_parser.o
OBJ += request_processor.o
OBJ += request_reader.o
OBJ += shession_client.o
OBJ += shession_control.o

TEST_OBJ += request_parser_test.o
TEST_OBJ += request_processor_test.o
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

# load
#
load : $(OBJ)
	$(CC) $(INC_DIR) -g -o load_shessiond $(OBJ) $(TEST_OBJ) load/load.cpp

clean :
	rm *.o

