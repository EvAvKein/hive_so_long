/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perrs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:37:51 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/13 10:08:44 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	perr_titled(char *text)
{
	write(2, "Error\n", 6);
	perr(text);
	return (1);
}

int	perr(char *text)
{
	write(2, text, ft_strlen(text));
	return (1);
}

int	perrno(char *precolon, int errnum)
{
	char	*str;

	str = strerror(errnum);
	if (str)
	{
		perr(precolon);
		write(2, ": ", 2);
		perr(str);
	}
	return (1);
}
