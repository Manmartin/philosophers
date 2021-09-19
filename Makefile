NAME = philo

SRCS = main.c \
		aux.c \
		simulation.c \
		parser.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -o3

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  -o $@  $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
