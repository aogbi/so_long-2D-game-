/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:17:20 by aogbi             #+#    #+#             */
/*   Updated: 2024/04/05 02:35:33 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int valid_size(void *mlx_ptr, t_rules map)
{
	int sizex, sizey;

	mlx_get_screen_size(mlx_ptr, &sizex, &sizey);
	if (sizex < (int)map.len * CHAR_SIZE || sizey < (int)map.height * CHAR_SIZE)
	    return (0);
	return (1);
}

void	draw(t_game *game, t_rules *rules)
{
	size_t	i;
	size_t	j;
	
	j = 0;
	put_background(game->data);
	while(j < rules->height)
	{
		i = 0;
		while(i < rules->len)
		{
			if (rules->map[i + (j * rules->len)] == '1')
				put_image(game->data, "XPM/wall.xpm", (t_action){i * CHAR_SIZE, j * CHAR_SIZE});
			else if (rules->map[i + (j * rules->len)] == 'C')
			    put_image(game->data, "XPM/Coin.xpm", (t_action){i * CHAR_SIZE + 5, j * CHAR_SIZE + 5});
			else if (rules->map[i + (j * rules->len)] == 'P'){
				put_image(game->data, game->filename, (t_action){i * CHAR_SIZE + game->player_x, j * CHAR_SIZE + game->player_y});
				// ft_printf("x = %d, len = %d\n", rules->p_index, rules->len);
			}
			i++;
		}
		j++;
	}
}

int	handle_keypress(int keysym, t_game *game)
{
    if (keysym == XK_Escape)
    {
        mlx_destroy_window(game->data->mlx_ptr, game->data->win_ptr);
        game->data->win_ptr = NULL;
		mlx_destroy_image(game->data->mlx_ptr, game->data->img.mlx_img);
		game->data->img.mlx_img = NULL;
		mlx_loop_end(game->data->mlx_ptr);
    }
	else if (keysym == 65362)
		game->animation = 61;
    else if (keysym == 65364)
		game->animation = 55;
    else if (keysym == 65361)
		game->animation = 73;
    else if (keysym == 65363)
		game->animation = 67;
    return (0);
}

void up_arrow_key(t_game *game)
{
	int i;
	int j;
	
	if ((game->player_y % CHAR_SIZE != 0) && (game->player_y / CHAR_SIZE == 0))
		j = 1;
	else
	    j = 0;
	i = game->rules.p_index % game->rules.len + (game->player_x / CHAR_SIZE);
	j += game->rules.p_index / game->rules.len + (game->player_y / CHAR_SIZE);
	if (game->rules.map[i + ((j - 1) * game->rules.len)] != '1')
		game->player_y -= 4;
	if (game->rules.map[i + (j * game->rules.len)] == 'C')
		 game->rules.map[i + (j * game->rules.len)] = '0';
	game->animation = 79;
}
void down_arrow_key(t_game *game)
{
	int i;
	int j;

	i = game->rules.p_index % game->rules.len + (game->player_x / CHAR_SIZE);
	j = game->rules.p_index / game->rules.len + (game->player_y / CHAR_SIZE);
	if (game->rules.map[i + ((j + 1) * game->rules.len)] != '1')
		game->player_y += 4;
	if (game->rules.map[i + (j * game->rules.len)] == 'C')
		 game->rules.map[i + (j * game->rules.len)] = '0';
	game->animation = 49;
}
void left_arrow_key(t_game *game)
{
	int i;
	int j;

	if ((game->player_x % CHAR_SIZE != 0) && (game->player_x / CHAR_SIZE == 0))
		i = 1;
	else
	    i = 0;
	i += game->rules.p_index % game->rules.len + (game->player_x / CHAR_SIZE);
	j = game->rules.p_index / game->rules.len + (game->player_y / CHAR_SIZE);
	if (game->rules.map[i - 1 + (j * game->rules.len)] != '1')
		game->player_x -= 4;
	if (game->rules.map[i + (j * game->rules.len)] == 'C')
		 game->rules.map[i + (j * game->rules.len)] = '0';
	game->animation = 91;
}
void right_arrow_key(t_game *game)
{
	int i;
	int j;

	i = game->rules.p_index % game->rules.len + (game->player_x / CHAR_SIZE);
	j = game->rules.p_index / game->rules.len + (game->player_y / CHAR_SIZE);
	if (game->rules.map[i + 1 + (j * game->rules.len)] != '1')
		game->player_x += 4;
	if (game->rules.map[i + (j * game->rules.len)] == 'C')
		 game->rules.map[i + (j * game->rules.len)] = '0';
	game->animation = 85;
}

int	handle_keyrelease(int keysym, t_game *game)
{
	// ft_printf("%d\n", keysym);
	if (keysym == 65362) // Up arrow key
		up_arrow_key(game);
    else if (keysym == 65364) // Down arrow key
		down_arrow_key(game);
    else if (keysym == 65361) // Left arrow key
		left_arrow_key(game);
    else if (keysym == 65363) // Right arrow key
		right_arrow_key(game);
    return (0);
}

int	x_button_in_window(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    data->win_ptr = NULL;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = NULL;
	mlx_loop_end(data->mlx_ptr);
    return (0);
}

int animation_loop(t_game *game)
{
	if (game->index > 5)
		game->index = 0;
	game->filename[11] = game->animation + game->index;
    draw(game, &game->rules);
	mlx_put_image_to_window(game->data->mlx_ptr, game->data->win_ptr, game->data->img.mlx_img, 0, 0);
	usleep(100000);
	game->index++;
    return (0);
}

int hooks(t_game *game)
{
	game->filename = malloc(sizeof(char) * 17);
	 if (!game->filename) {
        ft_printf("Memory allocation failed\n");
        return (0);
    }
	ft_strcpy(game->filename, "XPM/player/X.xpm");
	mlx_hook(game->data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->data->win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	mlx_loop_hook(game->data->mlx_ptr, (int (*)(void *))animation_loop, game);
	mlx_hook(game->data->win_ptr, ClientMessage, 0, &x_button_in_window, game->data);
	mlx_loop(game->data->mlx_ptr);
	return (1);
}

int	open_window(t_rules *rules, t_data *data)
{
	t_game	game;

	data->img.width = (int) rules->len * CHAR_SIZE;
	data->img.height = (int) rules->height * CHAR_SIZE;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->img.width,  data->img.height, "so_long");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return (0);
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, data->img.width, data->img.height);
	if (data->img.mlx_img == NULL)
	{
		free(data->img.mlx_img);
		return (0);
	}
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	game = (t_game){data, *rules, 0, 0, NULL, 49, 0};
	hooks(&game);
	free_memory(&game.filename);
	return (1);
};