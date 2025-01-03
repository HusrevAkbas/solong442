/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:00 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/03 16:16:38 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	set_images(t_screen *screen)
{
	t_image	sprite;
	t_image	background;
	char	*add;
	background.img = mlx_new_image(screen->mlx, 200, 200);
	background.address = mlx_get_data_addr(background.img, &background.bits_per_pixel, &background.line_length, &background.endian);
	ft_printf("len: %i, bits: %i, endian: %i\n", background.line_length, background.bits_per_pixel, background.endian);
	sprite.img = mlx_xpm_file_to_image(screen->mlx, "assets/Eyemonster.xpm", &sprite.width, &sprite.heigth);
	if (!sprite.img)
		return ;
	int x = 0;
	int y = 0;
	while (x < 200)
	{
		y = 0;
		while (y < 200)
		{
			add = background.address + (y * background.line_length + x * (background.bits_per_pixel / 8));
			*(unsigned int *)add = 0xFF0000;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(screen->mlx, screen->win, background.img, 0, 0);
	mlx_put_image_to_window(screen->mlx, screen->win, sprite.img, 0, 0);
	//mlx_destroy_image(screen->mlx ,image.img);
	//free(image.img);
}
