/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:00:09 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/06 21:11:35 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char    direction_by_i(unsigned int i)
{
    if (i == 0)
		return (UP_CHAR);
    if (i == 1)
		return (LEFT_CHAR);
	if (i == 2)
		return (RIGHT_CHAR); 
	if (i == 3)
		return (DOWN_CHAR);
    return (perr("BUG: direction_by_i received i of '")
            && perr(&i) && !perr("' (ascii representation)\n"));
}