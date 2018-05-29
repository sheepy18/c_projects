FLAGS=-g -Wall -std=c++11 -c
LIBS= -lpthread -lcppunit
OBJ=obj
NAME=Test
DIR=test
CXX=g++

.PHONY: default clean
default: $(DIR)/$(NAME)
clean:
		rm -rf $(DIR)/$(NAME) $(OBJ)

$(OBJ):
		mkdir -p $(OBJ)
$(OBJ)/queue.o: queue.c | $(OBJ)
		$(CXX) $(FLAGS) -o $@ $< 

$(OBJ)/$(NAME).o: $(DIR)/$(NAME).c | $(OBJ)
		$(CXX) $(FLAGS) -o $@ $<

$(OBJ)/UnitTest.o: $(DIR)/UnitTest.cpp | $(OBJ)
		$(CXX) $(FLAGS) -o $@ $<

$(DIR)/$(NAME): $(OBJ)/$(NAME).o $(OBJ)/queue.o $(OBJ)/UnitTest.o
		$(CXX) -o $@ $^ $(LIBS)


run:
	./$(DIR)/$(NAME)
