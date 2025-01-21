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

bool	move_player(t_game *game, char direction, size_t distance)
{
	t_pos		player_pos;
	mlx_instance_t	*player_img;
	mlx_instance_t	*first_wall_img;
	t_entity		ahead;

	player_img = game->images.player->instances;
	first_wall_img = game->images.wall->instances;
	update_pos(&player_pos, (player_img->x - first_wall_img->x) / BPP, (player_img->y - first_wall_img->y)/ BPP);
	while (distance--)
	{
		ahead = adjacent_entity(game->map->layout, player_pos, direction);
		if (ahead.chr == WALL_CHAR)
			return (0);
		if (ahead.chr == COLLECTIBLE_CHAR && game->progress.to_collect--)
			image_instance_by_pos(game->images.wall->instances, game->images.collectible, ahead.pos)->enabled = 0;
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
	}
	return (1);
}
