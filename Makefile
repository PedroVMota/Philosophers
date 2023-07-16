PROJECT_NAME = philosophers
RULES = -Wall -Wextra -Werror -pthread -g -fsanitize=address
INCLUDE = -I include/
APP = philosophers
FILES = $(wildcard src/*.c)
FILES_OBJ = $(FILES:.c=.o)

all: $(APP)

$(APP): $(FILES_OBJ)
	cc $(RULES) $(INCLUDE) $(FILES_OBJ) -o $(APP)

%.o: %.c
	cc $(RULES) $(INCLUDE) -c $< -o $@

run:
	./philosophers 1 1 1 1 1

leak:
	leaks -atExit -- ./philosophers 10 1 1 1 1 > leaks.leaks 
clean:
	rm -rf $(FILES_OBJ)

fclean: clean
	rm -rf $(APP)

re: fclean all



