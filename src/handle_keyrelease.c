/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyrelease.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 07:24:54 by aogbi             #+#    #+#             */
/*   Updated: 2024/04/08 07:26:52 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void up_arrow_key(t_game *game)
{
	if (game->rules.map[game->x + (game->y * game->rules.len)] == 'C')
	{
		game->rules.map[game->x + (game->y * game->rules.len)] = '0';
		game->rules.c--;
	}
	game->animation = 79;
	if (game->rules.map[game->x + ((game->y - 1) * game->rules.len)] == '1'|| game->player_y != game->action.y)
		return ;
	game->player_y -= 16;
	game->cont += 1;
	ft_printf("up move, total : %d\n", game->cont);
}

void down_arrow_key(t_game *game)
{
	if (game->rules.map[game->x + (game->y * game->rules.len)] == 'C')
	{
		game->rules.map[game->x + (game->y * game->rules.len)] = '0';
		game->rules.c--;
	}
	game->animation = 49;
	if (game->rules.map[game->x + ((game->y + 1) * game->rules.len)] == '1' || game->player_y != game->action.y)
		return ;
	game->player_y += 16;
	game->cont += 1;
	ft_printf("down move, total : %d\n", game->cont);
}

void left_arrow_key(t_game *game)
{
	if (game->rules.map[game->x + (game->y * game->rules.len)] == 'C')
	{
		game->rules.map[game->x + (game->y * game->rules.len)] = '0';
		game->rules.c--;
	}
	game->animation = 91;
	if (game->rules.map[game->x - 1 + (game->y * game->rules.len)] == '1'|| game->player_x != game->action.x)
		return ;
	game->player_x -= 16;
	game->cont += 1;
	ft_printf("left move, total : %d\n", game->cont);
}

void right_arrow_key(t_game *game)
{
	if (game->rules.map[game->x + (game->y * game->rules.len)] == 'C')
	{
		game->rules.map[game->x + (game->y * game->rules.len)] = '0';
		game->rules.c--;
	}
	game->animation = 85;
	if (game->rules.map[game->x + 1 + (game->y * game->rules.len)] == '1'|| game->player_x != game->action.x)
		return ;
	game->player_x += 16;
	game->cont += 1;
	ft_printf("right move, total : %d\n", game->cont);
}

int	handle_keyrelease(int keysym, t_game *game)
{
	if (keysym == 65362)
		up_arrow_key(game);
    else if (keysym == 65364)
		down_arrow_key(game);
    else if (keysym == 65361)
		left_arrow_key(game);
    else if (keysym == 65363)
		right_arrow_key(game);
	else if (keysym == 32)
		attack(game);
    return (0);
}