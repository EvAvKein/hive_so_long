/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 08:34:21 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/07 12:32:12 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_char_with_color(char c, int fd)
{
	if (c == NAVIGATED_CHAR)
		write(fd, "\033[0;37m", 7);
	else if (c == EMPTY_CHAR)
		write(fd, "\033[0;32m", 7);
	else if (c == WALL_CHAR)
		write(fd, "\033[0;33m", 7);
	else if (c == EXIT_CHAR)
		write(fd, "\033[1;30m", 7);
	else if (c == PLAYER_CHAR)
		write(fd, "\033[1;32m", 7);
	else if (c == COLLECTIBLE_CHAR)
		write(fd, "\033[1;34m", 7);
	else if (c == FOE_CHAR)
		write(fd, "\033[1;35m", 7);
	else
	{
		perr("BUG: print_char_with_color received invalid character: ");
		perr(&c);
		perr("\n");
		write(fd, "\033[0m", 4);
	}
	write(fd, &c, 1);
}

bool	print_layout(char **layout, size_t lines, int fd)
{
	size_t	line_len;
	size_t	line_i;
	size_t	char_i;
	char	prev_char;

	line_len = ft_strlen(layout[0]);
	line_i = 0;
	prev_char = '\0';
	while (line_i < lines)
	{
		char_i = 0;
		while (char_i < line_len)
		{
			if (layout[line_i][char_i] == prev_char)
				write(fd, &prev_char, 1);
			else
				print_char_with_color(layout[line_i][char_i], fd);
			prev_char = layout[line_i][char_i++];
		}
		write(fd, "\n", 1);
		line_i++;
	}
	write(fd, "\033[0m", 4);
	return (1);
}

bool	print_journey(t_journey *journey, int fd)
{
	if (journey)
	{
		write(fd, "Exit ", 5);
		if (journey->exit_found)
			write(fd, "found", 5);
		else
		{
			write(fd, "not found", 9);
		}
		write(fd, ", ", 3);
		write(fd, "collected: ", 11);
		ft_putnbr_fd(journey->collected, fd);
		write(fd, "\n", 1);
		return (1);
	}
	return (0);
}

bool	print_layout_journey_and_pause(
	char **layout, t_journey *journey, int fd)
{
	char	terminal[1];

	print_layout(layout, journey->visualizing_lines, fd);
	print_journey(journey, fd);
	write(fd, "\033[37m(Type S to skip visualizer)\n\033[0m", 38);
	read(0, terminal, 1);
	return (terminal[0] != 'S' && terminal[0] != 's');
}
