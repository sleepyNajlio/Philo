NAME	= philo

SRC	= philo.c tools.c tools1.c supervisor.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread #-g -fsanitize=thread

$(NAME) :
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

all	: $(NAME)
clean :
	@rm -rf $(NAME)
fclean : clean
	@rm -rf $(NAME)
re : clean fclean all
