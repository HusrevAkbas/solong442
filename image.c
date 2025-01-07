/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:00 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/07 13:45:54 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

char	*get_px_addr(t_image *img, int x, int y)
{
	return (img->address + (y * img->linelen + x * (img->bits_p_px / 8)));
}

void	set_img_data(t_image *img)
{
	img->address = mlx_get_data_addr(img->img, &img->bits_p_px,
				&img->linelen, &img->endian);
}

void	overwrite(t_image *bg, t_image *img, int offx, int offy)
{
	int	x;
	int	y;
	char	*bg_addr;
	char	*img_addr;

	if (!bg || !img || !bg->img || !img->img)
		ft_printf("Something is missing in 'overwrite' func\n");
	x = 0;
	y = 0;
	while (x < bg->width && x < img->width)
	{
		y = 0;
		while (y < bg->heigth && y < img->heigth)
		{
			bg_addr = get_px_addr(bg, x, y);
			img_addr = get_px_addr(img, x + offx, y + offy);
			if (*img_addr)
				*(unsigned int *)bg_addr = *(unsigned int *)img_addr;
			y++;
		}
		x++;
	}
}

void	put_image_to_big_pic(t_image *bg, t_image *img, int offx, int offy)
{
	int	x;
	int	y;
	char	*bg_addr;
	char	*img_addr;

	if (!bg || !img || !bg->img || !img->img)
		ft_printf("Something is missing in 'put image to big pic' func\n");
	x = 0;
	y = 0;
	while (x < bg->width && x < img->width)
	{
		y = 0;
		while (y < bg->heigth && y < img->heigth)
		{
			bg_addr = get_px_addr(bg, x + offx, y + offy);
			img_addr = get_px_addr(img, x, y);
			if (*img_addr)
				*(unsigned int *)bg_addr = *(unsigned int *)img_addr;
			y++;
		}
		x++;
	}
}

t_image	*new_tile(t_screen *screen, int width, int heigth)
{
	t_image	*tile;
	t_image	pic;
	int		offx;
	int		offy;

	tile = malloc(sizeof(t_image));
	tile->img = mlx_new_image(screen->mlx, width, heigth);
	tile->heigth = heigth;
	tile->width = width;
	set_img_data(tile);
	pic.img = mlx_xpm_file_to_image(screen->mlx, "assets/Grass_Dirt_Tile.xpm", &pic.width, &pic.heigth);
	if (!pic.img)
		ft_printf("picture couldnt catched\n");
	set_img_data(&pic);
	offx = rand() % 32;
	offy = rand() % 32;
	overwrite(tile, &pic, 384 + offx, 0 + offy); //x : 384 - 416, y: 0 - 32
	return (tile);
}

t_image	*new_sprite(t_screen *screen, t_image *tile)
{
	t_image	*sprite;
	int		x;
	int		y;
	char	*tile_addr;
	char	*sprite_addr;

	sprite = malloc(sizeof(t_image));
	sprite->img = mlx_xpm_file_to_image(screen->mlx, "assets/AnimatedAutum.xpm", &sprite->width, &sprite->heigth);
	sprite->address = mlx_get_data_addr(sprite->img, &sprite->bits_p_px, &sprite->linelen, &sprite->endian);
	x = 0;
	y = 0;
	while (y < tile->width)
	{
		x = 0;
		while (x < tile->heigth)
		{
			tile_addr = get_px_addr(tile, x, y);
			sprite_addr = get_px_addr(sprite, x, y);
			if (*sprite_addr != 0)
				*(unsigned int *)tile_addr = *(unsigned int *)sprite_addr;
			x++;
		}
		y++;
	}
	return (tile);
}

void	put_images(t_screen *screen)
{
	t_image	*tile;
	t_image	*spirit;

	int i = 0;
	int j = 0;
	screen->big_picture = malloc(sizeof(t_image));
	screen->big_picture->img = mlx_new_image(screen->mlx, TILE_W * screen->map_w, TILE_H * screen->map_h);
	set_img_data(screen->big_picture);
	screen->big_picture->heigth = TILE_H * screen->map_h;
	screen->big_picture->width = TILE_W * screen->map_w;
	while (screen->map[i])
	{
		j = 0;
		while (screen->map[i][j])
		{
			tile = new_tile(screen, TILE_W, TILE_H);
			spirit = new_sprite(screen, tile);
			put_image_to_big_pic(screen->big_picture, tile, TILE_W * j, TILE_H * i);
			if (screen->map[i][j] == '1')
			{
				mlx_put_image_to_window(screen->mlx, screen->win, spirit->img, j * TILE_W, i * TILE_H);
			}
			j++;
		}
		i++;
	}
	sleep(1);
	mlx_put_image_to_window(screen->mlx, screen->win, screen->big_picture->img, 0, 0);
}
