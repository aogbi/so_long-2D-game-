/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:17:20 by aogbi             #+#    #+#             */
/*   Updated: 2024/04/08 18:33:27 by aogbi            ###   ########.fr       */
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

	game->x = game->rules.p_index % game->rules.len + (game->player_x / CHAR_SIZE);
	game->y = game->rules.p_index / game->rules.len + (game->player_y / CHAR_SIZE);
	if ((game->rules.map[game->x + (game->y * game->rules.len)] == 'E' && game->rules.c == 0) 
		|| (game->rules.map[game->x + (game->y * game->rules.len)] == 'A'))
		x_button_in_window(game->data);
	if (game->data->win_ptr == NULL)
	    return (1);
	if (game->index > 5)
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
	if (!game->filename || !game->door || !game->slime || !game->slime_die)
	{
        ft_printf("Memory allocation failed\n");
        return (0);
    }
	game->x = game->rules.p_index % game->rules.len;
	game->y = game->rules.p_index / game->rules.len;
	mlx_loop_hook(game->data->mlx_ptr, (int (*)(void *))animation_loop, game);
	mlx_hook(game->data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->data->win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	mlx_hook(game->data->win_ptr, ClientMessage, 0, &x_button_in_window, game->data);
	mlx_loop(game->data->mlx_ptr);
	if (game->rules.map[game->x + (game->y * game->rules.len)] == 'E')
		ft_printf("YOU WIN\n");
	else if(game->rules.map[game->x + (game->y * game->rules.len)] == 'A')
	    ft_printf("YOU LOSE\n");
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
	game = (t_game){data, *rules, (t_action){0, 0}, (t_action){0, 0}, 0, 0, 0, 0, ft_strdup("XPM/player/X.xpm"),
		ft_strdup("XPM/door1.xpm"),  ft_strdup("XPM/1.xpm"), ft_strdup("XPM/a.xpm"), 49, 0, 0};
	hooks(&game);
	free_memory(&game.filename);
	free_memory(&game.door);
	free_memory(&game.slime);
	free_memory(&game.slime_die);
	return (1);
};