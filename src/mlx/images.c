/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:03:35 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/14 21:10:12by ekeinan          ###   ########.fr       */
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

bool load_images(t_game *game)
{
	t_images *images;

	images = ft_calloc(1, sizeof(t_images));
	if (!images)
		return (!perrno("Image saving", ENOMEM));
	images->background = load_image(game->mlx, "./textures/background.png");
	if (!images->background)
		return (!perr("Failed to load background image\n"));
	images->wall = load_image(game->mlx, "textures/wall.png");
	if (!images->wall)
		return (!perr("Failed to load wall image\n"));
	images->collectible = load_image(game->mlx, "textures/collectible.png");
	if (!images->collectible)
		return (!perr("Failed to load collectible image\n"));
	images->exit = load_image(game->mlx, "textures/exit.png");
	if (!images->exit)
		return (!perr("Failed to load exit image\n"));
	images->player = load_image(game->mlx, "textures/player.png");
	if (!images->player)
		return (!perr("Failed to load player image\n"));
	game->images = images;
	return (1);
}

// CHECK PERFORMANCE -  SEEMS LIKE A BAD IDEA BUT CBA TO LOOK INTO MLX INTERNALS YET
bool	draw_new_images(t_game *game, t_entity c, void *extras)
{
	t_pos		offset;
	mlx_image_t	*img;
	
	offset = *(t_pos *)extras;
	if (c.chr == WALL_CHAR)
		img = game->images->wall;
	else if (c.chr == PLAYER_CHAR)
		img = game->images->player;
	else if (c.chr == COLLECTIBLE_CHAR)
		img = game->images->collectible;
	else if (c.chr == EXIT_CHAR)
		img = game->images->exit;
	else
		return (0);
	if (mlx_image_to_window(game->mlx, game->images->background,
		c.pos.x + offset.x, c.pos.y + offset.y) < 0
		|| mlx_image_to_window(game->mlx, img,
		c.pos.x + offset.x, c.pos.y + offset.y) < 0)
		return (!perr("MLX image drawing error\n"));
	return (1);
}

bool	draw_frame(t_game *game)
{
	t_pos	offset;
	
	offset.x = smin((game->player->pos.x * BPP) - (WIDTH / 2),
				(game->map->width * BPP) - WIDTH);
	offset.y = smin((game->player->pos.y * BPP) - (HEIGHT / 2),
				(game->map->lines * BPP) - HEIGHT);
	if (!for_each_tile(game, draw_new_images, &offset))
		return (0);
	return (1);
	// while (i < images->wall->count)
	// 	images->wall->instances[i].x;
	// while (i < images->player)
	// 	images->player->instances[i].x;
	// while (i < images->collectible->count)
	// 	images->collectible->instances[i].x;
	// while (i < images->exit->count)
	// 	images->exit->instances[i].x;
}