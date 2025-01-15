/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:49:11 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/15 15:28:23 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static bool	launch_game(t_game *game)
{
	game->mlx = mlx_init(game->screen.width, game->screen.height, "so_long", true);
	if (!game->mlx)
		return (clean_exit(game, EXIT_FAILURE));
	mlx_key_hook(game->mlx, keyhook, game);
	mlx_resize_hook(game->mlx, resizehook, game);	
	load_images(game);
	render_init(game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (clean_exit(game, EXIT_SUCCESS));
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc < 2)
		return (perr("Map please :)\n"));
	if (argc > 2)
		return (perr("Just one map please :(\n"));
	ft_bzero(&game, sizeof(t_game));
	game.screen.width = INIT_WIDTH;
	game.screen.height = INIT_HEIGHT;
	if (!save_map(&game, argv[1]))
		clean_exit(&game, EXIT_FAILURE);
	return (launch_game(&game));
}
