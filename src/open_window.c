/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:17:20 by aogbi             #+#    #+#             */
/*   Updated: 2024/04/07 18:03:14 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int valid_size(void *mlx_ptr, t_rules map)
{
	int sizex, sizey;

	mlx_get_screen_size(mlx_ptr, &sizex, &sizey);
	if (sizex < (int)map.len * CHAR_SIZE || sizey < (int)(map.height + 1) * CHAR_SIZE)
	    return (0);
	return (1);
}
void put_anime(t_game *game, t_action action)
{
	ssize_t i = action.x;
	ssize_t j = action.y;

	game->slime[4] = '1' + game->index;
	if ((game->rules.p_index % game->rules.len) + game->action.x > i && game->rules.map[i + 1 + (j * game->rules.len)] != '1' && game->rules.map[i + 1 + (j * game->rules.len)] != 'A')
	{
		game->rules.map[i + (j * game->rules.len)] = '0';
		game->rules.map[i + 1 + (j * game->rules.len)] = 'A';
	}
	else if (((game->rules.p_index % game->rules.len) + game->action.x < i && game->rules.map[i - 1 + (j * game->rules.len)] != '1') && game->rules.map[i - 1 + (j * game->rules.len)] != 'A')
	{
		game->rules.map[i + (j * game->rules.len)] = '0';
		game->rules.map[i - 1 + (j * game->rules.len)] = 'A';
	}
	else if ((game->rules.p_index / game->rules.len) + game->action.y > j && game->rules.map[i + ((j + 1) * game->rules.len)] != '1' && game->rules.map[i + ((j + 1) * game->rules.len)] != 'A')
	{
		game->rules.map[i + (j * game->rules.len)] = '0';
		game->rules.map[i + ((j + 1) * game->rules.len)] = 'A';
	}
	else if (((game->rules.p_index / game->rules.len) + game->action.y < j && game->rules.map[i + ((j - 1) * game->rules.len)] != '1') && game->rules.map[i + ((j - 1) * game->rules.len)] != 'A')
	{
		game->rules.map[i + (j * game->rules.len)] = '0';
		game->rules.map[i + ((j - 1) * game->rules.len)] = 'A';
	}
}

void put_player(t_game *game, t_action action)
{
	int i;
	int j;

	i = action.x;
	j = action.y;
	if (game->action.x < game->player_x)
	    game->action.x += 8;
	else if (game->action.x > game->player_x)
	    game->action.x -= 8;
	if (game->action.y < game->player_y)
	    game->action.y += 8;
	else if (game->action.y > game->player_y)
		game->action.y -= 8;
	if (game->animation == 97)
		put_image(game->data, game->filename, (t_action){(i * (CHAR_SIZE) - 7) + game->action.x, (j * CHAR_SIZE) + game->action.y});
	else
		put_image(game->data, game->filename, (t_action){(i * CHAR_SIZE) + game->action.x, (j * CHAR_SIZE) + game->action.y});
}
void	draw(t_game *game, t_rules *rules)
{
	ssize_t	i;
	ssize_t	j;
	t_action	action;
	
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
				put_image(game->data, "XPM/Heart.xpm", (t_action){i * CHAR_SIZE + 4, j * CHAR_SIZE + 4});
			else if (rules->map[i + (j * rules->len)] == 'E')
				put_image(game->data, game->door, (t_action){i * CHAR_SIZE, j * CHAR_SIZE});
			else if (rules->map[i + (j * rules->len)] == 'A')
			{
				ft_printf("action.x = %d   action.y = %d\n", i, j);
				if (game->kill.x == i && game->kill.y == j)
				{
					// ft_printf("i = %d   j = %d\n", i, j);
					game->slime[4] = 'a' + game->index;
					if (game->index == 4)
						rules->map[i + (j * rules->len)] = '0';
				}
				else
						action = (t_action){i, j};
				put_image(game->data, game->slime, (t_action){i * CHAR_SIZE - 2, j * CHAR_SIZE - 2});
			}
			i++;
		}
		j++;
	}
	i = game->rules.p_index % game->rules.len;
	j = game->rules.p_index / game->rules.len;
	put_anime(game,  action);
	ft_printf("action.x = %d   action.y = %d\n", action.x, action.y);
    put_player(game, (t_action){i , j});
}

void attack(t_game *game)
{
	int i;
	int j;

	i = game->rules.p_index % game->rules.len + (game->player_x / CHAR_SIZE);
	j = game->rules.p_index / game->rules.len + (game->player_y / CHAR_SIZE);
	if (game->animation == 97)
	{
		if (game->rules.map[i + ((j - 1) * game->rules.len)] == 'A')
			game->kill = (t_action){i , (j - 1)};
		game->animation = 79;
	}
	else if (game->animation == 103)
	{
		if (game->rules.map[i + ((j + 1) * game->rules.len)] == 'A')
			game->kill = (t_action){i , (j + 1)};
	    game->animation = 49;
	}
	else if (game->animation == 109)
	{
		if (game->rules.map[(i + 1) + (j * game->rules.len)] == 'A')
			game->kill = (t_action){(i + 1) , j};
		game->animation = 85;
	}
	else if (game->animation == 115)
	{
		if (game->rules.map[(i - 1) + (j * game->rules.len)] == 'A')
			game->kill = (t_action){(i - 1) , j};
	    game->animation = 91;
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
	else if (keysym == 32)
		{
			if (game->animation == 61 || game->animation == 79)
				game->animation = 97;
			else if(game->animation == 49 || game->animation == 55)
				game->animation = 103;
			else if (game->animation == 67 || game->animation == 85)
				game->animation = 109;
			else if (game->animation == 73 || game->animation == 91)
				game->animation = 115;
		}
    return (0);
}

void up_arrow_key(t_game *game)
{
	int i;
	int j;
	
	i = game->rules.p_index % game->rules.len + (game->player_x / CHAR_SIZE);
	j = game->rules.p_index / game->rules.len + (game->player_y / CHAR_SIZE);
	if (game->rules.map[i + (j * game->rules.len)] == 'C')
	{
		game->rules.map[i + (j * game->rules.len)] = '0';
		game->rules.c--;
	}
	game->animation = 79;
	if (game->rules.map[i + ((j - 1) * game->rules.len)] == '1'|| game->player_y != game->action.y)
		return ;
	game->player_y -= 16;
}
void down_arrow_key(t_game *game)
{
	int i;
	int j;

	i = game->rules.p_index % game->rules.len + (game->player_x / CHAR_SIZE);
	j = game->rules.p_index / game->rules.len + (game->player_y / CHAR_SIZE);
	if (game->rules.map[i + (j * game->rules.len)] == 'C')
	{
		game->rules.map[i + (j * game->rules.len)] = '0';
		game->rules.c--;
	}
	game->animation = 49;
	if (game->rules.map[i + ((j + 1) * game->rules.len)] == '1' || game->player_y != game->action.y)
		return ;
	game->player_y += 16;
}
void left_arrow_key(t_game *game)
{
	int i;
	int j;

	i = game->rules.p_index % game->rules.len + (game->player_x / CHAR_SIZE);
	j = game->rules.p_index / game->rules.len + (game->player_y / CHAR_SIZE);
	if (game->rules.map[i + (j * game->rules.len)] == 'C')
	{
		game->rules.map[i + (j * game->rules.len)] = '0';
		game->rules.c--;
	}
	game->animation = 91;
	if (game->rules.map[i - 1 + (j * game->rules.len)] == '1'|| game->player_x != game->action.x)
		return ;
	game->player_x -= 16;
}
void right_arrow_key(t_game *game)
{
	int i;
	int j;

	i = game->rules.p_index % game->rules.len + (game->player_x / CHAR_SIZE);
	j = game->rules.p_index / game->rules.len + (game->player_y / CHAR_SIZE);
	if (game->rules.map[i + (j * game->rules.len)] == 'C')
	{
		game->rules.map[i + (j * game->rules.len)] = '0';
		game->rules.c--;
	}
	game->animation = 85;
	if (game->rules.map[i + 1 + (j * game->rules.len)] == '1'|| game->player_x != game->action.x)
		return ;
	game->player_x += 16;
}

int	handle_keyrelease(int keysym, t_game *game)
{
	if (keysym == 65362)
	{
		up_arrow_key(game);
		game->cont += 1;
	}
    else if (keysym == 65364)
	{
		down_arrow_key(game);
		game->cont += 1;
	}
    else if (keysym == 65361)
	{
		left_arrow_key(game);
		game->cont += 1;
	}
    else if (keysym == 65363)
	{
		right_arrow_key(game);
		game->cont += 1;
	}
	else if (keysym == 32)
		attack(game);
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

char *string_on_window(int num)
{
	char *str;
	char *str1;
	char *str2;

    str1 = ft_strdup("moves : ");
	str2 = ft_itoa(num);
	str = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
    return (str);
}

int animation_loop(t_game *game)
{
	char *str;
	int i;
	int j;

	i = game->rules.p_index % game->rules.len + (game->player_x / CHAR_SIZE);
	j = game->rules.p_index / game->rules.len + (game->player_y / CHAR_SIZE);
	if ((game->rules.map[i + (j * game->rules.len)] == 'E' && game->rules.c == 0) || (game->rules.map[i + (j * game->rules.len)] == 'A'))
		x_button_in_window(game->data);
	if (game->data->win_ptr == NULL)
	    return (1);
	if (game->index >= 5)
		game->index = 0;
	if (game->rules.c == 0)
	    game->door[8] = '2';
	game->filename[11] = game->animation + game->index;
	game->slime[4] = '1' + game->index;
    draw(game, &game->rules);
	mlx_put_image_to_window(game->data->mlx_ptr, game->data->win_ptr, game->data->img.mlx_img, 0, 0);
	str = string_on_window(game->cont);
	mlx_string_put(game->data->mlx_ptr, game->data->win_ptr, 0, 10, (int)0xffffffff, str);
	free_memory(&str);
	usleep(100000);
	game->index++;
    return (0);
}

int hooks(t_game *game)
{
	game->filename = malloc(sizeof(char) * 17);
	game->door = malloc(sizeof(char) * 14);
	game->slime = malloc(sizeof(char) * 10);
	if (!game->filename || !game->door)
	{
        ft_printf("Memory allocation failed\n");
        return (0);
    }
	ft_strcpy(game->filename, "XPM/player/X.xpm");
	ft_strcpy(game->door, "XPM/door1.xpm");
	ft_strcpy(game->slime, "XPM/1.xpm");
	mlx_loop_hook(game->data->mlx_ptr, (int (*)(void *))animation_loop, game);
	mlx_hook(game->data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->data->win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	mlx_hook(game->data->win_ptr, ClientMessage, 0, &x_button_in_window, game->data);
	mlx_loop(game->data->mlx_ptr);
	return (0);
}

int	open_window(t_rules *rules, t_data *data)
{
	t_game	game;

	data->img.width = (int) rules->len * CHAR_SIZE;
	data->img.height = (int) (rules->height + 1) * CHAR_SIZE;
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
	game = (t_game){data, *rules, (t_action){0, 0}, (t_action){0, 0}, 0, 0, NULL, NULL, NULL, 49, 0, 0};
	hooks(&game);
	free_memory(&game.filename);
	free_memory(&game.door);
	free_memory(&game.slime);
	return (1);
};