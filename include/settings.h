/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:16:03 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/30 09:16:04 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# define WINDOW_TITLE		"so_long"
# define WINDOW_SCALE		2

# define TILE_PADDING			1

# define FOE_PENDING    8

# define EMPTY_CHAR			'0'
# define WALL_CHAR			'1'
# define COLLECTIBLE_CHAR	'C'
# define EXIT_CHAR			'E'
# define PLAYER_CHAR		'P'
# define FOE_CHAR			'F'

# define NAVIGATED_CHAR		'-'

# ifndef VISUALIZE
#  define VISUALIZE 0
# endif

# define LAYOUT_MALLOC_CHUNK 512

#endif