/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:24:47 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/27 10:18:36 by ekeinan          ###   ########.fr       */
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

void free_foes(t_foe *foes)
{
	t_foe	*next;

	while (foes)
	{
	//	printf("free %p!\n", foes);
		next = foes->next;
		free(foes);
		foes = next;
	}
}

int	clean_exit(t_game *game, bool exit_code)
{
	if (game->map)
	{
		free_layout(game->map->layout, game->map->lines);
		free(game->map);
	}
	if (game->foes)
		free_foes(game->foes);
	exit(exit_code);
	return (1);
}

void	victory(t_game *game)
{
	mlx_terminate(game->mlx);
	ft_printf("You've won! :)\n");
	clean_exit(game, EXIT_SUCCESS);
}

void	defeat(t_game *game)
{
	mlx_terminate(game->mlx);
	ft_printf("You've lost :(\n");
	clean_exit(game, EXIT_SUCCESS);
}
