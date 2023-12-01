CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g
CFLAGS_TREADS = -fsanitize=thread
CFLAGS_ADDRESS = -fsanitize=address
SRC = $(wildcard Source/*.c)
OBJ = $(SRC:.c=.o)
NAME = philosophers

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -IInc/ $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -IInc/ -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	valgrind --tool=helgrind --log-file=helgrind_output.txt ./$(NAME) 2 800 200 200 10

.PHONY: all clean fclean re