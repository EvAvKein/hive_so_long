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

char	adjacent_char(char **layout, size_t own_x, size_t own_y, char direction)
{
	if (direction == UP_CHAR)
		return (layout[own_y - 1][own_x]);
	if (direction == DOWN_CHAR)
		return (layout[own_y + 1][own_x]);
	if (direction == LEFT_CHAR)
		return (layout[own_y][own_x - 1]);
	if (direction == RIGHT_CHAR)
		return (layout[own_y][own_x + 1]);
	else
		return (perr("BUG: adjacent_char got invalid direction\n")
			&& perr(&direction) && !perr("\n"));
}

static bool    update_xy(
		t_entity *entity, size_t new_y, size_t new_x)
{
    entity->y = new_y;
    entity->x = new_x;
	return (1);
}

bool	adjacent_move(char **layout, t_entity *entity,
			char direction, char trailing)
{	
	char	*prev;
	char	*dest;

	if (WALL_CHAR == adjacent_char(layout, entity->x, entity->y, direction))
		return (0);
	prev = &layout[entity->y][entity->x];
	if (direction == UP_CHAR && update_xy(entity, entity->y - 1, entity->x))
		dest = &layout[entity->y - 1][entity->x];
	if (direction == DOWN_CHAR && update_xy(entity, entity->y + 1, entity->x))
		dest = &layout[entity->y + 1][entity->x];
	if (direction == LEFT_CHAR && update_xy(entity, entity->y, entity->x - 1))
		dest = &layout[entity->y][entity->x - 1];
	if (direction == RIGHT_CHAR && update_xy(entity, entity->y, entity->x + 1))
		dest == &layout[entity->y][entity->x + 1];
	else
		return (!perr("BUG: adjacent_move got invalid direction\n"));
	*dest = entity->chr;
	*prev = trailing;
}
