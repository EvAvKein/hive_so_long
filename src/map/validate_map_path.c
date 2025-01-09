/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:11:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/09 19:57:31 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static bool	init_player(t_map *map, t_entity *player)
{
	size_t	y;
	char	*line;
	size_t	x;

	player->chr = PLAYER_CHAR;
	y = 0;
	while (y < map->lines)
	{
		x = 0;
		line = map->layout[y];
		while (line[x])
		{
			if (line[x] == PLAYER_CHAR)
			{
				update_pos(&player->pos, y, x);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (!perr("BUG: Player found at map saving but not at pathing\n"));
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

bool	validate_map_path(t_map *map, size_t collectibles)
{
	char			**replica;
	t_map_path_vali	journey;
	t_entity		player;

	ft_bzero(&journey, sizeof(t_map_path_vali));
	if (!layoutdup_unchunked_swap(map, &replica))
		return (0);
	if (!init_player(map, &player))
		return (0);
	navigate(replica, player.pos, &journey);
	if (journey.collected < collectibles)
		return (perr_titled("Map validation: Unreachable collectibles!\n")
			&& !print_layout(replica, map->lines, 2));
	if (!journey.exit_found)
		return (perr_titled("Map validation: Unreachable exit!\n")
			&& !print_layout(replica, map->lines, 2));
	return (1);
}
