NAME = philo

HEADER = philo.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c\
utils.c\
phil.c\
life.c\
forks.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all


