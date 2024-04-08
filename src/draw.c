/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 07:30:14 by aogbi             #+#    #+#             */
/*   Updated: 2024/04/08 17:40:49 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void put_player(t_game *game)
{
	int i;
	int j;

	i = game->x - (game->player_x / CHAR_SIZE);
	j = game->y - ((game->player_y / CHAR_SIZE));
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

void put_anime(t_game *game, t_action action)
{
	if (action.x == game->kill.x && action.y == game->kill.y)
	{
		game->slime_die[4] = 97 + game->index;
		put_image(game->data, game->slime_die, (t_action){game->kill.x * CHAR_SIZE - 2, game->kill.y * CHAR_SIZE - 2});
	}
	else
        put_image(game->data, game->slime, (t_action){action.x * CHAR_SIZE - 2, action.y * CHAR_SIZE - 2});
	if (game->slime_die[4] == 101 && game->rules.map[game->kill.x + (game->kill.y * game->rules.len)] == 'A')
		game->rules.map[game->kill.x + (game->kill.y * game->rules.len)] = '0';
}

void swap(t_game *game, int x, int y)
{
	if (game->rules.map[y] == '0')
	{
		game->rules.map[x] = '0';
		game->rules.map[y] = 'A';
	}
}

void follow_player(t_game *game)
{
	char *tmp;
	int i;

	i = 0;
    tmp = ft_strdup(game->rules.map);
	while(tmp[i] && (game->index == 1 || game->index == 4))
	{
		if (tmp[i] == 'A')
		{
			if (i % game->rules.len - game->x > 0 && labs(i % game->rules.len - game->x) < 12
				&& labs(i % game->rules.len - game->x) > labs(i / game->rules.len - game->y))
				swap(game, i, i - 1);
			else if (i % game->rules.len - game->x < 0 && labs(i % game->rules.len - game->x) < 12
				&& labs(i % game->rules.len - game->x) > labs(i / game->rules.len - game->y))
				swap(game, i, i + 1);
			if (i / game->rules.len - game->y > 0 && labs(i / game->rules.len - game->y) < 12
				&& labs(i % game->rules.len - game->x) <= labs(i / game->rules.len - game->y))
				swap(game, i, i - game->rules.len);
			else if (i / game->rules.len - game->y < 0 && labs(i / game->rules.len - game->y) < 12
				&& labs(i % game->rules.len - game->x) <= labs(i / game->rules.len - game->y))
			    swap(game, i, i + game->rules.len);
		}
		i++;
	}
	free_memory(&tmp);
}

void	draw(t_game *game, t_rules *rules)
{
	ssize_t	i;
	ssize_t	j;
	
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
				put_anime(game, (t_action){i, j});
			i++;
		}
		j++;
	}
    put_player(game);
	follow_player(game);
}