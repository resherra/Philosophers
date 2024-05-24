CFLAGS=-Wall -Wextra -Werror
SRC=init.c
OBJS=$(SRC:.c=.o)
NAME=philo
LIBFT=libft/libft.a

all: $(NAME)

$(NAME): init.h $(LIBFT) $(OBJS)


clean:

fclean:

re: fclean all