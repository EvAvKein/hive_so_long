/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:37:51 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/30 08:30:14 by ekeinan          ###   ########.fr       */
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
	errno = errnum;
	perror(precolon);
	return (1);
}

int	perrno_mlx()
{
	char	*strerror;

	strerror = mlx_strerror(mlx_errno);
	if (strerror)
	{
		perr("MLX: ");
		perr((char *) strerror);
		perr("\n");
		free(strerror);
	}
	return (1);
}