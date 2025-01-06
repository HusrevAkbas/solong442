/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:00 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/06 13:13:25 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	offset(t_image *img, int x, int y)
{
	return (y * img->linelen + x * (img->bits_p_px / 8));
}

t_image	*new_tile(t_screen *screen, int width, int heigth)
{
	t_image	*tile;
	char	*addr;
	int		x;
	int		y;

	tile = malloc(sizeof(t_image));
	tile->img = mlx_new_image(screen->mlx, width, heigth);
	tile->heigth = heigth;
	tile->width = width;
	tile->address = mlx_get_data_addr(tile->img, &tile->bits_p_px, &tile->linelen, &tile->endian);
	x = 0;
	y = 0;
	while (y < tile->heigth)
	{
		x = 0;
		while (x < tile->width)
		{
			addr = tile->address + offset(tile, x, y);
			*(unsigned int *)addr = 0x11AAFF22;
			x++;
		}
		y++;
	}
	return (tile);
}

void	set_images(t_screen *screen)
{
	t_image	sprite;
	t_image	background;
	t_image	*tile;
	char	*add;
	char	*add2sp;
	int		color = 16711680;
	background.img = mlx_new_image(screen->mlx, 200, 200);
	background.address = mlx_get_data_addr(background.img, &background.bits_p_px, &background.linelen, &background.endian);
	sprite.img = mlx_xpm_file_to_image(screen->mlx, "assets/Eyemonster.xpm", &sprite.width, &sprite.heigth);
	if (!sprite.img)
		return ;
	sprite.address = mlx_get_data_addr(sprite.img, &sprite.bits_p_px, &sprite.linelen, &sprite.endian);
	ft_printf("value of x 0 y 0: %c\n", *sprite.address);
	int x = 0;
	int y = 0;
	while (x < 200)
	{
		y = 0;
		color = 16711680;
		while (y < 200)
		{
			add = background.address + (y * background.linelen + x * (background.bits_p_px / 8));
			if (y < sprite.heigth)
			{
				add2sp = sprite.address + (y * sprite.linelen + x * (sprite.bits_p_px / 8));
				if (*add2sp == 0 && *(add2sp + sprite.bits_p_px / 8) == 0)
					*(unsigned int *)add2sp = color;
			}
			*(unsigned int *)add = color;
			y++;
			color -= 2;
		}
		x++;
	}
	tile = new_tile(screen, TILE_W, TILE_H);
	mlx_put_image_to_window(screen->mlx, screen->win, background.img, 0, 0);
	mlx_put_image_to_window(screen->mlx, screen->win, sprite.img, 0, 0);
	mlx_put_image_to_window(screen->mlx, screen->win, tile->img, 1, 64);
	//mlx_destroy_image(screen->mlx ,image.img);
	//free(image.img);
}
