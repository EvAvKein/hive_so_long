/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:16:07 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/15 14:25:24 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

bool	render_background(t_game *game, t_entity c, void *extras)
{
	(void) extras;
	
	if (mlx_image_to_window(game->mlx,
			game->images.background, c.pos.x * BPP, c.pos.y * BPP) < 0)
		return (!perrno_mlx());
	return (1);
}

bool	render_tile(t_game *game, t_entity c, void *extras)
{
	int	outcome;
	(void) extras;
	
	outcome = -1;
	if (c.chr == EMPTY_CHAR)
		outcome = 1;
	else if (c.chr == WALL_CHAR)
		outcome = mlx_image_to_window(game->mlx,
			game->images.wall, c.pos.x * BPP, c.pos.y * BPP);
	else if (c.chr == PLAYER_CHAR)
		outcome = mlx_image_to_window(game->mlx,
			game->images.player, c.pos.x * BPP, c.pos.y * BPP);
	else if (c.chr == COLLECTIBLE_CHAR)
		outcome = mlx_image_to_window(game->mlx,
			game->images.collectible, c.pos.x * BPP, c.pos.y * BPP);
	else if (c.chr == EXIT_CHAR)
		outcome = mlx_image_to_window(game->mlx,
			game->images.exit, c.pos.x * BPP, c.pos.y * BPP);
	else
	{
		perr("Attempted render tile from invalid char: '");
		perr(&c.chr);
		perr("' \n");
	}
	return (!(outcome < 0) || !perrno_mlx());
}


bool	render_init(t_game *game)
{
	// if (!for_each_tile(game, render_background, NULL))
	// 	return (0);
	// if (!for_each_tile(game, render_tile, NULL))
	// 	return (0);
	if (!draw_frame(game))
		return (0);
	return (1);
}