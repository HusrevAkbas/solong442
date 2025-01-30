/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:00 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/30 11:21:09 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

t_bg	*new_bg(t_screen *screen, int width, int heigth)
{
	t_bg	*bg;
	t_image	*pic;

	bg = malloc(sizeof(t_bg));
	if (!bg)
		clean_exit(screen);
	ft_memset(bg, 0, sizeof(t_bg));
	bg->img = mlx_new_image(screen->mlx, width, heigth);
	if (!bg->img)
		clean_exit(screen);
	bg->heigth = heigth;
	bg->width = width;
	set_bg_addr(bg);
	pic = screen->assets[GRASS];
	pic->offx = rand() % 32 + 384;
	pic->offy = rand() % 32;
	overwrite_create_bg(bg, pic);
	return (bg);
}

t_image	*new_tile(t_screen *screen, int width, int heigth)
{
	t_image	*tile;

	tile = malloc(sizeof(t_image));
	if (!tile)
		clean_exit(screen);
	ft_memset(tile, 0, sizeof(t_image));
	tile->img = mlx_new_image(screen->mlx, width, heigth);
	if (!tile->img)
		clean_exit(screen);
	tile->heigth = heigth;
	tile->width = width;
	tile->offx = 0;
	tile->offy = 0;
	set_img_addr(tile);
	tile->bg = new_bg(screen, width, heigth);
	overwrite_bg(tile);
	tile->wid_per_frame = TILE_SIZE;
	return (tile);
}

void	create_tiles(t_screen *screen)
{
	t_image	*tile;
	int		i;
	int		j;

	i = 0;
	while (screen->map[i])
	{
		j = 0;
		while (screen->map[i][j])
		{
			tile = new_tile(screen, TILE_SIZE, TILE_SIZE);
			tile->x = j;
			tile->y = i;
			tile->asset = -1;
			tile->mlx = screen->mlx;
			set_tiles(screen, tile);
			if (!screen->images)
				screen->images = ft_lstnew(tile);
			else
				ft_lstadd_back(&screen->images, ft_lstnew(tile));
			put_tiles_to_big_pic(screen->big_picture, tile);
			j++;
		}
		i++;
	}
}

void	first_move_enemies(t_screen *screen)
{
	t_list		*list;
	t_player	*enemy;

	list = screen->enemies;
	while (list)
	{
		enemy = list->content;
		next_move_enemy(screen, enemy);
		list = list->next;
	}
}

void	put_images(t_screen *screen)
{
	screen->images = NULL;
	screen->big_picture = malloc(sizeof(t_image));
	if (!screen->big_picture)
		clean_exit(screen);
	ft_memset(screen->big_picture, 0, sizeof(t_image));
	screen->big_picture->img = mlx_new_image(screen->mlx,
			TILE_SIZE * screen->map_w, TILE_SIZE * screen->map_h);
	if (!screen->big_picture->img)
		clean_exit(screen);
	set_img_addr(screen->big_picture);
	screen->big_picture->heigth = TILE_SIZE * screen->map_h;
	screen->big_picture->width = TILE_SIZE * screen->map_w;
	screen->big_picture->mlx = screen->mlx;
	get_assets(screen);
	create_tiles(screen);
	first_move_enemies(screen);
	mlx_put_image_to_window(screen->mlx, screen->win,
		screen->big_picture->img, 0, 0);
}
