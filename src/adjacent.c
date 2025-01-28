/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacent.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:36:20 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/27 20:29:53 by ekeinan          ###   ########.fr       */
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
	return (pos);
}

t_entity	adjacent_entity(char **layout, t_pos pos, char direction)
{
	t_entity adjacent;

	adjacent.pos = adjacent_pos(pos, direction);
	adjacent.chr = layout[adjacent.pos.y][adjacent.pos.x];
	return (adjacent);
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


t_foe	*adjacent_foe(t_game *game, t_offset *player_move)
{
	t_images img;
	t_pos	pos;
	t_pos	dest;
	t_foe *foe;

	img = game->images;
	pos = (t_pos){
		.x = (img.player->instances->x - game->images.wall->instances->x) / BPP,
		.y = (img.player->instances->y - game->images.wall->instances->y) / BPP
	};
	dest = (t_pos){.x = pos.x + player_move->x, .y = pos.y + player_move->y};
	foe = game->foes;
	while (foe && (
			(foe->img_i < 0 || !img.foe->instances[foe->img_i].enabled)
			|| (dest.x != foe->pos.x || dest.y != foe->pos.y)))
		foe = foe->next;
	return (foe);
}
