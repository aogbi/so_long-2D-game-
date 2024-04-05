#include "minilibx-linux/mlx.h"
#include "ft_printf/ft_printf.h"
#include <unistd.h>
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50
#define NUM_FRAMES 6 // Number of frames in the player animation

typedef struct s_game {
    void *mlx_ptr;
    void *win_ptr;
    int player_x;
    int player_y;
    void *player_imgs[NUM_FRAMES]; // Array to store player sprite frames
    int current_frame; // Index of the current frame
} t_game;

void load_player_sprites(t_game *game)
{
    int img_width, img_height;
    int i = 0;
    char filename[17] = "XPM/player/1.xpm";

    while (i < NUM_FRAMES)
    {
        filename[11] = '1' + i;
        game->player_imgs[i] = mlx_xpm_file_to_image(game->mlx_ptr, filename, &img_width, &img_height);
        if (game->player_imgs[i] == NULL) {
           ft_printf("Failed to load player image.\n");
        }
        i++;
    }
}


// Draw the player sprite
void draw_player(t_game *game)
{
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->player_imgs[game->current_frame], game->player_x, game->player_y);
}

// Update player animation frame
void update_player_animation(t_game *game)
{
    // Update the current frame index for animation
    game->current_frame = (game->current_frame + 1) % NUM_FRAMES;
}

// Update player position based on key press
void update_player_position(t_game *game, int keycode)
{
    const int move_step = 5;

    // Update player position based on the key pressed
    if (keycode == 65362) // Up arrow key
        game->player_y -= move_step;
    else if (keycode == 65364) // Down arrow key
        game->player_y += move_step;
    else if (keycode == 65361) // Left arrow key
        game->player_x -= move_step;
    else if (keycode == 65363) // Right arrow key
        game->player_x += move_step;

    // Ensure player does not move outside the window bounds
    if (game->player_x < 0)
        game->player_x = 0;
    if (game->player_y < 0)
        game->player_y = 0;
    if (game->player_x + PLAYER_WIDTH > WIN_WIDTH)
        game->player_x = WIN_WIDTH - PLAYER_WIDTH;
    if (game->player_y + PLAYER_HEIGHT > WIN_HEIGHT)
        game->player_y = WIN_HEIGHT - PLAYER_HEIGHT;
}

// Key press event handler
int key_press(int keycode, t_game *game)
{
    update_player_position(game, keycode);
    update_player_animation(game);
    mlx_clear_window(game->mlx_ptr, game->win_ptr);
    draw_player(game);
    return (0);
}

// Loop function for animation
int animation_loop(t_game *game)
{
    update_player_animation(game);
    mlx_clear_window(game->mlx_ptr, game->win_ptr);
    draw_player(game);
	usleep(100000);
    return (0);
}

int main()
{
    t_game game;

    // Initialize MLX
    game.mlx_ptr = mlx_init();
    game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Game");

    // Load player sprites
    load_player_sprites(&game);

    // Initial player position
    game.player_x = WIN_WIDTH / 2 - PLAYER_WIDTH / 2;
    game.player_y = WIN_HEIGHT / 2 - PLAYER_HEIGHT / 2;

    // Start animation loop
    mlx_loop_hook(game.mlx_ptr, (int (*)(void *))animation_loop, &game);

    // Set up key press event handling
    mlx_hook(game.win_ptr, 2, 1L << 0, key_press, &game);

    // Enter the event loop
    mlx_loop(game.mlx_ptr);

    return 0;
}
