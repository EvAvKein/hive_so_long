/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:42:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/06 20:28:24 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "libft_full/libft_full.h"
# include "map.h"

typedef struct	s_entity {
	char		chr;
	size_t		x;
	size_t		y;
}				t_entity;

typedef struct s_game {
	t_map		*map;
	
}				t_game;

#endif
