PROJECT_NAME = philosophers
RULES = -pthread -g #-Wall -Wextra -Werror 
INCLUDE = -I include/
APP = philosophers
FILES = $(wildcard src/*.c)
FILES_OBJ = $(FILES:.c=.o)

all: $(APP)

$(APP): $(FILES_OBJ)
	cc $(RULES) $(INCLUDE) $(FILES_OBJ) -o $(APP)

%.o: %.c
	cc $(RULES) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(FILES_OBJ)

fclean: clean
	rm -rf $(APP)

re: fclean all

