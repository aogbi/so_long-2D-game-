/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:17:20 by aogbi             #+#    #+#             */
/*   Updated: 2024/03/31 15:17:24 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int valid_size(void *mlx_ptr, t_rules map)
{
	int sizex, sizey;

	mlx_get_screen_size(mlx_ptr, &sizex, &sizey);
	if (sizex < (int)map.len*32 || sizey < (int)map.height*32)
	    return (0);
	return (1);
}

// int	right_move(t_data *data)
// {}

int	handle_keypress(int keysym, t_data *data)
{
	ft_printf("%d\n", keysym);
    if (keysym == XK_Escape)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        data->win_ptr = NULL;
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		data->img.mlx_img = NULL;
		mlx_loop_end(data->mlx_ptr);
    }
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

void	put_wall(t_data *data, t_rules *rules)
{
	size_t	i;
	size_t	j;
	
	put_background(data);
	j = 0;
	while(j < rules->height)
	{
		i = 0;
		while(i < rules->len)
		{
			if (rules->map[i + (j * rules->len)] == '1')
				put_image(data, "XPM/wall.xpm", (t_action){i * 32, j * 32});
			i++;
		}
		j++;
	}
}
int my_loop_handler(void *param) {
    // Update your animation, game state, or other dynamic content here
	while (param);
    return 0; // Return 0 to continue the loop
}

int	open_window(t_rules *rules, t_data *data)
{
	data->img.width = (int) rules->len * 32;
	data->img.height = (int) rules->height * 32;
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
	put_wall(data, rules);
    mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, 33, 0, &x_button_in_window, data);
	mlx_loop_hook(data->mlx_ptr, my_loop_handler, NULL);
    mlx_loop(data->mlx_ptr);
	return (1);
}