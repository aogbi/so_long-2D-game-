/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:23:36 by aogbi             #+#    #+#             */
/*   Updated: 2024/04/04 18:00:00 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include "../minilibx-linux/mlx.h"
#include "../includes/get_next_line.h"
#include <string.h>
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"

#define MLX_ERROR 1
#define CHAR_SIZE 16
#define NUM_FRAMES 6

typedef struct s_rules
{
    char *map;
    size_t len;
    size_t height;
    int p_index;
	int p;
	int e;
	int c;
}   t_rules;

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
    int        y;
}   t_action;

typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
    t_img   img;
}	t_data;

typedef struct s_game {
    t_data *data;
    t_rules rules;
    int player_x;
    int player_y;
    char *filename;
    char animation;
    int index;
} t_game;


int open_file(int arc, char **arv);

int read_map(int fd, t_rules *rules);

int map_is_valid(t_rules *rules);

int cant_win(t_rules *rules, int index);

void edit_index(t_rules *rulse, char *character, int index);

int map_checker(t_rules *rulse);

int valid_size(void *mlx_ptr, t_rules map);

int	open_window(t_rules *rules, t_data *data);

void put_background(t_data *data);

void put_image(t_data *data, char *filename, t_action index);

void copy_part_of_image(t_data *data, char *filename, t_action action, t_action place);

#endif