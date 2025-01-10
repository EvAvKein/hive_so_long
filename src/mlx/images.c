/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:03:35 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/10 21:18:52 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static mlx_image_t *load_image(mlx_t *mlx, char *path)
{
	mlx_texture_t *texture;
	mlx_image_t *img;

	texture = mlx_load_png(path);
	printf("%s\n", path);
	if (!texture)
		return (NULL);
	printf("texture %p\n", texture);
	img = mlx_texture_to_image(mlx, texture);
	printf("image\n");
	return (img);
}

bool load_images(t_game *game)
{
	t_images *images;
	
	images = ft_calloc(1, sizeof(t_images));
	if (!images)
		return (!perrno("Image saving", ENOMEM));
	printf("1\n");
	images->background = load_image(game->mlx, "./textures/background2.png");
	printf("1.5\n");
	if (!images->background)
		return (!perr("Failed to load background image\n"));
	printf("2\n");
	images->wall = load_image(game->mlx, "textures/wall.png");
	if (!images->wall)
		return (!perr("Failed to load wall image\n"));
	printf("3\n");
	images->collectible = load_image(game->mlx, "textures/collectible.png");
	if (!images->collectible)
		return (!perr("Failed to load collectible image\n"));
	printf("4\n");
	images->exit = load_image(game->mlx, "textures/exit.png");
	if (!images->exit)
		return (!perr("Failed to load exit image\n"));
	printf("5\n");
	images->player = load_image(game->mlx, "textures/player.png");
	if (!images->player)
		return (!perr("Failed to load player image\n"));
	printf("6\n");
	game->images = images;
	printf("7\n");
	return (1);
}
