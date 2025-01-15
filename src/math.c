/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:25:14 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/15 15:43:17 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

size_t	min_s(size_t first, size_t second)
{
	if (first < second)
		return (first);
	return (second);
}

size_t	clamp_s(size_t min, size_t num, size_t max)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}

size_t	safe_minus(size_t first, size_t second)
{
	if (first < second)
		return (0);
	return (first - second);
}