/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:49:11 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/27 18:01:09 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static bool	launch_game(t_game *game)
{
	game->mlx = mlx_init(game->screen.width, game->screen.height,
		WINDOW_TITLE, false);
	if (!game->mlx)
		return (clean_exit(game, EXIT_FAILURE));
	mlx_key_hook(game->mlx, keyhook, game);
	draw_images(game);
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
	game = (t_game){
		.mlx = NULL,
		.map = NULL,
		.foes = NULL,
		.images = {
			.background = NULL,
			.wall = NULL,
			.collectible = NULL,
			.exit = NULL,
			.player = NULL,
			.foe = NULL
		},
		.progress = (t_progress){.standing_on_exit = 0, .to_collect = 0,
			.moves = 0, .attacks = 0, .moves_str = NULL, .attacks_str = NULL},
		.screen = (t_screen){.width = INIT_WIDTH, .height = INIT_HEIGHT}
	};
	if (!save_map(&game, argv[1]))
		clean_exit(&game, EXIT_FAILURE);
	return (launch_game(&game));
}
