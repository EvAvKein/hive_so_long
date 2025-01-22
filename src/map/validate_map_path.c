/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:11:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/15 14:40:53 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	navigate(char **replica, t_pos pos, t_journey *journey)
{
	unsigned int	i;
	char			*tile;
	char			chr;

	tile = &replica[pos.y][pos.x];
	chr = *tile;
	if (chr == WALL_CHAR || chr == NAVIGATED_CHAR)
		return ;
	if (journey->visualize)
		journey->visualize = print_layout_and_pause(replica, journey->map_lines,
		1, journey);
	if (chr == COLLECTIBLE_CHAR)
		journey->collected++;
	if (chr == EXIT_CHAR)
		journey->exit_found = 1;
	*tile = NAVIGATED_CHAR;
	i = 0;
	while (i < 4)
		navigate(replica, adjacent_pos(pos, direction_by_i(i++)), journey);
}

bool	validate_map_path(t_game *game, size_t collectibles)
{
	char			**replica;
	t_journey	journey;
	t_pos			nav_pos;

	nav_pos = (t_pos){.x = 0, .y = 0};
	journey = (t_journey){
		.collected = 0, .exit_found = false,
		.visualize = 1, .map_lines = game->map->lines
	};
	if (!layoutdup_unchunked_swap(game->map, &replica))
		return (0);
	if (!init_player_pos(game, &nav_pos))
		return (!perr("BUG: Found player in validation but not init\n"));
	navigate(replica, nav_pos, &journey);
	if (journey.collected < collectibles)
		return (perr_titled("Map validation: Unreachable collectibles!\n")
			&& !print_layout(replica, game->map->lines, 2));
	if (!journey.exit_found)
		return (perr_titled("Map validation: Unreachable exit!\n")
			&& !print_layout(replica, game->map->lines, 2));
	game->progress.to_collect = collectibles;
	return (1);
}
