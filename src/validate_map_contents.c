/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_contents.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:11:38 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/07 10:14:56 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	validate_char(char chr, t_map_chars_vali *data)
{
	if (chr == EMPTY_CHAR || chr == WALL_CHAR)
		return (1);
	else if (chr == COLLECTIBLE_CHAR)
		data->collectible++;
	else if (chr == EXIT_CHAR)
	{
		if (data->exit)
			return (!perr_titled("Map can only have 1 exit!\n"));
		data->exit++;
	}
	else if (chr == PLAYER_CHAR)
	{
		if (data->player)
			return (!perr_titled("Map can only have 1 player :(\n"));
		data->player++;
	}
	else
		return (perr_titled("Map has invalid character: ")
				&& perr(&chr) && !perr("\n"));
	return (1);
}

static bool validate_line(t_map *map, t_map_chars_vali *data, size_t line_i)
{
	char	*line;
	size_t	char_i;

	char_i = 0;
	line = map->layout[line_i];
	if (!line_i || ((line_i + 1) == map->lines))
	{
		while (line[char_i])
			if (line[char_i++] != WALL_CHAR)
				return (!perr_titled("Map not walled!\n"));
	}
	else
	{
		while (line[char_i])
		{
			if ((!char_i || ((char_i + 1) == map->width)) && line[char_i] != WALL_CHAR)
				return (!perr_titled("Map not walled!\n"));
			if (!validate_char(line[char_i++], data))
				return (0);
		}
	}
	if (char_i >= map->width)
		return (!perr_titled("Map not rectangular!\n"));
}

bool validate_map_contents(t_map *map)
{
	t_map_chars_vali	*data;
	size_t		line_i;

	data = ft_calloc(1, sizeof(t_map_chars_vali));
	if (!data)
		return (!perrno("Map validation", ENOMEM));
	if (map->lines)
		map->width = ft_strlen(map->layout[1]);
	else
		map->width = 0;
	line_i = 0;
	while (line_i < map->lines)
	{
		if (!validate_line(map->layout[line_i++], data, line_i))
			return (0);
	}
	if (map->width < 3 || map->lines < 3)
		return (!perr_titled("Map too small!\n"));
	return (1);
}
