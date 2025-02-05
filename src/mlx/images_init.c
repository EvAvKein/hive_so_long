/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:03:35 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/05 11:43:04 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static mlx_image_t	*load_image(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	img = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (img);
}

static bool	load_images(t_game *game)
{
	game->images.background = load_image(game->mlx,
			"textures/background.png");
	game->images.wall = load_image(game->mlx,
			"textures/wall.png");
	game->images.collectible = load_image(game->mlx,
			"textures/collectible.png");
	game->images.exit = load_image(game->mlx,
			"textures/exit.png");
	game->images.player = load_image(game->mlx,
			"textures/player.png");
	game->images.foe = load_image(game->mlx,
			"textures/foe.png");
	game->images.sprite_max = load_image(game->mlx,
			"textures/sprite_max.png");
	game->images.sprite_min = load_image(game->mlx,
			"textures/sprite_min.png");
	if (!game->images.background || !game->images.wall
		|| !game->images.collectible || !game->images.exit
		|| !game->images.player || !game->images.foe
		|| !game->images.sprite_max || !game->images.sprite_min)
		return (!perr("Failed to load images\n"));
	return (1);
}

static bool	draw_background(t_game *game, t_entity c, void *extras)
{
	t_offset	offset;

	offset = *(t_offset *)extras;
	if (mlx_image_to_window(game->mlx, game->images.background,
			((int)c.pos.x + offset.x) * BPP, ((int)c.pos.y + offset.y) * BPP
		) < 0)
		return (!perr("MLX background drawing error\n"));
	return (1);
}

static bool	draw_tile(t_game *game, t_entity c, void *extras)
{
	t_offset	offset;
	mlx_image_t	*img;

	if (c.chr == EMPTY_CHAR)
		return (1);
	offset = *(t_offset *)extras;
	if (c.chr == WALL_CHAR)
		img = game->images.wall;
	else if (c.chr == PLAYER_CHAR)
		img = game->images.player;
	else if (c.chr == COLLECTIBLE_CHAR)
		img = game->images.collectible;
	else if (c.chr == EXIT_CHAR)
		img = game->images.exit;
	else
		return (!perr("Draw image attempt with invalid char\n"));
	if (mlx_image_to_window(game->mlx, img,
			((int)c.pos.x + offset.x) * BPP, ((int)c.pos.y + offset.y) * BPP
		) < 0)
		return (!perr("MLX tile drawing error\n"));
	return (1);
}

bool	draw_images(t_game *game)
{
	t_offset			offset;

	if (!load_images(game))
		return (0);
	offset = calc_offset(game);
	if (!for_each_tile(game, draw_background, &offset)
		|| !for_each_tile(game, draw_tile, &offset))
		return (0);
	if (mlx_image_to_window(game->mlx, game->images.sprite_max,
			0, 0 - BPP * 2) < 0
		|| mlx_image_to_window(game->mlx, game->images.sprite_min,
			0, 0 - BPP * 2) < 0)
		return (!perr("MLX sprite drawing error\n"));
	return (1);
}
