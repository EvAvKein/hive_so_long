/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:24:47 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/10 18:51:19 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	free_map(t_map	*map)
{
	size_t		i;

	i = 0;
	while (i < map->lines)
		free(map->layout[i++]);
	free(map->layout);
	free(map);
}

int	clean_exit(t_game *game, bool exit_code)
{
	if (game->mlx)
		mlx_terminate(game->mlx);
	if (game->map)
		free_map(game->map);
	if (game->images) // figure out if we need to free the images ourselves too
		free (game->images);
	exit(exit_code);
	return (1);
}
