/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:49:11 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/05 11:43:12 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	keyhook(mlx_key_data_t key_data, void *param)
{
	t_game	*game;
	bool	move_collects;

	move_collects = 0;
	game = param;
	if (key_data.action != MLX_PRESS && key_data.action != MLX_REPEAT)
		return ;
	if (key_data.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(game->mlx);
		clean_exit(game, EXIT_SUCCESS);
	}
	if (!handle_player_move(game, key_data, &move_collects))
		return ;
	play_foes(game);
	update_sprites(game, move_collects);
	if (VISUALIZE)
		print_layout(game->map->layout, game->map->lines, 1);
}

static bool	launch_game(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT,
			WINDOW_TITLE, 1);
	if (!game->mlx)
		return (clean_exit(game, EXIT_FAILURE));
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx_key_hook(game->mlx, keyhook, game);
	if (draw_images(game))
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
		.images = (t_images){
		.background = NULL, .wall = NULL, .collectible = NULL,
		.exit = NULL, .player = NULL, .foe = NULL},
		.progress = (t_progress){.standing_on_exit = 0, .to_collect = 0,
		.moves = 0, .attacks = 0, .moves_str = NULL, .attacks_str = NULL},
	};
	if (!save_map(&game, argv[1]))
		clean_exit(&game, EXIT_FAILURE);
	return (launch_game(&game));
}
