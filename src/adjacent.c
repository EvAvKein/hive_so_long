/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacent.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:36:20 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/27 19:10:36 by ekeinan          ###   ########.fr       */
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
	else
	{
		//perr("BUG: adjacent_pos got invalid direction: '");
		//perr(&direction);
		//perr("'\n");
	}
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
	t_offset  img_offset;
	t_pos	player_pos;
	t_pos	player_dest;
	t_foe *foe_node;
	
	img_offset = (t_offset){.y = game->images.wall->instances->y, .x = game->images.wall->instances->x};
	player_pos = (t_pos){.x = (game->images.player->instances->x - img_offset.x) / BPP,
		.y = (game->images.player->instances->y - img_offset.y) / BPP};
	player_dest = (t_pos){.x = player_pos.x + player_move->x, .y = player_pos.y + player_move->y};
	foe_node = game->foes;
	while (foe_node && (!game->images.foe->instances[foe_node->img_i].enabled
		|| (player_dest.x != foe_node->pos.x && player_dest.y != foe_node->pos.y)))
		foe_node = foe_node->next;
	if (!foe_node)
   		perr("BUG: destroy_foe - foe not found\n");
	return (foe_node);
}
