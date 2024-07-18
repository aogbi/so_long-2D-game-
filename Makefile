CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = src
OBJDIR = obj
INCDIR = includes
LIBFTDIR = Libft
FT_PRINTFDIR = printf
MLXDIR = mlx
LIBS = -L$(LIBFTDIR) -lft -L$(FT_PRINTFDIR) -lftprintf -L$(MLXDIR) -lmlx -lXext -lX11 -lm
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
EXEC = so_long

all: $(EXEC)

$(EXEC): $(OBJS)
	make -C mlx
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -I$(FT_PRINTFDIR) -I$(MLXDIR) -c $< -o $@

clean:
	make clean -C mlx
	rm -f $(OBJS)

fclean: clean
	make fclean -C mlx
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re