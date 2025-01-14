/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:42:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/14 22:50:24 by ekeinan          ###   ########.fr       */
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

# define BASE_WIDTH			640 // Scales well to a lot of screen sizes!
# define BASE_HEIGHT		360 // Scales well to a lot of screen sizes!
# define WIDTH				2 * BASE_WIDTH
# define HEIGHT				2 * BASE_HEIGHT

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

typedef	struct	s_screen_tiles {
	size_t		width;
	size_t		height;
}				t_screen_tiles;

typedef struct		s_game {
	mlx_t			*mlx;
	t_map			*map;
	t_images		*images;
	t_entity		*player;
	t_screen_tiles	screen_tiles;
}					t_game;

bool	load_images(t_game *game);
bool	render_init(t_game *game);
bool	draw_frame(t_game *game);

bool	for_each_tile(t_game *game,
			bool(*func)(t_game *game, t_entity c, void *extras),
			void *extras);
bool	print_layout(char **layout, size_t lines, int fd);

bool	save_map(t_game *game, char *map_path);
bool	layoutdup_unchunked_swap(t_map *map, char ***dest);

bool	validate_map_contents(t_game *game, size_t *collectibles);
bool	validate_map_path(t_game *game, size_t collectible);

size_t	smin(size_t first, size_t second);

bool    update_pos(t_entity *entity, size_t new_y, size_t new_x);
t_pos	adjacent_pos(t_pos pos, char direction);
char	adjacent_char(char **layout, t_pos pos, char direction);
bool	adjacent_replace(char **layout, t_pos pos,
			char direction, char replacement);
bool	adjacent_move(char **layout, t_entity *entity,
			char direction, char trailing);
char    direction_by_i(unsigned int i);

int		clean_exit(t_game *game, bool exit_code);

#endif
