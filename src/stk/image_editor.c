#include "../includes/so_long.h"

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

	img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "xpm/grass.xpm", &img.width, &img.height);
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
