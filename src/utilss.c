/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilss.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:40:30 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/15 14:41:42 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool update_pos_if_player(t_game *game, t_entity c, void *extras)
{
	(void) game;
	
	if (c.chr == PLAYER_CHAR)
	{
		update_pos((t_pos *) extras, c.pos.x, c.pos.y);
		return (0);
	}
	return (1);
}

bool	init_player_pos(t_game *game, t_pos *nav_pos)
{
	for_each_tile(game, update_pos_if_player, nav_pos);
	return (nav_pos->x && nav_pos->y);
}

void	edit_attack_counters(t_game *game, size_t new_count)
{
	char 	 *itoa;
	char		*new_string;

	if (game->progress.attacks_str)
		mlx_delete_image(game->mlx, game->progress.attacks_str);
	itoa = ft_itoa(new_count);
	new_string = ft_strjoin("Attacks: ", ft_itoa(new_count));
	printf("hmmm\n");
	if (!itoa || !new_string)
	{
		if (itoa)
			free(itoa);
		game->progress.attacks_str = mlx_put_string(game->mlx,
			"ERROR: Memory allocation failed\n", 0, 0);
		return ;
	}
	printf("attacks counter edited\n");
  game->progress.attacks_str = mlx_put_string(game->mlx, new_string, 0, 0);
	free(itoa);
	free(new_string);
}
