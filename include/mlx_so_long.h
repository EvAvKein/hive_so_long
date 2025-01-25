/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:48:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/15 15:28:13 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_SO_LONG_H
# define MLX_SO_LONG_H

# include "../MLX42/include/MLX42/MLX42.h"

typedef struct	s_images {
	mlx_image_t	*background;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
	mlx_image_t	*player;
	mlx_image_t	*foe;
}				t_images;

void    keyhook(mlx_key_data_t keydata, void *param);
void    resizehook(int width, int height, void* param);

#endif