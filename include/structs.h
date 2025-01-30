/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:07:27 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/30 09:09:28 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#ifndef STRUCTS_H
# define STRUCTS_H


typedef struct	s_images {
	mlx_image_t	*background;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
	mlx_image_t	*player;
	mlx_image_t	*foe;
	mlx_image_t	*sprite_max;
	mlx_image_t	*sprite_min;
}				t_images;

typedef struct  s_map_chars_vali {
	bool	player;
	bool    exit;
	size_t  collectibles;
}           t_map_chars_vali;

typedef struct  s_journey {
	size_t  collected;
	bool    exit_found;
	bool    visualize;
	size_t  visualizing_lines;
}           t_journey;

typedef struct	s_offset {
	int	x;
	int	y;
}			t_offset;

typedef struct	s_progress {
	mlx_image_t		*moves_str;
	mlx_image_t		*attacks_str;
	size_t	moves;
	size_t	attacks;
	size_t	to_collect;
	size_t	standing_on_exit;
}			t_progress;

typedef struct	s_pos {
	size_t	x;
	size_t	y;
}			t_pos;

typedef struct	s_entity {
	char		chr;
	t_pos		pos;
}				t_entity;

typedef struct	s_foe {
	unsigned int	pending;
	t_pos			pos;
	int			standing_on_collectible;
	int			standing_on_exit;
	int		img_i;
	struct s_foe		*next;
}				t_foe;

typedef struct 		s_map 	{
	char  			**layout;
	size_t			width;
	size_t			lines;
}					t_map;

typedef	struct	s_screen {
	int		width;
	int		height;
}				t_screen;

typedef struct		s_game {
	mlx_t			*mlx;
	t_map			*map;
	t_foe			*foes;
	t_images		images;
	t_screen		screen;
	t_progress		progress;
}					t_game;
#endif