/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:24:47 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/15 13:46:51 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void free_layout(char **layout, size_t lines)
{
	size_t	i;

	i = 0;
	while (i < lines)
		free(layout[i++]);
	free(layout);
}

int	clean_exit(t_game *game, bool exit_code)
{
	if (game->map)
	{
		free_layout(game->map->layout, game->map->lines);
		free(game->map);
	}
	exit(exit_code);
	return (1);
}
