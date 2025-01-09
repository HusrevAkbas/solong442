/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:00 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/09 15:18:13 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

char	*get_px_addr(t_image *img, int x, int y)
{
	return (img->address + (y * img->linelen + x * (img->bits_p_px / 8)));
}

void	set_img_addr(t_image *img)
{
	img->address = mlx_get_data_addr(img->img, &img->bits_p_px,
				&img->linelen, &img->endian);
}

void	get_assets(t_screen *screen)
{
	t_image	*img;
	char	*pathmap[9];
	int		i;

	pathmap[GRASS] = GRASS_PATH;
	pathmap[TREE] = TREE_PATH;
	pathmap[FENCE] = FENCE_PATH;
	pathmap[PEACOCK_FL] = PEACOCK_OP_PATH;
	pathmap[BUTTERFLY] = BUTTERFLY_PATH;
	pathmap[EYEMONSTER] = EYEMONSTER_PATH;
	pathmap[COLLECTION] = COLLECTION_PATH;
	pathmap[PEACOCK_OP] = PEACOCK_OP_PATH;
	pathmap[8] = NULL;
	i = 0;
	while (i < 8)
	{
		img = malloc(sizeof(t_image));
		img->img = mlx_xpm_file_to_image(screen->mlx, pathmap[i], &img->width, &img->heigth);
		if (!img->img)
			clean_exit(screen);
		set_img_addr(img);
		screen->assets[i] = img;
		i++;
	}
}

void	overwrite(t_image *bg, t_image *img)
{
	int	x;
	int	y;
	char	*bg_addr;
	char	*img_addr;

	if (!bg || !img || !bg->img || !img->img)
		ft_printf("Something is missing in 'overwrite' func\n");
	x = 0;
	y = 0;
	while (x + bg->offx < bg->width && x + img->offx < img->width)
	{
		y = 0;
		while (y + bg->offy < bg->heigth && y + img->offy < img->heigth)
		{
			bg_addr = get_px_addr(bg, x + bg->offx, y + bg->offy);
			img_addr = get_px_addr(img, x + img->offx, y + img->offy);
			if (*img_addr)
				*(unsigned int *)bg_addr = *(unsigned int *)img_addr;
			y++;
		}
		x++;
	}
}

void	put_image_to_big_pic(t_image *bg, t_image *img)
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
			bg_addr = get_px_addr(bg, x + (TILE_SIZE * img->x), y + (TILE_SIZE * img->y));
			img_addr = get_px_addr(img, x, y);
			if (*img_addr)
				*(unsigned int *)bg_addr = *(unsigned int *)img_addr;
			y++;
		}
		x++;
	}
}

t_image	*new_bg(t_screen *screen, int width, int heigth)
{
	t_image	*tile;
	t_image	*pic;

	tile = malloc(sizeof(t_image));
	tile->img = mlx_new_image(screen->mlx, width, heigth);
	tile->heigth = heigth;
	tile->width = width;
	set_img_addr(tile);
	pic = screen->assets[GRASS];
	pic->offx = rand() % 32 + 384;
	pic->offy = rand() % 32;
	overwrite(tile, pic); //x : 384 - 416, y: 0 - 32
	return (tile);
}

t_image	*new_tile(t_screen *screen, int width, int heigth)
{
	t_image	*tile;

	tile = malloc(sizeof(t_image));
	tile->img = mlx_new_image(screen->mlx, width, heigth);
	tile->heigth = heigth;
	tile->width = width;
	tile->offx = 0;
	tile->offy = 0;
	set_img_addr(tile);
	tile->bg = new_bg(screen, width, heigth);
	overwrite(tile, tile->bg);
	return (tile);
}

void	new_sprite(t_screen *screen, t_image *tile)
{
	t_image	*sprite;
	int		x;
	int		y;
	char	*tile_addr;
	char	*sprite_addr;

	sprite = screen->assets[tile->asset];
	x = 0;
	y = 0;
	while (y + tile->offy < tile->heigth)
	{
		x = 0;
		while (x + tile->offx < tile->width)
		{
			tile_addr = get_px_addr(tile, x, y);
			sprite_addr = get_px_addr(sprite, x, y);
			if (*sprite_addr != 0)
				*(unsigned int *)tile_addr = *(unsigned int *)sprite_addr;
			x++;
		}
		y++;
	}
}

void	put_images(t_screen *screen)
{
	t_image	*tile;

	screen->big_picture = malloc(sizeof(t_image));
	screen->big_picture->img = mlx_new_image(screen->mlx, TILE_SIZE * screen->map_w, TILE_SIZE * screen->map_h);
	if (!screen->big_picture->img)
		ft_printf("I can't see the big picture");
	set_img_addr(screen->big_picture);
	screen->big_picture->heigth = TILE_SIZE * screen->map_h;
	screen->big_picture->width = TILE_SIZE * screen->map_w;
	get_assets(screen);
	int i = 0;
	int j = 0;
	while (screen->map[i])
	{
		j = 0;
		while (screen->map[i][j])
		{
			tile = new_tile(screen, TILE_SIZE, TILE_SIZE);
			tile->x = j;
			tile->y = i;
			tile->asset = TREE;
			overwrite(tile, screen->assets[tile->asset]);
			set_borders(screen, tile);
			put_image_to_big_pic(screen->big_picture, tile);
	//mlx_put_image_to_window(screen->mlx, screen->win, tile->img, j * TILE_SIZE, i * TILE_SIZE);
	//sleep(1);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(screen->mlx, screen->win, screen->big_picture->img, 0, 0);
}
