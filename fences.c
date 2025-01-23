/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fences.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:06:07 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/23 13:01:42 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	set_top_left_corner(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	asset->wid_per_frame = 32;
	overwrite_bg(tile);
	tile->offx = 32;
	tile->offy = 32;
	overwrite(tile, asset);
}

void	set_top_right_corner(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite_bg(tile);
	tile->offx = 0;
	tile->offy = 32;
	asset->offx = 64;
	asset->wid_per_frame = 32;
	overwrite(tile, asset);
	// tile->offx = 32;
	// tile->offy = 0;
	// tile->bg->offx = 32;
	// tile->bg->offy = 0;
}

void	set_bottom_left_corner(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite_bg(tile);
	tile->offx = 32;
	tile->offy = 0;
	asset->offx = 0;
	asset->offy = 64;
	asset->wid_per_frame = 32;
	overwrite_asset(tile, asset);
}

void	set_bottom_right_corner(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite_bg(tile);
	tile->offx = 0;
	tile->offy = 0;
	asset->offx = 64;
	asset->offy = 64;
	asset->wid_per_frame = 32;
	overwrite_asset(tile, asset);
}

void	set_left_border(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite_bg(tile);
	tile->offx = 32;
	tile->offy = 0;
	asset->offx = 96;
	asset->offy = 1;
	asset->wid_per_frame = 32;
	overwrite(tile, asset);
}

void	set_rigth_border(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite_bg(tile);
	tile->offx = 0;
	tile->offy = 0;
	asset->offx = 96;
	asset->offy = 1;
	asset->wid_per_frame = 32;
	overwrite(tile, asset);
}

void	set_top_border(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite_bg(tile);
	tile->offx = 0;
	tile->offy = 32;
	asset->offx = 23;
	asset->offy = 96;
	asset->wid_per_frame = 32;
	overwrite(tile, asset);
}

void	set_bottom_border(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite_bg(tile);
	tile->offx = 0;
	tile->offy = 0;
	asset->offx = 8;
	asset->offy = 96;
	asset->wid_per_frame = 32;
	overwrite(tile, asset);
}

void	set_tree(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = TREE;
	tile->frame = 0;
	asset = screen->assets[tile->asset];
	overwrite_bg(tile);
	tile->offx = 0;
	tile->offy = 2;
	asset->offx = 0;
	asset->offy = 0;
	asset->wid_per_frame = 64;
	overwrite(tile, asset);
}

void	set_player(t_screen *screen, t_image *tile)
{
	t_player	*player;
	t_image		*asset;

	player = malloc(sizeof(t_image));
	player->x = tile->x;
	player->y = tile->y;
	player->asset = PEACOCK_FL;
	player->frame = 0;
	asset = screen->assets[player->asset];
	asset->wid_per_frame = 36;
	player->direction = 2;
	asset->offx = asset->wid_per_frame * player->direction;
	asset->offy = 0;
	tile->offx = 14;
	tile->offy = 14;
	player->px_move = 0;
	screen->player = player;
	overwrite_asset(tile, asset);
}

void	set_collectible(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = COLLECTION;
	tile->frame = 0;
	asset = screen->assets[tile->asset];
	tile->offx = 16;
	tile->offy = 16;
	asset->offx = 0;
	asset->offy = 32;
	asset->wid_per_frame = 32;
	asset->wid_per_frame = 32;
	overwrite_asset(tile, asset);
}

void	set_exit_point(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = GRASS;
	asset = screen->assets[tile->asset];
	tile->offx = 16;
	tile->offy = 16;
	asset->offx = 0;
	asset->offy = 96;
	asset->wid_per_frame = 32;
	overwrite_asset(tile, asset);
	//put flowers
	asset = screen->assets[FLOWERS];
	asset->wid_per_frame = 12;
	asset->offx = 0 * asset->wid_per_frame;
	asset->offy = 2 * asset->wid_per_frame;
	tile->offx = 12;
	tile->offy = 0;
	overwrite_asset(tile, asset);
	tile->offy = 48;
	overwrite_asset(tile, asset);
	tile->offx = 36;
	overwrite_asset(tile, asset);
	tile->offy = 0;
	overwrite_asset(tile, asset);
	tile->offx = 0;
	tile->offy = 24;
	overwrite_asset(tile, asset);
	tile->offx = 48;
	overwrite_asset(tile, asset);
}

void	set_tiles(t_screen *screen, t_image *tile)
{
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
	else if (screen->map[tile->y][tile->x] == 'P')
		set_player(screen, tile);
	else if (screen->map[tile->y][tile->x] == 'C')
		set_collectible(screen, tile);
	else if (screen->map[tile->y][tile->x] == 'E')
		set_exit_point(screen, tile);
}
