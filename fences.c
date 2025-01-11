/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fences.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husrevakbas <husrevakbas@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:06:07 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/12 00:19:28 by husrevakbas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	set_top_left_corner(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite(tile, tile->bg);
	tile->offx = 32;
	tile->offy = 32;
	overwrite(tile, asset);
}

void	set_top_right_corner(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite(tile, tile->bg);
	tile->offx = 0;
	tile->offy = 32;
	asset->offx = 64;
	overwrite(tile, asset);
	tile->offx = 32;
	tile->offy = 0;
	tile->bg->offx = 32;
	tile->bg->offy = 0;
	overwrite(tile, tile->bg);
}

void	set_bottom_left_corner(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite(tile, tile->bg);
	tile->offx = 32;
	tile->offy = 0;
	asset->offx = 0;
	asset->offy = 64;
	overwrite(tile, asset);
	tile->offx = 32;
	tile->offy = 32;
	tile->bg->offx = 32;
	tile->bg->offy = 32;
	overwrite(tile, tile->bg);
}

void	set_bottom_right_corner(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite(tile, tile->bg);
	tile->offx = 0;
	tile->offy = 0;
	asset->offx = 64;
	asset->offy = 64;
	overwrite(tile, asset);
	tile->offx = 32;
	tile->offy = 0;
	tile->bg->offx = 32;
	tile->bg->offy = 0;
	overwrite(tile, tile->bg);
	tile->offx = 0;
	tile->offy = 32;
	tile->bg->offx = 0;
	tile->bg->offy = 32;
	overwrite(tile, tile->bg);
}

void	set_left_border(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite(tile, tile->bg);
	tile->offx = 32;
	tile->offy = 0;
	asset->offx = 96;
	asset->offy = 1;
	overwrite(tile, asset);
}

void	set_rigth_border(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite(tile, tile->bg);
	tile->offx = 0;
	tile->offy = 0;
	asset->offx = 96;
	asset->offy = 1;
	overwrite(tile, asset);
}

void	set_top_border(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite(tile, tile->bg);
	tile->offx = 0;
	tile->offy = 32;
	asset->offx = 23;
	asset->offy = 96;
	overwrite(tile, asset);
}

void	set_bottom_border(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite(tile, tile->bg);
	tile->offx = 0;
	tile->offy = 0;
	asset->offx = 8;
	asset->offy = 96;
	overwrite(tile, asset);
}

void	set_tree(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = TREE;
	asset = screen->assets[tile->asset];
	overwrite(tile, tile->bg);
	tile->offx = 0;
	tile->offy = 0;
	asset->offx = 0;
	asset->offy = 0;
	overwrite(tile, asset);
}

void	set_tiles(t_screen *screen, t_image *tile)
{
ft_printf("x %i y %i in map %c\n", tile->x, tile->y, screen->map[tile->y][tile->x]);
	if (tile->x == 0 && tile->y == 0)
		set_top_left_corner(screen, tile);
	else if (tile->x == screen->map_w - 1 && tile->y == 0)
		set_top_right_corner(screen, tile);
	else if (tile->x == 0 && tile->y == screen->map_h - 1)
		set_bottom_left_corner(screen, tile);
	else if (tile->x == screen->map_w - 1 && tile->y == screen->map_h - 1)
		set_bottom_right_corner(screen, tile);
	else if (tile->x == 0)
		set_left_border(screen, tile);
	else if (tile->x == screen->map_w - 1)
		set_rigth_border(screen, tile);
	else if (tile->y == 0)
		set_top_border(screen, tile);
	else if (tile->y == screen->map_h - 1)
		set_bottom_border(screen, tile);
	else if (screen->map[tile->y][tile->x] == '1')
		set_tree(screen, tile);
	else
		ft_printf("somethin else\n");
}
