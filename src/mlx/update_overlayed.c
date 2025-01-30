/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_overlayed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 08:41:32 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/30 09:51:20 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

bool toggle_sprite(t_images *img, mlx_image_t *sprite, bool active)
{
	if (active)
	{
		sprite->instances->x = img->player->instances->x - BPP / 2;
		sprite->instances->y = img->player->instances->y - BPP / 2;
		if (img->foe->count)
			sprite->instances->z = img->foe->instances[img->foe->count - 1].z + 1;
	}
	else
		sprite->instances->y = -BPP * 2;
	return (1);
}

void update_sprites(t_game *game, bool boost)
{
	t_images	img;

	img = game->images;
	if (boost)
	{
		toggle_sprite(&img, img.sprite_max, 1);
		toggle_sprite(&img, img.sprite_min, 0);
	}
	if (img.sprite_max->instances->y > 0)
	{
		toggle_sprite(&img, img.sprite_max, 0);
		toggle_sprite(&img, img.sprite_min, 1);
	}
	else if (img.sprite_min->instances->y > 0)
		toggle_sprite(&img, img.sprite_min, 0);
}

void	increment_move_counters(t_game *game)
{
	size_t	new_count;
	char 	 *itoa;
	char		*new_string;

	if (game->progress.moves_str)
		mlx_delete_image(game->mlx, game->progress.moves_str);
	new_count = ++game->progress.moves;
	ft_printf("Moves: %d\n", new_count);
	itoa = ft_itoa(new_count);
	new_string = ft_strjoin("Moves: ", ft_itoa(new_count));
	if (!itoa || !new_string)
	{
		if (itoa)
			free(itoa);
		game->progress.moves_str = mlx_put_string(game->mlx,
			"ERROR: Memory allocation failed\n", 0, game->screen.height - FONT_HEIGHT);
		return ;
	}
  game->progress.moves_str = mlx_put_string(game->mlx, new_string,
		0, game->screen.height - FONT_HEIGHT);
	free(itoa);
	free(new_string);
}

void	edit_attack_counters(t_game *game, size_t new_count)
{
	char 	 *itoa;
	char		*new_string;

	if (game->progress.attacks_str)
		mlx_delete_image(game->mlx, game->progress.attacks_str);
	itoa = ft_itoa(new_count);
	new_string = ft_strjoin("Attacks: ", ft_itoa(new_count));
	if (!itoa || !new_string)
	{
		if (itoa)
			free(itoa);
		game->progress.attacks_str = mlx_put_string(game->mlx,
			"ERROR: Memory allocation failed\n", 0, 0);
		return ;
	}
	game->progress.attacks_str = mlx_put_string(game->mlx, new_string, 0, 0);
	free(itoa);
	free(new_string);
}