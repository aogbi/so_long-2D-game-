#include "../includes/so_long.h"

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

int map_is_valid(t_rules *rules)
{
	int i;
	int j;

    i = 0;
	while (i < rules->height)
	{
		j = 0;
		while (j < rules->len)
		{
			if (map_rules(rules, i, j))
			    return (1);
			j++;
		}
		i++;
        // ft_printf("%d\n", i);
	}
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
        {
            free_memory(&line);
            return (rules);
        }
		rules.height++;
	}
	if (!map_is_valid(&rules))
		rules.map_valid = 0;
	return (rules);
}

t_rules open_file(int arc, char **arv)
{
    int fd;
	char *ber;
	t_rules map;

	map.map_valid = 1;
    if (arc != 2) {
        ft_printf("nssiti map\n");
        return map;
    }
	ber = ft_strrchr(arv[1], '.');
	if (ft_strncmp(ber, ".ber", 5) != 0)
	    return map;
    fd = open(arv[1], O_RDONLY);
    if (fd == -1) {
        perror("hadchi ma3raft malo");
        return map;
    }
	map =  read_map(fd);
	return (map);
}

void copy_part_of_image(t_img *img1, t_img *img2, t_action action) 
{
	int j; 
	int i = 0;
	int h = 0;

	while (i < img1->height)
	{
		j = 0;
		while (j < img1->line_len)
		{
			if ((j >= (img1->line_len / action.sx) * (action.x - 1)) &&
				(j < (img1->line_len / action.sx) * action.x) &&
				(i >= (img1->height / action.sy) * (action.y - 1)) &&
				(i < (img1->height / action.sy) * action.y))
				img2->addr[h++] = img1->addr[j + (i * img1->line_len)];
			j++;
		}
		i++;
	}
}

void paste_part_into_image(t_img *img1, t_img *img2, t_action action) 
{
    int i = 0;
	int j;
	int *img1_addr = (int *)img1->addr;
	int *img2_addr = (int *)img2->addr;

	while (i < img1->height)
	{
		j = 0;
		while (j < img1->width)
		{
			if (img1_addr[j + i * img1->width] != -16777216)
				img2_addr[(action.x + j) + ((i + action.y) * (img2->width))] = img1_addr[j + i * img1->width];
			j++;
		}
		i++;
	}
}

void put_background(t_data *data)
{
	t_img	img;
	int        i = 0;
	int        j;

	img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "xpm/Dark-grass-tileset.xpm", &img.width, &img.height);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
	while (i * img.height < data->img.height)
	{
		j = 0;
		while (j * img.width < data->img.width)
		{
			paste_part_into_image(&img, &data->img, (t_action){j*img.width, 0, i*img.height, 0});
			j++;
		}
		i++;
	}
	mlx_destroy_image(data->mlx_ptr, img.mlx_img);
}

void put_image(t_data *data, char *filename, t_action index)
{
	t_img img;

	img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, filename, &img.width, &img.height);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
	paste_part_into_image(&img, &data->img, index);
	mlx_destroy_image(data->mlx_ptr, img.mlx_img);
}


int valid_size(void *mlx_ptr, t_rules map)
{
	int sizex, sizey;

	mlx_get_screen_size(mlx_ptr, &sizex, &sizey);
	if (sizex < map.len*32 || sizey < map.height*32)
	    return (1);
	return (0);
}
void put_wall(t_data *data)
{
    int i;
    int j;

	i = 0;
    j = 0;
    while (i < data->img.width)
    {
        put_image(data, "xpm/fence.xpm", (t_action){i, 0, j, 0});
        i += 32;
        if (i == data->img.width && j != data->img.height - 22)
        {
            j = data->img.height - 22;
            i = 0;
        }
    }
    i = 0;
    j = 0;
    while (j < data->img.height)
    {
        put_image(data, "xpm/fence3.xpm", (t_action){i, 0, j, 0});
        j += 32;
        if (j == data->img.height && i != data->img.width - 20)
        {
            i = data->img.width - 20;
            j = 0;
        }
    }
}

void put_player(t_data *data, int index)
{
	put_image(data, )
}


void push_stuff(t_data *data, char *map)
{

	put_background(data);
    put_wall(data);
	// put_player(data, map);
}

// int key_press(int keycode, void *param)
// {
//     if (keycode == 'a')
//         printf("Keycode: %c\n", keycode);
//     return (0);
// }
// void my_mlx_function()
// {
// }
void open_window(t_rules rules)
{
	t_data    data;
	char *map;

    data.mlx_ptr = mlx_init();
	map = ft_strdup(rules.map);
    if(valid_size(data.mlx_ptr, rules) || cant_win(&rules, rules.p_index))
    {
        ft_printf("Error");
        mlx_destroy_display(data.mlx_ptr);
        exit(1);
    }
    data.win_ptr = mlx_new_window(data.mlx_ptr, rules.len * 32,  rules.height * 32, "so_long");
    data.img.width = rules.len * 32;
    data.img.height = rules.height * 32;
    data.img.mlx_img = mlx_new_image(data.mlx_ptr, data.img.width, data.img.height);
    if (data.img.mlx_img == NULL)
        exit(1);
    data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	ft_printf("%s\n", map);
    push_stuff(&data, map);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);
    // mlx_key_hook(data.win_ptr, &key_press, NULL);
    mlx_loop(data.mlx_ptr);
}


int main(int arc, char **arv)
{
    t_rules map;

    map = open_file(arc, arv);
    if (map.map_valid)
        return 1;
    open_window(map);
	free_memory(&map.map);
    return 0;
}
