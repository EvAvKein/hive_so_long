/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:00:09 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/08 15:17:21 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	update_pos(t_pos *pos, size_t new_y, size_t new_x)
{
	pos->y = new_y;
	pos->x = new_x;
	return (1);
}

char	direction_by_i(unsigned int i)
{
	if (i == 0)
		return (UP_CHAR);
	if (i == 1)
		return (LEFT_CHAR);
	if (i == 2)
		return (RIGHT_CHAR);
	if (i == 3)
		return (DOWN_CHAR);
	return (perr("BUG: direction_by_i received i of '")
		&& perr((char *)&i) && !perr("' (ascii representation)\n"));
}

bool	print_layout(char **layout, size_t lines, int fd)
{
	size_t	i;

	i = 0;
	while (i < lines)
	{
		ft_putstr_fd(layout[i++], fd);
		ft_putchar_fd('\n', fd);
	}
	return (1);
}
