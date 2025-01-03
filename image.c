/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:00 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/03 17:17:19 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	set_images(t_screen *screen)
{
	t_image	sprite;
	t_image	background;
	char	*add;
	char	*add2sp;
	int		color = 16711680;
	background.img = mlx_new_image(screen->mlx, 200, 200);
	background.address = mlx_get_data_addr(background.img, &background.bits_per_pixel, &background.line_length, &background.endian);
	sprite.img = mlx_xpm_file_to_image(screen->mlx, "assets/Eyemonster.xpm", &sprite.width, &sprite.heigth);
	if (!sprite.img)
		return ;
	sprite.address = mlx_get_data_addr(sprite.img, &sprite.bits_per_pixel, &sprite.line_length, &sprite.endian);
	ft_printf("value of x 0 y 0: %c\n", *sprite.address);
	int x = 0;
	int y = 0;
	while (x < 200)
	{
		y = 0;
		color = 16711680;
		while (y < 200)
		{
			add = background.address + (y * background.line_length + x * (background.bits_per_pixel / 8));
			if (y < sprite.heigth)
			{
				add2sp = sprite.address + (y * sprite.line_length + x * (sprite.bits_per_pixel / 8));
				if (*add2sp == 0 && *(add2sp + sprite.bits_per_pixel / 8) == 0)
					*(unsigned int *)add2sp = color;
			}
			*(unsigned int *)add = color;
			y++;
			color -= 2;
		}
		x++;
	}
	mlx_put_image_to_window(screen->mlx, screen->win, background.img, 0, 0);
	mlx_put_image_to_window(screen->mlx, screen->win, sprite.img, 0, 0);
	//mlx_destroy_image(screen->mlx ,image.img);
	//free(image.img);
}
