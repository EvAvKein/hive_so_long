/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:42:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/09 20:02:17 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void    keyhook(mlx_key_data_t keydata, void *param)
{
    (void)param;
    if (keydata.key == MLX_KEY_UP)
    {}
    if (keydata.key == MLX_KEY_LEFT)
    {}
    if (keydata.key == MLX_KEY_RIGHT)
    {}
    if (keydata.key == MLX_KEY_DOWN)
    {}
}