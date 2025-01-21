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

void    resizehook(int width, int height, void* param)
{ 
    t_game  *game;

    game = param;
    game->screen.height = height;
    game->screen.width = width;
    //draw_frame(game);
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
    movement.y = 0 - (e.key == MLX_KEY_UP) + (e.key == MLX_KEY_DOWN);
    movement.x = 0 - (e.key == MLX_KEY_LEFT) + (e.key == MLX_KEY_RIGHT);
    if (movement.x && movement.y)
        return ((void)!perr("Diagonal movement not supported\n"));
    if (movement.x && move_player(game, direction_by_offset(movement), abs(movement.x)))
        game->images.player->instances->x += (movement.x * BPP);
    else if (movement.y && move_player(game, direction_by_offset(movement), abs(movement.y)))
        game->images.player->instances->y += (movement.y * BPP);
    //print_layout(game->map->layout, game->map->lines, 1);
}
