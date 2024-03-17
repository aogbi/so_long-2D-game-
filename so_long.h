#ifndef SO_LONG_H
#define SO_LONG_H


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include "minilibx-linux/mlx.h"
#include "get_next_line/get_next_line.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MLX_ERROR 1

typedef struct s_img
{
    void	*mlx_img;
    char	*addr;
    int		bpp;
    int		line_len;
    int		endian;
    int        width;
    int        height;
}	t_img;

typedef struct s_action
{
    int        x;
    int        sx;
    int        y;
    int         sy;
}   t_action;

typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
    t_img   *img;
}	t_data;

#endif