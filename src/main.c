/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:49:11 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/10 21:15:54 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static bool	launch_game(t_game *game)
{
	mlx_t *mlx = game->mlx;
	
	mlx = mlx_init(WIDTH, HEIGHT, "so_long", false);
	if (!mlx)
		return (EXIT_FAILURE);
	game->mlx = mlx;
	printf("one\n");
	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	ft_memset(img->pixels, 255, WIDTH * HEIGHT * sizeof(int));
	printf("two\n");
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		clean_exit(game, EXIT_FAILURE);
	//mlx_key_hook(game->mlx, keyhook, NULL);
	printf("three\n");
	load_images(game);
	printf("four\n");
	render_init(game);
	printf("five\n");
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc < 2)
		return (perr("Map please :)\n"));
	if (argc > 2)
		return (perr("Just one map please :(\n"));
	ft_bzero(&game, sizeof(t_game));
	if (!save_map(&game, argv[1]))
		clean_exit(&game, EXIT_FAILURE);
	return (launch_game(&game));
}
