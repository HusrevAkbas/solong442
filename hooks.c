/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husrevakbas <husrevakbas@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:41:51 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/26 19:11:45 by husrevakbas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
/*
	w: 119
	a: 97
	s: 115
	d: 100
	r: 114
	space: 32
	esc: 65307
	left arrow: 65361
	right arrow: 65363
	up arrow: 65362
	down arrow: 65364
	backspace: 65288
	enter: 65293
*/

void	del_image(void *image)
{
	t_image	*img;

	img = image;
	mlx_destroy_image(img->mlx, img->img);
	if (img->bg)
	{
		mlx_destroy_image(img->mlx, img->bg->img);
		free(img->bg);
		img->bg = NULL;
	}
	free(img);
	img = NULL;
}

void	del_enemy(void *content)
{
	free(content);
}

void	clean_exit(t_screen *screen)
{
	int	i;

	if (screen->images)
		ft_lstclear(&screen->images, &del_image);
	clear_map(screen->map, screen->map_h - 1);
	i = 9;
	while (i > 0 && screen->assets[i])
	{
		i--;
		del_image(screen->assets[i]);
	}
	if (screen->enemies)
		ft_lstclear(&screen->enemies, &del_enemy);
	if (screen->big_picture)
		del_image(screen->big_picture);
	if (screen->player)
		free(screen->player);
	if (screen->win)
		mlx_destroy_window(screen->mlx, screen->win);
	if (screen->mlx)
	{
		mlx_destroy_display(screen->mlx);
		free(screen->mlx);
	}
	exit (0);
}

int	clean_exit_button(t_screen *screen)
{
	clean_exit(screen);
	return (0);
}

int	run_key_hook(int keycode, t_screen *screen)
{
	if (keycode == 65307)
		clean_exit(screen);
	if (keycode == 65362 || keycode == 119)
		move_up(screen);
	if (keycode == 65364 || keycode == 115)
		move_down(screen);
	if (keycode == 65363 || keycode == 100)
		move_right(screen);
	if (keycode == 65361 || keycode == 97)
		move_left(screen);
	return (0);
}
