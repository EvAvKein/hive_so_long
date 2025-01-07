/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:11:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/07 18:09:04 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool set_starting_pos(t_map *map, t_entity *player)
{
    size_t  y;
    char    *line;
    size_t  x;

    y = 0;
    while (y < map->lines)
    {
        x = 0;
        line = map->layout[y];
        while (line[x])
        {
            if (line[x] == PLAYER_CHAR)
            {
                player->x = x;
                player->y = y;
                return (1);
            }
        }
        y++;
    }
    return (0);
}

static void navigate(char **replica, t_entity player, t_map_path_vali *journey)
{
    unsigned int    i;
    char            c;

    i = 0;
    while (i < 4)
    {
        c = adjacent_char(replica, player.x, player.y, direction_by_i(i));
        if (c == COLLECTIBLE_CHAR)
            journey->collected++;
        if (c == EXIT_CHAR)
            journey->exit_found++;
        if (c != WALL_CHAR && c != NAVIGATED_CHAR)
        {
            adjacent_move(replica, &player, direction_by_i(i), NAVIGATED_CHAR);
            navigate(replica, player, journey);
        }
    }
}

bool validate_map_path(t_map *map, t_map_chars_vali *data)
{
    char    	    **replica;
    t_map_path_vali journey;
	t_entity	    player;

    replica = layoutdup_unchunked_swap(map);
    if (!replica)
        return (0);
    if (!set_starting_pos(map, &player))
        return (!perr("BUG: Player found at map saving but not at pathing\n"));
    navigate(replica, player, &journey);
	if (data->collectible != journey.collected)
        return (!perr_titled("Map validation: Unreachable collectibles\n"));
    if (!journey.exit_found)
        return (!perr_titled("Map validation: Unreachable exit\n"));
    return (1);
}
