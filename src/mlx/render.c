/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:16:07 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/10 20:10:55 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

bool render_background(char c, size_t x, size_t y, void *extras)
{
	t_game *game;
	static size_t debug = 0;

	(void)c;
	game = extras;
	printf("%lu\n", debug);
	if (mlx_image_to_window(game->mlx,
			game->images->background, x * BPP, y * BPP) < 0)
		return (!perrno_mlx());
	return (1);
}

// bool render_tile(char c, size_t x, size_t y, void *extras)
// {
// 	if (map.)
// }

bool render_init(t_game *game)
{
	mlx_image_t *bg_image;

	bg_image = game->images->background;
	if (for_each_tile(game->map, render_background, bg_image))
		return (0);

	//for_each_tile(game->map, render_tile, NULL);
	return (1);
}