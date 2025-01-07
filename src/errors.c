/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:37:51 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/06 17:51:51 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	perr_titled(char *text)
{
	write(2, "Error\n", 6);
	perr(text);
	return (1);
}

int perr(char *text)
{
	write(2, text, ft_strlen(text));
	return (1);
}

int	perrno(char *precolon, unsigned int errno)
{
	perror(precolon, errno);
	return (1);
}
