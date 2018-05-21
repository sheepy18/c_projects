FLAGS=-g -Wall -std=c11 -c
LIBS= -lpthread
OBJ=obj
NAME=test
C=gcc

.PHONY: default clean
default: $(NAME)
clean:
		rm -rf $(NAME) $(OBJ)

$(OBJ):
		mkdir -p $(OBJ)
$(OBJ)/queue.o: queue.c | $(OBJ)
		$(C) $(FLAGS) -o $@ $< 
$(OBJ)/test.o: test.c | $(OBJ)
		$(C) $(FLAGS) -o $@ $< 

$(NAME): $(OBJ)/test.o $(OBJ)/queue.o
		$(C) -o $@ $^ $(LIBS)
run:
		./$(NAME)   
		

