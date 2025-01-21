/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:42:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/15 16:53:13 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

typedef struct s_resize_data {
    t_offset    prev_offset;
    t_offset    new_offset;
    mlx_image_t *img;
    char        chr;
}           t_resize_data;

static bool    resize_adjust_image(t_game *game, t_entity c, void *extras)
{
    t_resize_data *data;
    mlx_instance_t *instance;

    (void) game;
    data = (t_resize_data *)extras;
    if (c.chr == EMPTY_CHAR)
    {
        data->img->instances[c.pos.y * (c.pos.x + 1) + c.pos.x].x = (data->new_offset.x + c.pos.x) * BPP; 
        data->img->instances[c.pos.y * (c.pos.x + 1) + c.pos.x].y = (data->new_offset.y + c.pos.y) * BPP;
    }

    instance = image_instance_by_pos(data->img, data->prev_offset, c.pos);
    if (instance == NULL)
        return (false);

    instance->x = data->new_offset.x;
    instance->y = data->new_offset.y;
    return (true);
    //
    // find image equivalent of tile using coordinates
    //
}

static void    resize_adjust_images(t_game *game, t_resize_data *data)
{
    *data = (t_resize_data){.img = game->images.background, .chr = EMPTY_CHAR};
    for_each_tile(game, resize_adjust_image, data);
    *data = (t_resize_data){.img = game->images.wall, .chr = WALL_CHAR};
    for_each_tile(game, resize_adjust_image, data);
    *data = (t_resize_data){.img = game->images.collectible, .chr = COLLECTIBLE_CHAR};
    for_each_tile(game, resize_adjust_image, data);
    *data = (t_resize_data){.img = game->images.player, .chr = PLAYER_CHAR};
    for_each_tile(game, resize_adjust_image, data);
    *data = (t_resize_data){.img = game->images.exit, .chr = EXIT_CHAR};
    for_each_tile(game, resize_adjust_image, data);
}

void    resizehook(int width, int height, void* param)
{ 
    t_game  *game;
    t_resize_data data;

    game = param;
    game->screen.height = height;
    game->screen.width = width;
    data = (t_resize_data) {
        .img = NULL,
        .chr = '\0',
        .prev_offset = (t_offset){
            .x = game->images.wall->instances->x,
            .y = game->images.wall->instances->y
        },
        .new_offset = calc_offset(game)
    };
    resize_adjust_images(game, &data);
}

void    keyhook(mlx_key_data_t e, void *param)
{
    t_game  *game;
    t_offset    movement;

    game = param;
    movement = (t_offset){.x = 0, .y = 0};
    if (e.action != MLX_PRESS && e.action != MLX_REPEAT)
        return ;
    if (e.key == MLX_KEY_ESCAPE)
    {
        mlx_terminate(game->mlx);
        clean_exit(game, EXIT_SUCCESS);
    }
    movement.y = 0 - (e.key == MLX_KEY_W) + (e.key == MLX_KEY_S);
    movement.x = 0 - (e.key == MLX_KEY_A) + (e.key == MLX_KEY_D);
    if (movement.x && movement.y)
        return ((void)!perr("Diagonal movement not supported\n"));
    if (movement.x && move_player(game, direction_by_offset(movement)))
        game->images.player->instances->x += (movement.x * BPP);
    if (movement.y && move_player(game, direction_by_offset(movement)))
        game->images.player->instances->y += (movement.y * BPP);
    //print_layout(game->map->layout, game->map->lines, 1);
}
