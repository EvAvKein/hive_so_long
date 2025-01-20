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
	return (1);
}

static bool	draw_image_by_chr(t_game *game, t_entity c, void *extras)
{
	t_offset		offset;
	mlx_image_t	*img;

	offset = *(t_offset *)extras;
	img = NULL;
	if (c.chr == WALL_CHAR)
		img = game->images.wall;
	else if (c.chr == PLAYER_CHAR)
		img = game->images.player;
	else if (c.chr == COLLECTIBLE_CHAR)
		img = game->images.collectible;
	else if (c.chr == EXIT_CHAR)
		img = game->images.exit;
	else if (c.chr != EMPTY_CHAR)
		return (!perr("Draw image attempt with invalid char\n"));
	if (mlx_image_to_window(game->mlx, game->images.background,
		((int)c.pos.x + offset.x) * BPP, ((int)c.pos.y + offset.y) * BPP) < 0
		|| (img && mlx_image_to_window(game->mlx, img,
		((int)c.pos.x + offset.x) * BPP, ((int)c.pos.y + offset.y) * BPP) < 0))
		return (!perr("MLX image drawing error\n"));
	return (1);
}

static t_offset calc_initial_offset(t_game *game)
{
	t_offset			offset;
	t_pos		player;

	ft_bzero(&offset, sizeof(t_offset));
	if ((size_t)game->screen.width > game->map->width * BPP)
		offset.x = (game->screen.width / BPP / 2) - (game->map->width / 2);	
	if ((size_t)game->screen.height > game->map->lines * BPP)
		offset.y = (game->screen.height / BPP / 2) - (game->map->lines / 2);
	if (offset.x && offset.y)
		return (offset);
		//ft_printf("sx=%i, sy=%i\n", offset.x, offset.y);
	if (game->images.player->instances)
		update_pos(&player, (size_t)game->images.player->instances->x / BPP,
			(size_t)game->images.player->instances->y / BPP);
	else
		init_player_pos(game, &player);
	if (!offset.x)
		offset.x = clamp((0 - game->map->width + (game->screen.width / BPP)),
				(0 - player.x + (game->screen.width / BPP / 2)), 0);
	if (!offset.y)
		offset.y = clamp((0 - game->map->lines + (game->screen.height / BPP)),
				(0 - player.y + (game->screen.height / BPP / 2)), 0);
	//ft_printf("ox=%i, oy=%i\n", offset.x, offset.y);
	return (offset);
}

bool	draw_images(t_game *game)
{
	t_offset			offset;

	if (!game->images.player)
		load_images(game);
	offset = calc_initial_offset(game);	
	if (!for_each_tile(game, draw_image_by_chr, &offset))
		return (0);
	return (1);
}
