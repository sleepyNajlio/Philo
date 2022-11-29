NAME = philo

SRC = philo.c tools.c tools1.c supervisor.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "✅🤖✅"

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@echo "🚮🚮🚮"

re: fclean all