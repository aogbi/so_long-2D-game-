#include "so_long.h"

// // void paste_part_into_image(t_img *img1, t_img *img2, t_action action, int size_width, int size_height) 
// // {
// // 	int j;
// // 	int i = action.y;
// // 	int h = 0;

// // 	while (i < img1->height)
// // 	{
// // 		j = 0;
// // 		while (j < img1->width)
// // 		{
// // 			if ((int)&img1->addr[(j + (i * img1->width)) * 4] != 0)
// // 				img2->addr[(action.x + (action.y * img2->width)) + j] = img1->addr[j + (i * img1->line_len)];
// // 			j++;
// // 		}
// // 		action.y++;
// // 		i++;
// // 	}
// // }

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

int main(int argc, char **argv)
{
	t_rules rules;

	rules = read_map(open_file(argc, argv));
	if (rules.map_valid && rules.map_valid != -1)
	{
        ft_printf("map machi s7i7a\n");
        return (0);
    }
    return 0;
}