/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:23:20 by aogbi             #+#    #+#             */
/*   Updated: 2024/03/28 12:00:49 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/so_long.h"

int main(int arc, char **arv)
{
	int		fd;
	t_rules	map;
	t_data	data;

	fd = open_file(arc, arv);
	map = (t_rules){NULL, 0, 0, 0, 0, 0, 0};
	if (data.mlx_ptr == NULL)
        return (MLX_ERROR);
	data.mlx_ptr = mlx_init();
	if (!read_map(fd, &map) || !valid_size(data.mlx_ptr, map) || !map_is_valid(&map) ||!map_checker(&map))
	{
		ft_printf("Problem in map file");
		return (MLX_ERROR);
	}
	if (!open_window(&map,  &data))
		return (MLX_ERROR);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	free_memory(&map.map);
	return (0);
}