/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:01:55 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/03 13:38:52 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_screen	screen;

	screen.mlx = mlx_init();
	//screen.win = mlx_new_window(screen.mlx, 200, 200, "lets go baby");
	//mlx_key_hook(screen.win, &run_key_hook, &screen);
	//mlx_hook(screen.win, 17, 0, clean_exit_button, &screen);
	//mlx_loop(screen.mlx);
	// mlx_destroy_window(screen.mlx, screen.win);
	int a = mlx_destroy_display(screen.mlx);
	ft_printf("%i\n", a);
	//clean_exit(&screen);
	return (0);
}
