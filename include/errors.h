/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:03:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/03 19:08:58 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// All functions:
// - Print to stder (fd 2)
// - Return the number 1 (to support one-lining in conditional syntax)

// Print "Error\n" 
int	print_error_title();

// Print the provided text
int	print_error(char *text);

// Call `perror` (print the provided text, a colon, and the errno text)
int	print_errno(char *precolon, unsigned int errno);
