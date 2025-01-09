/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:42:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/08 15:34:37 by ekeinan          ###   ########.fr       */
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
# include "errors.h"

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

typedef struct s_game {
	t_map		*map;
	
}				t_game;

bool	print_layout(char **layout, size_t lines, int fd);

bool	save_map(t_game *game, char *map_path);
bool	layoutdup_unchunked_swap(t_map *map, char ***dest);
void	free_map(t_map	*map);

bool	validate_map_contents(t_map *map, size_t *collectibles);
bool	validate_map_path(t_map *map, size_t collectible);

bool    update_pos(t_pos *pos, size_t new_y, size_t new_x);
t_pos	adjacent_pos(t_pos pos, char direction);
char	adjacent_char(char **layout, t_pos pos, char direction);
bool	adjacent_replace(char **layout, t_pos pos,
			char direction, char replacement);
bool	adjacent_move(char **layout, t_entity *entity,
			char direction, char trailing);
char    direction_by_i(unsigned int i);

int		clean_exit(t_game *game);

#endif
