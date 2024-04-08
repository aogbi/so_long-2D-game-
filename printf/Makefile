NAME = libftprintf.a
SOURCES = \
	ft_printf.c ft_putchar.c ft_putstr.c ft_strlen.c \
	ft_putnbr_base.c ft_putbase.c

OBJECTS = $(SOURCES:.c=.o)


CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c99

all: $(NAME)

$(NAME): $(OBJECTS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.c.o:
	$(CC) -c $(CFLAGS) $<
	ar -rcs $(NAME) $@
