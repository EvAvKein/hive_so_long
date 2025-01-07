/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacent.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:36:20 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/07 09:31:08 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	adjacent_char(t_map *map, size_t own_x, size_t own_y, char direction)
{
	if ((own_x + 1 > map->width) || (own_y + 1 > map->lines))
		return (!perr("BUG: adjacent char is out of bounds\n"));
	if (direction == UP_CHAR)
		return (map->layout[own_y - 1][own_x]);
	if (direction == DOWN_CHAR)
		return (map->layout[own_y + 1][own_x]);
	if (direction == LEFT_CHAR)
		return (map->layout[own_y][own_x - 1]);
	if (direction == RIGHT_CHAR)
		return (map->layout[own_y][own_x + 1]);
	else
		return (perr("BUG: adjacent_char got invalid direction")
			&& perr(&direction) && !perr("\n"));
}

static bool    update_xy(
		t_entity *entity, size_t new_y, size_t new_x)
{
    entity->y = new_y;
    entity->x = new_x;
	return (1);
}

bool	adjacent_move(t_map *map, t_entity *entity,
			char direction, char trailing)
{	
	char	*prev;
	char	*dest;

	if (WALL_CHAR == adjacent_char(map, entity->x, entity->y, direction))
		return (0);
	prev = &map->layout[entity->y][entity->x];
	if (direction == UP_CHAR && update_xy(entity, entity->y - 1, entity->x))
		dest = &map->layout[entity->y - 1][entity->x];
	if (direction == DOWN_CHAR && update_xy(entity, entity->y + 1, entity->x))
		dest = &map->layout[entity->y + 1][entity->x];
	if (direction == LEFT_CHAR && update_xy(entity, entity->y, entity->x - 1))
		dest = &map->layout[entity->y][entity->x - 1];
	if (direction == RIGHT_CHAR && update_xy(entity, entity->y, entity->x + 1))
		dest == &map->layout[entity->y][entity->x + 1];
	else
		return (!perr("BUG: adjacent_move got invalid direction\n"));
	*dest = entity->chr;
	*prev = trailing;
}
