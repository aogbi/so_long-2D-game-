#include "so_long.h"

// void	render_background(t_data *data, int color)
// {
//     int	i;
//     int	j;

//     if (data->win_ptr == NULL)
//         return ;
//     i = 0;
//     while (i < WINDOW_HEIGHT)
//     {
//         j = 0;
//         while (j < WINDOW_WIDTH)
//             mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, color);
//         ++i;
//     }
// }
void copy_part_of_image(t_img *img1, t_img *img2, t_action action, int size_width, int size_height) 
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
				(i >= (size_height / action.sy) * (action.y - 1)) &&
				(i < (size_height / action.sy) * action.y))
				img2->addr[h++] = img1->addr[j + (i * img1->line_len)];
			j++;
		}
		i++;
	}
}
void paste_part_into_image(t_img *img1, t_img *img2, t_action action, int size_width, int size_height) 
{
	int j;
	int i = action.y;
	int h = 0;

	while (i < img1->height)
	{
		j = 0;
		while (j < img1->width)
		{
			if ((int)&img1->addr[(j + (i * img1->width)) * 4] != 0)
				img2->addr[(action.x + (action.y * img2->width)) + j] = img1->addr[j + (i * img1->line_len)];
			j++;
		}
		action.y++;
		i++;
	}
}

void valid(int arc, char **arv)
{
	char *map;
    int fd;

    if (arc != 2) {
        printf("Usage: %s <map>\n", arv[0]);
        return 1;
    }
    map = arv[1];
    fd = open(map, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    close(fd);
}
int main(int argc, char *argv[]) 
{   
    
    return 0;
}