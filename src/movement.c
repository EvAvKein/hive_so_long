/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:38:38 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/27 16:35:55 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


static void	increment_move_counters(t_game *game)
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

bool	move_player(t_game *game, char direction, bool *move_collects)
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
