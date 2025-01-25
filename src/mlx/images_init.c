/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:03:35 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/14 21:10:12by ekeinan          ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static mlx_image_t *load_image(mlx_t *mlx, char *path)
{
	mlx_texture_t *texture;
	mlx_image_t *img;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	img = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (img);
}

static bool load_images(t_game *game)
{
	game->images.background = load_image(game->mlx, "./textures/background.png");
	if (!game->images.background)
		return (!perr("Failed to load background image\n"));
	game->images.wall = load_image(game->mlx, "textures/wall.png");
	if (!game->images.wall)
		return (!perr("Failed to load wall image\n"));
	game->images.collectible = load_image(game->mlx, "textures/collectible.png");
	if (!game->images.collectible)
		return (!perr("Failed to load collectible image\n"));
	game->images.exit = load_image(game->mlx, "textures/exit.png");
	if (!game->images.exit)
		return (!perr("Failed to load exit image\n"));
	game->images.player = load_image(game->mlx, "textures/player.png");
	if (!game->images.player)
		return (!perr("Failed to load player image\n"));
	game->images.foe = load_image(game->mlx, "textures/foe.png");
	if (!game->images.foe)
		return (!perr("Failed to load foe image\n"));
	return (1);
}

static bool draw_background(t_game *game, t_entity c, void *extras)
{
	t_offset		offset;
	
	offset = *(t_offset *)extras;
	if (mlx_image_to_window(game->mlx, game->images.background,
		((int)c.pos.x + offset.x) * BPP, ((int)c.pos.y + offset.y) * BPP) < 0)
		return (!perr("MLX background drawing error\n"));
	return (1);
}

static bool	draw_tile(t_game *game, t_entity c, void *extras)
{
	t_offset		offset;
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
		((int)c.pos.x + offset.x) * BPP, ((int)c.pos.y + offset.y) * BPP) < 0)
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
	return (1);
}
