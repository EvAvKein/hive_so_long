/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:36:33 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/07 11:37:09 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	free_map(t_map	*map)
{
	size_t		i;

	i = 0;
	while (i < map->lines)
		free(map->layout[i++]);
	free(map->layout);
	free(map);
	return (0);
}

char	**layoutdup_unchunked_swap(t_map *map)
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
	return (original);
}

static bool	upchunk(char ***layout, size_t current_chunk_count)
{
	char	**upchunked;

	upchunked = ft_calloc(current_chunk_count + 1, LAYOUT_MALLOC_CHUNK);
	if (!upchunked)
		return (!perrno("Map processing, upchunking", ENOMEM));
	ft_memcpy(upchunked, *layout, LAYOUT_MALLOC_CHUNK * current_chunk_count);
	*layout = upchunked;
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
			break;
		if (!map->lines)
			map->width = ft_strlen(line) - !!*line;
		line[map->width] = '\0';
		map->layout[map->lines++] = line;
		if (((map->lines * 8) > (chunks * LAYOUT_MALLOC_CHUNK))
			&& !upchunk(&map->layout, chunks))
		{
			while(map->lines > 0)
				free(map->layout[--map->lines]);
			free(map->layout);
			map->layout = NULL;
			return (!perrno("Map processing", ENOMEM));
		}
	}
	return (1);
}

bool	save_map(t_game *game, char *map_path)
{
	int		fd;
	size_t	path_len;

	path_len = ft_strlen(map_path);
	if (path_len < 4
		|| ft_strncmp(map_path + (ft_strlen(map_path) - 4), ".ber", 5))
		return (!perr("The file path doesn't end with \".ber\" >:("));
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (!perr("Couldn't find the file D:"));
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		return (!perrno("Map processing", ENOMEM));
	game->map->layout = ft_calloc(1, LAYOUT_MALLOC_CHUNK);
	if (!game->map->layout)
		return (!perrno("Map Processing", ENOMEM));
	if (!save_map_lines(&game->map, fd) || !validate_map(game->map))
		return (0);
	ft_printf("Loaded map %s\n", map_path);	
	return (1);
}
