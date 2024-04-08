/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_release.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 07:34:13 by aogbi             #+#    #+#             */
/*   Updated: 2024/04/08 07:35:00 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void attack(t_game *game)
{
	if (game->animation == 97)
	{
		if (game->rules.map[game->x + ((game->y - 1) * game->rules.len)] == 'A')
			game->kill = (t_action){game->x, (game->y - 1)};
		game->animation = 79;
	}
	else if (game->animation == 103)
	{
		if (game->rules.map[game->x + ((game->y + 1) * game->rules.len)] == 'A')
			game->kill = (t_action){game->x  , (game->y + 1)};
	    game->animation = 49;
	}
	else if (game->animation == 109)
	{
		if (game->rules.map[(game->x + 1) + (game->y * game->rules.len)] == 'A')
			game->kill = (t_action){(game->x  + 1) , game->y};
		game->animation = 85;
	}
	else if (game->animation == 115)
	{
		if (game->rules.map[(game->x - 1) + (game->y * game->rules.len)] == 'A')
			game->kill = (t_action){(game->x - 1) , game->y};
	    game->animation = 91;
	}
}

void space_key(t_game *game)
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
		space_key(game);
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