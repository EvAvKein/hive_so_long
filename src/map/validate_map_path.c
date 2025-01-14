/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:11:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/14 19:00:18 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static bool update_pos_if_player(t_game *game, t_entity c, void *extras)
{
	(void) extras;

	if (c.chr == PLAYER_CHAR)
	{
		update_pos(game->player, c.pos.y, c.pos.x);
		return (0);
	}
	return (1);
}

static bool	init_player(t_game *game)
{
	game->player = ft_calloc(1, sizeof(t_entity));
	if (!game->player)
		return (!perrno("Player init", ENOMEM));
	game->player->chr = PLAYER_CHAR;
	for_each_tile(game, update_pos_if_player, NULL);
	if (!game->player->pos.x && !game->player->pos.y)
		return (!perr("BUG: Found player in validation but not init\n"));
	return (1);
}

static void	navigate(char **replica, t_pos pos, t_map_path_vali *journey)
{
	unsigned int	i;
	char			*tile;
	char			chr;

	tile = &replica[pos.y][pos.x];
	chr = *tile;
	if (chr == WALL_CHAR || chr == NAVIGATED_CHAR)
		return ;
	if (chr == COLLECTIBLE_CHAR)
		journey->collected++;
	if (chr == EXIT_CHAR)
		journey->exit_found++;
	*tile = NAVIGATED_CHAR;
	i = 0;
	while (i < 4)
		navigate(replica, adjacent_pos(pos, direction_by_i(i++)), journey);
}

bool	validate_map_path(t_game *game, size_t collectibles)
{
	char			**replica;
	t_map_path_vali	journey;

	ft_bzero(&journey, sizeof(t_map_path_vali));
	if (!layoutdup_unchunked_swap(game->map, &replica))
		return (0);
	if (!init_player(game))
		return (0);
	navigate(replica, game->player->pos, &journey);
	if (journey.collected < collectibles)
		return (perr_titled("Map validation: Unreachable collectibles!\n")
			&& !print_layout(replica, game->map->lines, 2));
	if (!journey.exit_found)
		return (perr_titled("Map validation: Unreachable exit!\n")
			&& !print_layout(replica, game->map->lines, 2));
	return (1);
}
