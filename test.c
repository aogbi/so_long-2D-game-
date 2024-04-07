#include "minilibx-linux/mlx.h"

int main() {
    void *mlx_ptr;
    void *win_ptr;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Hello World");

    // Display a string at position (x=100, y=100) in white color (0xFFFFFF)
    mlx_string_put(mlx_ptr, win_ptr, 100, 100, 0xFFFFFF, "Hello, MiniLibX!");

    mlx_loop(mlx_ptr);

    return 0;
}