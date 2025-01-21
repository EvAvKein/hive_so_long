/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:38:38 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/15 13:40:25 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	victory(t_game *game)
{
	mlx_terminate(game->mlx);
	ft_printf("Success!\n");
	clean_exit(game, EXIT_SUCCESS);
}

bool	move_player(t_game *game, char direction)
{
	t_pos		player_pos;
	t_entity		ahead;

	update_pos(&player_pos,
		(game->images.player->instances->x - game->images.wall->instances->x) / BPP, 
		(game->images.player->instances->y - game->images.wall->instances->y)/ BPP);
		ahead = adjacent_entity(game->map->layout, player_pos, direction);
	if (ahead.chr == WALL_CHAR)
		return (0);
	if (ahead.chr == COLLECTIBLE_CHAR && game->progress.to_collect--)
		image_instance_by_pos(game->images.collectible,
			(t_offset){.x = game->images.wall->instances->x / BPP,
			.y = game->images.wall->instances->y / BPP},
			ahead.pos)->enabled = 0;
	if (ahead.chr == EXIT_CHAR && ++game->progress.standing_on_exit
			&& !game->progress.to_collect)
			victory(game);
	if (ahead.chr != EXIT_CHAR && game->progress.standing_on_exit && game->progress.standing_on_exit--)
		game->map->layout[player_pos.y][player_pos.x] = EXIT_CHAR;
	else
		game->map->layout[player_pos.y][player_pos.x] = EMPTY_CHAR;
	adjacent_replace(game->map->layout, player_pos, direction, PLAYER_CHAR);
	player_pos = ahead.pos;
	offset_images_within_bounds(game, direction);
	return (1);
}
