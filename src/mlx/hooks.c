/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:42:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/14 22:21:51 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void    keyhook(mlx_key_data_t e, void *param)
{
    bool    rerender;
    t_game  *game;

    rerender = 0;
    game = param;
    if (e.key == MLX_KEY_UP && e.action == MLX_RELEASE && ++rerender)
        adjacent_move(game->map->layout, game->player, UP_CHAR, EMPTY_CHAR);
    if (e.key == MLX_KEY_LEFT && e.action == MLX_RELEASE && ++rerender)
        adjacent_move(game->map->layout, game->player, LEFT_CHAR, EMPTY_CHAR);
    if (e.key == MLX_KEY_RIGHT && e.action == MLX_RELEASE && ++rerender)
        adjacent_move(game->map->layout, game->player, RIGHT_CHAR, EMPTY_CHAR);
    if (e.key == MLX_KEY_DOWN && e.action == MLX_RELEASE && ++rerender)
        adjacent_move(game->map->layout, game->player, DOWN_CHAR, EMPTY_CHAR);
    if (rerender)
        draw_frame((t_game *)param);        
}