/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:38:38 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/30 09:00:07 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool update_pos_if_player(t_game *game, t_entity c, void *extras)
{
	(void) game;
	
	if (c.chr == PLAYER_CHAR)
	{
		update_pos((t_pos *) extras, c.pos.x, c.pos.y);
		return (0);
	}
	return (1);
}

bool	init_player_pos(t_game *game, t_pos *nav_pos)
{
	for_each_tile(game, update_pos_if_player, nav_pos);
	return (nav_pos->x && nav_pos->y);
}

static bool collect_collectible(t_game *game, t_entity *collectible,
	bool *move_collects)
{
	mlx_instance_t *img;

	if (collectible->chr != COLLECTIBLE_CHAR)
		return (!perr("Collect attempt with non-collectible tile!\n"));
	img = image_instance_by_pos(game->images.collectible,
		(t_offset){.x = game->images.wall->instances->x / BPP,
		.y = game->images.wall->instances->y / BPP},
		collectible->pos);
	if (!img)
		return (!perr("Collect attempt failed to find corresponding image!!\n"));
	img->enabled = 0;
	game->progress.to_collect--;
	*move_collects = 1;
	edit_attack_counters(game, ++game->progress.attacks);
	create_foe(game, collectible->pos);
	return (1);
}

static bool	move_player(t_game *game, char direction, bool *move_collects)
{
	t_pos		player_pos;
	t_entity		ahead;

	update_pos(&player_pos,
		(game->images.player->instances->x - game->images.wall->instances->x) / BPP,
		(game->images.player->instances->y - game->images.wall->instances->y) / BPP);
	ahead = adjacent_entity(game->map->layout, player_pos, direction);
	if (ahead.chr == WALL_CHAR)
		return (0);
	if (ahead.chr == FOE_CHAR)
	{
		defeat(game);
		return (0);
	}
	increment_move_counters(game);
	if (ahead.chr == COLLECTIBLE_CHAR)
		collect_collectible(game, &ahead, move_collects);
	if (ahead.chr == EXIT_CHAR && ++game->progress.standing_on_exit
		&& !game->progress.to_collect)
		victory(game);
	game->map->layout[player_pos.y][player_pos.x] = EMPTY_CHAR;
	if (ahead.chr != EXIT_CHAR && game->progress.standing_on_exit && game->progress.standing_on_exit--)
		game->map->layout[player_pos.y][player_pos.x] = EXIT_CHAR;
	game->map->layout[ahead.pos.y][ahead.pos.x] = PLAYER_CHAR;
	game->images.player->instances->x += ((ahead.pos.x - player_pos.x) * BPP);
	game->images.player->instances->y += ((ahead.pos.y - player_pos.y) * BPP);
	player_pos = ahead.pos;
	offset_images_within_bounds(game, direction);
	return (1);
}

bool    handle_player_move(t_game *game, mlx_key_data_t e, bool *move_collects)
{
	t_offset    movement;
	
	movement = (t_offset){.x = 0, .y = 0};
	movement.y = 0 - (e.key == MLX_KEY_W) + (e.key == MLX_KEY_S);
	movement.x = 0 - (e.key == MLX_KEY_A) + (e.key == MLX_KEY_D);
	if (!movement.x && !movement.y)
		return (0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT)
		&& game->progress.attacks)
		destroy_foe(game, &movement);
	if (movement.x)
		move_player(game, direction_by_offset(movement), move_collects);
	if (movement.y)
		move_player(game, direction_by_offset(movement), move_collects);
	return (1);
}
