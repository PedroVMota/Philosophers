CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=undefined 
CFLAGS_TREADS = -fsanitize=thread
CFLAGS_ADDRESS = -fsanitize=address
SRC = $(wildcard Source/*.c)
OBJ = $(SRC:.c=.o)
NAME = philosophers

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -IInc/ $(CFLAGS_ADDRESS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -IInc/ $(CFLAGS_ADDRESS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re