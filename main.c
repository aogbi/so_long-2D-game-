#include "so_long.h"

// int valid_size(t_data data, t_rules map)
// {
// 	int sizex, sizey;

// 	mlx_get_screen_size(data.mlx_ptr, &sizex, &sizey);
// 	if (sizex >= map.len && sizey >= map.height)
// 	    return (1);
// 	return (0);
// }
// int push_stuff(t_data *data, t_rules map)
// {
// 	put_background(data);

// }

// void open_window(t_rules map)
// {
// 	t_data    data;

//     data.mlx_ptr = mlx_init();
//     data.img.width = map.len;
//     data.img.height = map.height;
//     data.img.mlx_img = mlx_new_image(data.mlx_ptr, data.img.width, data.img.height);
//     data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
//     if (data.img.mlx_img == NULL)
//         exit(1);
//     push_stuff(&data, map);
//     mlx_loop_hook(data.mlx_ptr, push_stuff, &data);
// }

int key_press(int keycode, void *param)
{
    printf("Keycode: %d\n", keycode);
    return (0);
}

int main()
{
    void *mlx_ptr;
    void *win_ptr;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Keyboard Input");

    mlx_key_hook(win_ptr, &key_press, NULL);

    mlx_loop(mlx_ptr);

    return 0;
}
