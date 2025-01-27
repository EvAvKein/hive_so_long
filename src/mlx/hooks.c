/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:42:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/27 19:12:02 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

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
    if (!movement.x && !movement.y)
        return ;
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT)
        && game->progress.attacks)
        destroy_foe(game, &movement);
    if (movement.x)
        move_player(game, direction_by_offset(movement));
    if (movement.y)
        move_player(game, direction_by_offset(movement));
    play_foes(game);
    print_layout(game->map->layout, game->map->lines, 1);
}
