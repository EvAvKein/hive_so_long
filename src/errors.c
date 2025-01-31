/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:37:51 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/30 17:39:22 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
	char *str;
	
	str = strerror(errnum);
	if (str)
	{
		perr(precolon);
		write(2, ": ", 2);
		perr(str);
		free(str);
	}
	return (1);
}
