/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:00:09 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/05 11:43:12 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	for_each_tile(t_game *game,
			bool(*func)(t_game *game, t_entity c, void *extras),
			void *extras)
{
	char	**layout;
	char	*line;
	size_t	lines;
	size_t	y;
	size_t	x;

	y = 0;
	layout = game->map->layout;
	lines = game->map->lines;
	while (y < lines)
	{
		x = 0;
		line = layout[y];
		while (line[x])
		{
			if (!func(game, (t_entity){line[x], (t_pos){x, y}}, extras))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	update_pos(t_pos *pos, size_t new_x, size_t new_y)
{
	pos->x = new_x;
	pos->y = new_y;
}

char	direction_by_i(unsigned int i)
{
	if (i == 0)
		return (UP_CHAR);
	if (i == 1)
		return (LEFT_CHAR);
	if (i == 2)
		return (RIGHT_CHAR);
	if (i == 3)
		return (DOWN_CHAR);
	return (perr("BUG: direction_by_i received i of '")
		&& perr((char *)&i) && !perr("' (ascii representation)\n"));
}

char	offset_direction(t_offset offset)
{
	if (!offset.x && !offset.y)
		return ('\0');
	if (offset.x && offset.y)
		return (!perr("BUG: offset_direction received two offsets\n"));
	if (offset.x < 0)
		return (LEFT_CHAR);
	if (offset.x > 0)
		return (RIGHT_CHAR);
	if (offset.y < 0)
		return (UP_CHAR);
	if (offset.y > 0)
		return (DOWN_CHAR);
	return (!perr("BUG: offset_direction received impossible offset\n"));
}

int	clamp(int min, int num, int max)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}
