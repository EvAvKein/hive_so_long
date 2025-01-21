/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:42:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/15 15:43:31 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "../libft_full/libft_full.h"
# include "mlx.h"
# include "errors.h"

# define WINDOW_TITLE		"so_long"
# define WINDOW_SCALE		2

# define BASE_WIDTH			640 // Scales well to a lot of screen sizes!
# define BASE_HEIGHT		360 // Scales well to a lot of screen sizes!
# define INIT_WIDTH			BASE_WIDTH * WINDOW_SCALE
# define INIT_HEIGHT		BASE_HEIGHT * WINDOW_SCALE

# define BPP				40

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

typedef struct  s_map_path_vali {
	bool    exit_found;
	size_t  collected;
}           t_map_path_vali;

typedef struct  s_map_chars_vali {
	bool	player;
	bool    exit;
	size_t  collectibles;
}           t_map_chars_vali;

typedef struct	s_offset {
	int	x;
	int	y;
}			t_offset;

typedef struct	s_progress {
	size_t	moves;
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
	t_images		images;
	t_screen		screen;
	t_progress		progress;
}					t_game;

mlx_instance_t * image_instance_by_pos(mlx_image_t *img, t_offset offset, t_pos pos);
bool	draw_images(t_game *game);
bool	move_player(t_game *game, char direction);
t_offset calc_offset(t_game *game);

bool offset_images_within_bounds(t_game *game, char direction);
t_entity	adjacent_entity(char **layout, t_pos pos, char direction);

bool	for_each_tile(t_game *game,
			bool(*func)(t_game *game, t_entity c, void *extras),
			void *extras);
bool	print_layout(char **layout, size_t lines, int fd);

bool	update_pos_if_player(t_game *game, t_entity c, void *extras);
bool	init_player_pos(t_game *game, t_pos *nav_pos);

bool	save_map(t_game *game, char *map_path);
bool	layoutdup_unchunked_swap(t_map *map, char ***dest);

bool	validate_map_contents(t_game *game, size_t *collectibles);
bool	validate_map_path(t_game *game, size_t collectible);

int	clamp(int min, int num, int max);

bool    update_pos(t_pos *pos, size_t new_x, size_t new_y);
t_pos	adjacent_pos(t_pos pos, char direction);
char	adjacent_char(char **layout, t_pos pos, char direction);
bool	adjacent_replace(char **layout, t_pos pos,
			char direction, char replacement);
char    direction_by_i(unsigned int i);
char direction_by_offset(t_offset offset);

int		clean_exit(t_game *game, bool exit_code);

#endif
