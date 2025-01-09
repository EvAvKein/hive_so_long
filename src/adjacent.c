/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacent.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:36:20 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/08 16:55:19 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_pos	adjacent_pos(t_pos pos, char direction)
{
	if (direction == UP_CHAR)
		pos.y -= 1;
	else if (direction == DOWN_CHAR)
		pos.y += 1;
	else if (direction == LEFT_CHAR)
		pos.x -= 1;
	else if (direction == RIGHT_CHAR)
		pos.x += 1;
	else
	{
		perr("BUG: adjacent_char got invalid direction :");
		perr(&direction);
		perr("\n");
	}
	return (pos);
}

char	adjacent_char(char **layout, t_pos pos, char direction)
{
	if (direction == UP_CHAR)
		return (layout[pos.y - 1][pos.x]);
	else if (direction == DOWN_CHAR)
		return (layout[pos.y + 1][pos.x]);
	else if (direction == LEFT_CHAR)
		return (layout[pos.y][pos.x - 1]);
	else if (direction == RIGHT_CHAR)
		return (layout[pos.y][pos.x + 1]);
	else
		return (perr("BUG: adjacent_char got invalid direction\n")
			&& perr(&direction) && !perr("\n"));
}

bool	adjacent_replace(char **layout, t_pos pos, char direction,
			char replacement)
{
	t_pos	target_pos;
	char	*target;

	target_pos = adjacent_pos(pos, direction);
	target = &layout[target_pos.x][target_pos.y];
	*target = replacement;
	return (1);
}

bool	adjacent_move(char **layout, t_entity *entity,
			char direction, char trailing)
{
	char	*prev;
	char	*dest;

	if (WALL_CHAR == adjacent_char(layout, entity->pos, direction))
		return (0);
	prev = &layout[entity->pos.y][entity->pos.x];
	if (direction == UP_CHAR)
		update_pos(&entity->pos, entity->pos.y - 1, entity->pos.x);
	else if (direction == DOWN_CHAR)
		update_pos(&entity->pos, entity->pos.y + 1, entity->pos.x);
	else if (direction == LEFT_CHAR)
		update_pos(&entity->pos, entity->pos.y, entity->pos.x - 1);
	else if (direction == RIGHT_CHAR)
		update_pos(&entity->pos, entity->pos.y, entity->pos.x + 1);
	else
		return (!perr("BUG: adjacent_move got invalid direction\n"));
	dest = &layout[entity->pos.y][entity->pos.x];
	*dest = entity->chr;
	*prev = trailing;
	return (1);
}
