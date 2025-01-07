/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:11:59 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/07 11:14:22 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# define EMPTY_CHAR			'0'
# define WALL_CHAR			'1'
# define COLLECTIBLE_CHAR	'C'
# define EXIT_CHAR			'E'
# define PLAYER_CHAR		'P'

# define UP_CHAR			'U'
# define DOWN_CHAR			'D'
# define LEFT_CHAR			'L'
# define RIGHT_CHAR			'R'

# define NAVIGATED_CHAR		'-'

# define LAYOUT_MALLOC_CHUNK 512

typedef struct  s_map_data {
	bool    player;
	size_t  collectible;
	bool    exit;
}           t_map_data;

typedef struct 		s_map 	{
	char  			**layout;
	size_t			width;
	size_t			lines;
}					t_map;

#endif
