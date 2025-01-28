/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:42:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/27 16:48:40 by ekeinan          ###   ########.fr       */
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
# include "mlx_so_long.h"
# include "perrors.h"
# include "settings.h"

# define BASE_WIDTH			640 // Scales well to a lot of screen sizes!
# define BASE_HEIGHT		360 // Scales well to a lot of screen sizes!
# define INIT_WIDTH			BASE_WIDTH * WINDOW_SCALE
# define INIT_HEIGHT		BASE_HEIGHT * WINDOW_SCALE

# define BASE_TEXTURE_SIZE		40
# define BPP									(BASE_TEXTURE_SIZE + TILE_PADDING)

# define UP_CHAR			'U'
# define DOWN_CHAR			'D'
# define LEFT_CHAR			'L'
# define RIGHT_CHAR			'R'

# define FONT_HEIGHT		20

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

mlx_instance_t * image_instance_by_pos(mlx_image_t *img, t_offset offset, t_pos pos);
bool	draw_images(t_game *game);
bool	move_player(t_game *game, char direction, bool *move_collects);
bool update_sprites(t_game *game, bool boost);
t_offset calc_offset(t_game *game);

bool create_foe(t_game *game, t_pos pos);
bool play_foes(t_game *game);
void destroy_foe(t_game *game, t_offset *player_move);

void	edit_attack_counters(t_game *game, size_t new_count);
bool offset_images_within_bounds(t_game *game, char direction);
void update_foe_pos(t_foe *foe, mlx_image_t *foe_img, t_pos dest);
t_entity	adjacent_entity(char **layout, t_pos pos, char direction);

bool	for_each_tile(t_game *game,
			bool(*func)(t_game *game, t_entity c, void *extras),
			void *extras);

bool	update_pos_if_player(t_game *game, t_entity c, void *extras);
bool	init_player_pos(t_game *game, t_pos *nav_pos);

bool	save_map(t_game *game, char *map_path);
bool	layoutdup_unchunked_swap(t_map *map, char ***dest);

bool	print_layout(char **layout, size_t lines, int fd);
bool	print_journey(t_journey *journey, int fd);
bool	print_layout_journey_and_pause(
	char **layout, t_journey *journey, int fd);
bool	validate_map_contents(t_game *game, size_t *collectibles);
bool	validate_map_path(t_game *game, size_t collectible);

int	clamp(int min, int num, int max);

bool    update_pos(t_pos *pos, size_t new_x, size_t new_y);
t_pos	adjacent_pos(t_pos pos, char direction);
char	adjacent_char(char **layout, t_pos pos, char direction);
t_foe	*adjacent_foe(t_game *game, t_offset *player_move);
char    direction_by_i(unsigned int i);
char direction_by_offset(t_offset offset);

void	free_layout(char **layout, size_t lines);
int		clean_exit(t_game *game, bool exit_code);
void	victory(t_game *game);
void	defeat(t_game *game);

#endif
