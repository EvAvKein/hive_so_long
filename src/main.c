/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:49:11 by ekeinan           #+#    #+#             */
/*   Updated: 2025/01/09 19:46:29 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


// static bool	load_assets(t_game *game)
// {

// }

static bool	launch_game(mlx_t *mlx, t_game *game)
{
	(void) game;
	mlx = mlx_init(WIDTH, HEIGHT, "so_long", false);
	if (!mlx)
		return (EXIT_FAILURE);
	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	ft_memset(img->pixels, 255, WIDTH * HEIGHT * sizeof(int));
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		clean_exit(mlx, game, EXIT_FAILURE);
	mlx_key_hook(mlx, keyhook, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	mlx_t	mlx;
	t_game	game;

	if (argc < 2)
		return (perr("Map please :)\n"));
	if (argc > 2)
		return (perr("Just one map please :(\n"));
	ft_bzero(&game, sizeof(t_game));
	if (!save_map(&game, argv[1]))
		clean_exit(NULL, &game, EXIT_FAILURE);
	return (launch_game(&mlx, &game));
}
