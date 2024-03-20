#include "so_long.h"

int P(t_rules *rules, int index)
{
	if (rules->p != 0)
		return (1);
	rules->p++;
	rules->p_index = rules->map[index];
	return (0);
}

int E(t_rules *rules, int index)
{
	if (rules->e != 0)
	    return (1);
	rules->e++;
	rules->e_index = rules->map[index];
	return (0);
}

int map_rules_help (t_rules *rules, int i, int j)
{
	if (rules->map[j + (i * rules->len)] == 'P')
	{
		if(P(rules, j + (i * rules->len)))
		    return (1);
	}
	else if (rules->map[j + (i * rules->len)] == 'E')
	{
		if (E(rules, j + (i * rules->len)))
		    return (1);
	}
	else if (rules->map[j + (i * rules->len)] == 'C')
		rules->c++;
	else if (rules->map[j + (i * rules->len)] == '1');
	else if (rules->map[j + (i * rules->len)] == '0');
	else
		return (1);
	return (0);
}

int map_rules (t_rules *rules, int i, int j)
{
	if (i == 0 || i == rules->height - 1)
	{
		if (rules->map[j + (i * rules->len)] != '1')
			return (1);
	}
	else if (j == 0 || j == rules->len - 1)
	{
		if (rules->map[j + (i * rules->len)]!= '1')
			return (1);
	}
	else
	{
		if (map_rules_help(rules, i, j))
		    return (1);
	}
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
		return (0);
	return (1);
}

int map_is_valid(t_rules rules)
{
	int i;
	int j;

    i = 0;
	while (i < rules.height)
	{
		j = 0;
		while (j < rules.len)
		{
			if (map_rules(&rules, i, j))
			    return (1);
			j++;
		}
		i++;
	}
	rules.map_valid = cant_win(&rules, rules.p_index);
	if (rules.map_valid)
	    return (1);
	return (0);
}

t_rules read_map(int fd)
{
	char	*line;
	t_rules	rules;

	rules = (t_rules){"\0", 0, 0, 0, 0, 0, 0, 0, 1};
	if (fd < 0)
	    return ((t_rules){NULL, 0, 0, 0, 0, 0, 0, 0, -1});
    line = get_next_line(fd);
	if (!line)
	    return (rules);
	rules.len = ft_strlen(line);
	while (line)
	{
		rules.map = ft_strjoin(rules.map, line);
		free_memory(&line);
		line = get_next_line(fd);
        if (line && ft_strlen(line) != rules.len)
            return (rules);
		rules.height++;
	}
	if (map_is_valid(rules))
		return (rules);
	rules.map_valid = 0;
	return (rules);
}

int open_file(int arc, char **arv)
{
    int fd;
	char *ber;

    if (arc != 2) {
        ft_printf("nssiti map\n");
        return -1;
    }
	ber = ft_strrchr(arv[1], '.');
	if (ft_strncmp(ber, ".ber", 5) != 0)
	    return -1;
    fd = open(arv[1], O_RDONLY);
    if (fd == -1) {
        perror("hadchi ma3raft malo");
        return -1;
    }
	return (fd);
}
