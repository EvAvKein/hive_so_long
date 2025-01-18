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
    ft_bzero(&movement, sizeof(t_offset));
    // printf("Old %c: x-%lu, y-%lu\n", game->player->chr, game->player->pos.x, game->player->pos.y);
    if (e.key == MLX_KEY_UP && e.action == MLX_RELEASE)
        movement.y--;
    if (e.key == MLX_KEY_DOWN && e.action == MLX_RELEASE)
        movement.y++;
    if (e.key == MLX_KEY_LEFT && e.action == MLX_RELEASE)
        movement.x--;
    if (e.key == MLX_KEY_RIGHT && e.action == MLX_RELEASE)
        movement.x++;
    if (movement.x && movement.y)
    {
        printf("Can't move diagonal (%i,%i)\n", movement.x, movement.y);
        return ;
    }
    if (movement.x)
    {
        move_player(game, direction_by_offset(movement), movement.x);
        game->images.player->instances->x += (movement.x * BPP);
    }
    else if (movement.y)
    {
        move_player(game, direction_by_offset(movement), movement.y);
        game->images.player->instances->y += (movement.y * BPP);
    }
    // printf("New %c: x-%lu, y-%lu\n", game->player->chr, game->player->pos.x, game->player->pos.y);
}