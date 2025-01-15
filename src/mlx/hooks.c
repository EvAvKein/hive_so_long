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
    draw_frame(game);
}

void    keyhook(mlx_key_data_t e, void *param)
{
    (void)  e;
    (void)  param;
    // int     rerender;
    // t_game  *game;

    // rerender = 0;
    // game = param;
    // // printf("Old %c: x-%lu, y-%lu\n", game->player->chr, game->player->pos.x, game->player->pos.y);
    // if (e.key == MLX_KEY_UP && e.action == MLX_RELEASE && ++rerender)
    //     adjacent_move(game->map->layout, game->player, UP_CHAR, EMPTY_CHAR);
    // if (e.key == MLX_KEY_LEFT && e.action == MLX_RELEASE && ++rerender)
    //     adjacent_move(game->map->layout, game->player, LEFT_CHAR, EMPTY_CHAR);
    // if (e.key == MLX_KEY_RIGHT && e.action == MLX_RELEASE && ++rerender)
    //     adjacent_move(game->map->layout, game->player, RIGHT_CHAR, EMPTY_CHAR);
    // if (e.key == MLX_KEY_DOWN && e.action == MLX_RELEASE && ++rerender)
    //     adjacent_move(game->map->layout, game->player, DOWN_CHAR, EMPTY_CHAR);
    // if (rerender)
    //     draw_frame((t_game *)param);
    // printf("New %c: x=%lu, y=%lu\n", game->player->chr, game->player->pos.x, game->player->pos.y);
}