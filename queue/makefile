FLAGS=-g -Wall -std=c11 -c
LIBS= -lpthread
OBJ=obj
NAME=UnitTest
C=gcc

.PHONY: default clean
default: $(NAME)
clean:
		rm -rf $(NAME) $(OBJ)

$(OBJ):
		mkdir -p $(OBJ)
$(OBJ)/queue.o: queue.c | $(OBJ)
		$(C) $(FLAGS) -o $@ $< 
$(OBJ)/$(NAME).o: $(NAME).c | $(OBJ)
		$(C) $(FLAGS) -o $@ $< 

$(NAME): $(OBJ)/$(NAME).o $(OBJ)/queue.o
		$(C) -o $@ $^ $(LIBS)


run:
	./$(NAME)
