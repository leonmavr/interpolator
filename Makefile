###################################################
# definitions                                     #
###################################################
CC = g++

EXEC = main 
SRC_DIR = src
INCL_DIR = include 
CFLAGS = -std=c++17 -g -I$(INCL_DIR) -Wall
LDFLAGS = 
SOURCES = $(SRC_DIR)/interpolator.cpp $(SRC_DIR)/pointlist.cpp main.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)
RM = rm -rf

TEST_DIR = test
TEST_EXEC = $(TEST_DIR)/test
TEST_SOURCES = $(SRC_DIR)/pointlist.cpp $(SRC_DIR)/interpolator.cpp
TEST_OBJECTS = $(TEST_SOURCES:%.cpp=%.to)
TEST_CFLAGS = -std=c++17 -g -I$(INCL_DIR)

###################################################
# project                                         #
###################################################
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LDFLAGS) 

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: quickclean clean

quickclean:
	$(RM) $(OBJECTS)
	$(RM) $(EXEC)
	$(RM) $(TEST_OBJECTS)
	$(RM) $(TEST_EXEC)
	$(RM) $(TEST_DIR)/tests.to

clean: quickclean
	$(RM) $(TEST_DIR)/*.to

###################################################
# unit tests                                      #
###################################################

%.to: %.cpp
	$(CC) $(TEST_CFLAGS) -c $^ -o $@

tests.to: $(TEST_DIR)/tests.cpp
	$(CC) $(TEST_DIR)/tests.cpp $(TEST_CFLAGS) -o $(TEST_DIR)/tests.to

catch.to: $(TEST_DIR)/catch.cpp
	$(CC) -c $(TEST_DIR)/catch.cpp $(TEST_CFLAGS) -o $(TEST_DIR)/catch.to

test: $(TEST_DIR)/tests.to $(TEST_DIR)/catch.to $(TEST_OBJECTS)
	$(CC) $(TEST_DIR)/tests.to $(TEST_DIR)/catch.to $(TEST_OBJECTS) -o $(TEST_EXEC) $(LDFLAGS) 
	./$(TEST_EXEC)
