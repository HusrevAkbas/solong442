/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:01:55 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/23 13:45:27 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_screen	screen;

	if (argc != 2)
		return (ft_printf("You need to set a map\n"));
	screen.map = set_map(argv[1]);
	if (!screen.map)
		return (ft_printf("Invalid map, invalid filename or wrong file"));
	screen.count_moves = 0;
	set_map_size(&screen);
	int i = 0;
	while (screen.map[i])
	{
		ft_printf("%s\n", screen.map[i]);
		i++;
	}
	ft_printf("map w: %i, map h %i\n", screen.map_w, screen.map_h);
	screen.mlx = mlx_init();
	if (!screen.mlx)
		clean_exit(&screen);
	screen.win = mlx_new_window(screen.mlx, TILE_SIZE * (screen.map_w),
				TILE_SIZE * (screen.map_h), "i like to move it");
	if (!screen.win)
		clean_exit(&screen);
	put_images(&screen);
	mlx_key_hook(screen.win, &run_key_hook, &screen);
	mlx_hook(screen.win, 17, 0, clean_exit_button, &screen);
	mlx_loop_hook(screen.mlx, &animate, &screen);
	mlx_loop(screen.mlx);
	clean_exit(&screen);
	return (0);
}
