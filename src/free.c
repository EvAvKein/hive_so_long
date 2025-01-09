/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:24:47 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/06 15:08:51 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_map(t_map	*map)
{
	size_t		i;

	i = 0;
	while (i < map->lines)
		free(map->layout[i++]);
	free(map->layout);
	free(map);
}

int	clean_exit(mlx_t *mlx, t_game *game, bool exit_code)
{
	if (mlx)
		mlx_terminate(mlx);
	if (game->map)
		free_map(game->map);
	exit(exit_code);
	return (1);
}
