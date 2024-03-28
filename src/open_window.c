/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:17:20 by aogbi             #+#    #+#             */
/*   Updated: 2024/03/28 12:06:18 by aogbi            ###   ########.fr       */
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
    mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
    mlx_loop(data->mlx_ptr);
	return (1);
}