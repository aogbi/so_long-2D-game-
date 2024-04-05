/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:42:12 by aogbi             #+#    #+#             */
/*   Updated: 2024/04/02 18:20:12 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/so_long.h"

int cant_win(t_rules *rules, int index)
{
	if (rules->map[index - 1] != '1')
		edit_index(rules, &rules->map[index - 1], index - 1);
	if (rules->map[index + 1] != '1')
		edit_index(rules, &rules->map[index + 1], index + 1);
	if (rules->map[index - rules->len] != '1')
		edit_index(rules, &rules->map[index - rules->len], index - rules->len);
	if (rules->map[index + rules->len] != '1')
	    edit_index(rules, &rules->map[index + rules->len], index + rules->len);
	if (rules->p == 0 && rules->e == 0 && rules->c == 0)
		return (1);
	return (0);
}

void edit_index(t_rules *rulse, char *character, int index)
{
	if (character[0] == 'P')
	{
		rulse->p--;
		character[0] = '1';
		cant_win(rulse, index);
	}
	else if (character[0] == 'E')
	{
		rulse->e--;
		character[0] = '1';
		cant_win(rulse, index);
	}
	else if (character[0] == 'C')
	{
		rulse->c--;
		character[0] = '1';
		cant_win(rulse, index);
	}
	else
	{
		character[0] = '1';
		cant_win(rulse, index);
	}
}

int map_checker(t_rules *rulse)
{
	t_rules	tmp;
	int	valid;

	tmp = (t_rules){ft_strdup(rulse->map), rulse->len, rulse->height, rulse->p_index, rulse->p, rulse->e, rulse->c};
	valid = cant_win(&tmp, tmp.p_index);
	free_memory(&tmp.map);
	if(!valid)
		return (0);
	return (1);
}