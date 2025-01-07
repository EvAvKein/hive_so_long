/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:11:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/07 10:18:15 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool navigate(char **replica, t_map_data *data, size_t *collected)
{
	

}

static bool validate_completable(t_map *map, t_map_data *data)
{
    char    **replica;
    size_t  collected;

    replica = layoutdup_unchunked_swap(map);
    if (!replica)
        return (0);
    collected = 0;
	
    navigate(replica, data, &collected);
}
