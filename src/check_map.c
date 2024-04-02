/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:28:38 by aogbi             #+#    #+#             */
/*   Updated: 2024/03/30 13:45:49 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/so_long.h"

int open_file(int arc, char **arv)
{
	char	*ber;
    int		fd;

    if (arc != 2)
		return -1;
	ber = ft_strrchr(arv[1], '.');
	if (ft_strncmp(ber, ".ber", 5) != 0)
	    return -1;
    fd = open(arv[1], O_RDONLY);
	return (fd);
}

int map_rules_help (t_rules *rules, int i, int j)
{
	if (rules->map[j + (i * rules->len)] == 'P')
	{
		if(rules->p != 0)
			return (0);
		rules->p++;
		rules->p_index = j + (i * rules->len);
	}
	else if (rules->map[j + (i * rules->len)] == 'E')
	{
		if (rules->e != 0)
			return (0);
		rules->e++;
	}
	else if (rules->map[j + (i * rules->len)] == 'C')
		rules->c++;
	else if (rules->map[j + (i * rules->len)] == '1');
	else if (rules->map[j + (i * rules->len)] == '0');
	else
		return (0);
	return (1);
}

int map_rules (t_rules *rules, size_t i, size_t j)
{
	if (i == 0 || i == (rules->height - 1))
	{
		if (rules->map[j + (i * rules->len)] != '1')
			return (0);
	}
	else if (j == 0 || j == (rules->len - 1))
	{
		if (rules->map[j + (i * rules->len)] != '1')
			return (0);
	}
	else
	{
		if (!map_rules_help(rules, i, j))
		    return (0);
	}
	return (1);
}


int map_is_valid(t_rules *rules)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < rules->height)
	{
		j = 0;
		while (j < rules->len)
		{
			if (!map_rules(rules, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}


int read_map(int fd, t_rules *rules)
{
	char	*line;

	if (fd < 0)
	    return (0);
    line = get_next_line(fd);
	if (!line)
	    return (0);
	rules->len = ft_strlen(line);
	while (line)
	{
		ft_strjoin_get(&rules->map, line);
		free_memory(&line);
		line = get_next_line(fd);
		if (line && (ft_strlen(line) != rules->len))
		{
			free_memory(&line);
			free_memory(&rules->map);
			return (0);
		}
		rules->height++;
	}
	close(fd);
	return (1);
}