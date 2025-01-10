/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:48:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/10 20:12:26 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../MLX42/include/MLX42/MLX42.h"

typedef struct	s_images {
	mlx_image_t	*background;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
	mlx_image_t	*player;
}				t_images;

void    keyhook(mlx_key_data_t keydata, void *param);
