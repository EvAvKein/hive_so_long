/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:16:03 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/31 19:37:07 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# define WINDOW_TITLE			"so_long"

# define KEY_UP					MLX_KEY_W
# define KEY_DOWN				MLX_KEY_S
# define KEY_LEFT				MLX_KEY_A
# define KEY_RIGHT				MLX_KEY_D
# define KEY_MODIFIER_ATTACK	MLX_KEY_LEFT_SHIFT

# define FOE_PENDING			8

# define EMPTY_CHAR				'0'
# define WALL_CHAR				'1'
# define COLLECTIBLE_CHAR		'C'
# define EXIT_CHAR				'E'
# define PLAYER_CHAR			'P'
# define FOE_CHAR				'F'

# define NAVIGATED_CHAR			'-'

# ifndef VISUALIZE
#  define VISUALIZE				0
# endif

# define LAYOUT_MALLOC_CHUNK	512

#endif