/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:01:55 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/30 11:39:52 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	is_filename_ok(char *arg)
{
	int	length;

	if (!arg)
		return (0);
	length = ft_strlen(arg);
	if (length <= 4)
		return (0);
	if (arg[length - 4] != '.' || arg[length - 3] != 'b'
		|| arg[length - 2] != 'e' || arg[length - 1] != 'r')
		return (0);
	return (1);
}

void	set_map_size(t_screen *screen)
{
	int	heigth;

	screen->map_w = ft_strlen(screen->map[0]);
	heigth = 0;
	while (screen->map[heigth])
		heigth++;
	screen->map_h = heigth;
}

int	main(int argc, char **argv)
{
	t_screen	screen;

	if (argc != 2)
		return (ft_printf("Error\nSet a map with extension '.ber'\n"));
	ft_memset(&screen, 0, sizeof(t_screen));
	screen.map = set_map(argv[1], &screen.count_collectible);
	if (!screen.map)
		return (ft_printf("Error\nInvalid map, filename or no such file\n"));
	screen.count_moves = 0;
	set_map_size(&screen);
	screen.mlx = mlx_init();
	if (!screen.mlx)
		clean_exit(&screen);
	screen.win = mlx_new_window(screen.mlx, TILE_SIZE * (screen.map_w),
			TILE_SIZE * (screen.map_h), "I LIKE TO MOVE IT MOVE IT");
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
