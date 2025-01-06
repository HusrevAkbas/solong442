/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:01:55 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/06 16:30:57 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_screen	screen;

	screen.map = get_map();
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
	screen.win = NULL;
	screen.win = mlx_new_window(screen.mlx, TILE_W * (screen.map_w + 1),
				TILE_H * (screen.map_h + 1), "i like to move it");
	if (!screen.win)
		clean_exit(&screen);
	put_images(&screen);
	mlx_key_hook(screen.win, &run_key_hook, &screen);
	mlx_hook(screen.win, 17, 0, clean_exit_button, &screen);
	mlx_loop(screen.mlx);
	clean_exit(&screen);
	return (0);
}
