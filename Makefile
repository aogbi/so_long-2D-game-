# Compiler
CC = cc
# Compiler flags
CFLAGS = -Wall -Wextra -Werror
# Directories
SRCDIR = src
OBJDIR = obj
INCDIR = includes
LIBFTDIR = libft
FT_PRINTFDIR = ft_printf
MLXDIR = minilibx-linux
# Libraries
LIBS = -L$(LIBFTDIR) -lft -L$(FT_PRINTFDIR) -lftprintf -L$(MLXDIR) -lmlx -lXext -lX11 -lm
# Source files
SRCS = $(wildcard $(SRCDIR)/*.c)
# Object files
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
# Executable
EXEC = so_long

.PHONY: all clean fclean re

all: $(EXEC)

# Linking
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

# Compiling
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -I$(FT_PRINTFDIR) -I$(MLXDIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC)

re: fclean all
