/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:36:33 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/30 10:24:55 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

bool	layoutdup_unchunked_swap(t_map *map, char ***dest)
{
	char	**dupe;
	size_t	i;
	char	**original;

	dupe = ft_calloc(map->lines, sizeof(char *));
	if (!dupe)
		return (!perrno("Map processing", ENOMEM));
	i = 0;
	while (i < map->lines)
	{
		dupe[i] = ft_strdup(map->layout[i]);
		if (!dupe[i])
		{
			while (i > 0)
				free(dupe[--i]);
			free(dupe);
			return (!perrno("Map processing", ENOMEM));
		}
		i++;
	}
	original = map->layout;
	map->layout = dupe;
	*dest = original;
	return (1);
}

static bool	upchunk(t_map *map, size_t current_chunks)
{
	char	**upchunked;

	upchunked = ft_calloc(current_chunks + 1, LAYOUT_MALLOC_CHUNK);
	if (!upchunked)
		return (!perrno("Map processing, upchunking", ENOMEM));
	ft_memcpy(upchunked, map->layout, current_chunks * LAYOUT_MALLOC_CHUNK);
	map->layout = upchunked;
	return (1);
}

static bool	save_map_lines(t_map *map, int fd)
{
	char	*line;
	size_t	chunks;

	chunks = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!map->lines)
			map->width = ft_strlen(line) - !!*line;
		line[map->width] = '\0';
		if ((((map->lines + 1) * 8) > (chunks * LAYOUT_MALLOC_CHUNK))
			&& !upchunk(map, chunks++))
		{
			while (map->lines > 0)
				free(map->layout[--map->lines]);
			free(map->layout);
			map->layout = NULL;
			return (!perrno("Map processing", ENOMEM));
		}
		map->layout[map->lines++] = line;
	}
	return (1);
}

bool	save_map(t_game *game, char *map_path)
{
	int		fd;
	size_t	path_len;
	size_t	collectibles;

	path_len = ft_strlen(map_path);
	if (path_len < 5
		|| ft_strncmp(map_path + (path_len - 4), ".ber", 5))
		return (!perr("File path doesn't end with \".ber\"!\n"));
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (!perr("File not found!\n"));
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		return (!perrno("Map processing", ENOMEM));
	game->map->layout = ft_calloc(1, LAYOUT_MALLOC_CHUNK);
	if (!game->map->layout)
		return (!perrno("Map Processing", ENOMEM));
	if (!save_map_lines(game->map, fd)
		|| !validate_map_contents(game, &collectibles)
		|| !validate_map_path(game, collectibles))
		return (0);
	ft_printf("Loaded map %s\n", map_path);
	return (1);
}
