/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:42:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/30 11:41:41 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft_full/libft_full.h"
# include "structs.h"
# include "perrors.h"
# include "settings.h"

# define INIT_WIDTH			1280
# define INIT_HEIGHT		720

# define BPP				40

# define UP_CHAR			'U'
# define DOWN_CHAR			'D'
# define LEFT_CHAR			'L'
# define RIGHT_CHAR			'R'

# define FONT_HEIGHT		20

bool			save_map(t_game *game, char *map_path);
bool			layoutdup_unchunked_swap(t_map *map, char ***dest);
bool			validate_map_contents(t_game *game, size_t *collectibles);
bool			validate_map_path(t_game *game, size_t collectible);

bool			for_each_tile(t_game *game,
					bool(*func)(t_game *game, t_entity c, void *extras),
					void *extras);

bool			print_layout(char **layout, size_t lines, int fd);
bool			print_journey(t_journey *journey, int fd);
bool			print_layout_journey_and_pause(char **layout,
					t_journey *journey, int fd);

bool			draw_images(t_game *game);
t_offset		calc_offset(t_game *game);
void			offset_images_within_bounds(t_game *game, char direction);

bool			init_player_pos(t_game *game, t_pos *nav_pos);

bool			handle_player_move(t_game *game, mlx_key_data_t e,
					bool *move_collects);
void			increment_move_counters(t_game *game);
void			edit_attack_counters(t_game *game, size_t new_count);

void			play_foes(t_game *game);
void			create_foe(t_game *game, t_pos pos);
void			update_foe_pos(t_foe *foe, mlx_image_t *foe_img, t_pos dest);
void			destroy_foe(t_game *game, t_offset *player_move);

void			update_sprites(t_game *game, bool boost);

t_pos			adjacent_pos(t_pos pos, char direction);
char			adjacent_char(char **layout, t_pos pos, char direction);
t_entity		adjacent_entity(char **layout, t_pos pos, char direction);
t_foe			*adjacent_foe(t_game *game, t_offset *player_move);

int				clamp(int min, int num, int max);
void			update_pos(t_pos *pos, size_t new_x, size_t new_y);
char			direction_by_i(unsigned int i);
char			offset_direction(t_offset offset);
mlx_instance_t	*image_instance_by_pos(mlx_image_t *img,
					t_offset offset, t_pos pos);

void			free_layout(char **layout, size_t lines);
int				clean_exit(t_game *game, bool exit_code);
void			victory(t_game *game);
void			defeat(t_game *game);

#endif
