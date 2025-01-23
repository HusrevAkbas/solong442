/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:00 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/23 17:15:09 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

char	*get_px_addr(t_image *img, int x, int y)
{
	return (img->address + (y * img->linelen + x * (img->bits_p_px / 8)));
}

char	*get_px_addr_bg(t_bg *bg, int x, int y)
{
	return (bg->address + (y * bg->linelen + x * (bg->bits_p_px / 8)));
}

void	set_img_addr(t_image *img)
{
	img->address = mlx_get_data_addr(img->img, &img->bits_p_px,
				&img->linelen, &img->endian);
}

void	set_bg_addr(t_bg *bg)
{
	bg->address = mlx_get_data_addr(bg->img, &bg->bits_p_px,
				&bg->linelen, &bg->endian);
}

void	set_image_attributes(t_image *img)
{
	img->img = NULL;
	img->bg = NULL;
	img->address = NULL;
	img->asset = 0;
	img->bits_p_px = 0;
	img->endian = 0;
	img->linelen = 0;
	img->frame = 0;
	img->heigth = 0;
	img->width = 0;
	img->wid_per_frame = 0;
	img->offx = 0;
	img->offy = 0;
	img->x = 0;
	img->y = 0;
	// img->next = NULL;
}

void	set_player_attributes(t_player *player)
{
	player->px_move = 0;
	player->direction = 0;
	player->player_dest = NULL;
	player->player_start = NULL;
	player->next = NULL;
	player->asset = 0;
	player->frame = 0;
	player->heigth = 0;
	player->width = 0;
	player->offx = 0;
	player->offy = 0;
	player->x = 0;
	player->y = 0;
	player->wid_per_frame = 0;
	player->next = NULL;
}

void	set_bg_attributes(t_bg *bg)
{
	bg->address = NULL;
	bg->img = NULL;
	bg->bits_p_px = 0;
	bg->endian = 0;
	bg->heigth = 0;
	bg->linelen = 0;
	bg->offx = 0;
	bg->offy = 0;
	bg->width = 0;
}

void	get_assets(t_screen *screen)
{
	t_image	*img;
	char	*pathmap[10];
	int		i;

	pathmap[GRASS] = GRASS_PATH;
	pathmap[TREE] = TREE_PATH;
	pathmap[FENCE] = FENCE_PATH;
	pathmap[PEACOCK_FL] = PEACOCK_FL_PATH;
	pathmap[BUTTERFLY] = BUTTERFLY_PATH;
	pathmap[EYEMONSTER] = EYEMONSTER_PATH;
	pathmap[COLLECTION] = COLLECTION_PATH;
	pathmap[PEACOCK_OP] = PEACOCK_OP_PATH;
	pathmap[FLOWERS] = FLOWERS_PATH;
	pathmap[9] = NULL;
	i = 0;
	while (i < 9)
	{
		img = malloc(sizeof(t_image));
		if (!img)
			ft_printf("malloc fail in get assets");
		set_image_attributes(img);
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
	x = 1;
	while (x + bg->offx < bg->width && x + img->offx < img->width)
	{
		y = 1;
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

void	overwrite_create_bg(t_bg *bg, t_image *img)
{
	int	x;
	int	y;
	char	*bg_addr;
	char	*img_addr;

	if (!bg || !img || !bg->img || !img->img)
		ft_printf("Something is missing in 'overwrite create bg' func\n");
	x = 1;
	while (x + bg->offx < bg->width && x + img->offx < img->width)
	{
		y = 1;
		while (y + bg->offy < bg->heigth && y + img->offy < img->heigth)
		{
			bg_addr = get_px_addr_bg(bg, x + bg->offx, y + bg->offy);
			img_addr = get_px_addr(img, x + img->offx, y + img->offy);
			if (*img_addr)
				*(unsigned int *)bg_addr = *(unsigned int *)img_addr;
			y++;
		}
		x++;
	}
}

void	overwrite_bg(t_image *img)
{
	int	x;
	int	y;
	char	*bg_addr;
	char	*img_addr;

	if (!img || !img->bg || !img->img)
		ft_printf("Something is missing in 'overwrite' func\n");
	x = 0;
	while (x + img->bg->offx < img->bg->width && x + img->offx < img->width)
	{
		y = 0;
		while (y + img->bg->offy < img->bg->heigth && y + img->offy < img->heigth)
		{
			bg_addr = get_px_addr_bg(img->bg, x + img->bg->offx, y + img->bg->offy);
			img_addr = get_px_addr(img, x + img->offx, y + img->offy);
			if (*bg_addr)
				*(unsigned int *)img_addr = *(unsigned int *)bg_addr;
			y++;
		}
		x++;
	}
}

void	overwrite_asset(t_image *bg, t_image *asset)
{
	int		x;
	int		y;
	char	*bg_addr;
	char	*img_addr;

	if (!bg || !asset || !bg->img || !asset->img)
		ft_printf("Something is missing in 'overwrite_asset' func\n");
	x = 0;
	y = 0;
	while (x + bg->offx < bg->width && x + asset->offx < asset->width && x < asset->wid_per_frame)
	{
		y = 0;
		while (y + bg->offy < bg->heigth && y + asset->offy < asset->heigth && y < asset->wid_per_frame)
		{
			bg_addr = get_px_addr(bg, x + bg->offx, y + bg->offy);
			img_addr = get_px_addr(asset, x + asset->offx, y + asset->offy);
			if (*img_addr)
				*(unsigned int *)bg_addr = *(unsigned int *)img_addr;
			y++;
		}
		x++;
	}
}

void	put_tiles_to_big_pic(t_image *big_pic, t_image *img)
{
	int	x;
	int	y;
	char	*bg_addr;
	char	*img_addr;

	if (!big_pic || !img || !big_pic->img || !img->img)
		ft_printf("Something is missing in 'put image to big pic' func\n");
	x = 0;
	y = 0;
	while (x < big_pic->width && x < img->width && x < img->wid_per_frame)
	{
		y = 0;
		while (y < big_pic->heigth && y < img->heigth && y < img->wid_per_frame)
		{
			bg_addr = get_px_addr(big_pic, x + (TILE_SIZE * img->x), y + (TILE_SIZE * img->y));
			img_addr = get_px_addr(img, x, y);
			if (*img_addr)
				*(unsigned int *)bg_addr = *(unsigned int *)img_addr;
			y++;
		}
		x++;
	}
}

t_bg	*new_bg(t_screen *screen, int width, int heigth)
{
	t_bg	*bg;
	t_image	*pic;

	bg = malloc(sizeof(t_bg));
	if (!bg)
		ft_printf("malloc fail in 'new bg'");
	set_bg_attributes(bg);
	bg->img = mlx_new_image(screen->mlx, width, heigth);
	if (!bg->img)
		ft_printf("malloc fail in 'new bg' bg img");
	bg->heigth = heigth;
	bg->width = width;
	set_bg_addr(bg);
	pic = screen->assets[GRASS];
	pic->offx = rand() % 32 + 384;
	pic->offy = rand() % 32;
	overwrite_create_bg(bg, pic); //x : 384 - 416, y: 0 - 32
	return (bg);
}

t_image	*new_tile(t_screen *screen, int width, int heigth)
{
	t_image	*tile;

	tile = malloc(sizeof(t_image));
	if (!tile)
		ft_printf("malloc fail in new tile");
	set_image_attributes(tile);
	tile->img = mlx_new_image(screen->mlx, width, heigth);
	if (!tile->img)
		ft_printf("malloc fail in new tile tile img");
	tile->heigth = heigth;
	tile->width = width;
	tile->offx = 0;
	tile->offy = 0;
	set_img_addr(tile);
	tile->bg = new_bg(screen, width, heigth);
	overwrite_bg(tile);
	tile->wid_per_frame = TILE_SIZE;
	// tile->next = NULL;
	return (tile);
}

void	put_images(t_screen *screen)
{
	t_image	*tile;
	t_image	*current;

	screen->images = NULL;
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
			tile->asset = -1;
			set_tiles(screen, tile);
			if (!screen->images)
				screen->images = ft_lstnew(tile);
			else
				ft_lstadd_back(&screen->images, ft_lstnew(tile));
			current = tile;
			put_tiles_to_big_pic(screen->big_picture, tile);
	//mlx_put_image_to_window(screen->mlx, screen->win, tile->img, j * TILE_SIZE, i * TILE_SIZE);
	//sleep(1);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(screen->mlx, screen->win, screen->big_picture->img, 0, 0);
}
