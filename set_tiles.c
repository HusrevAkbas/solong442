/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:06:07 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/25 12:50:16 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	set_tree(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	if (!screen || ! tile)
		return ;
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

	if (!screen || ! tile)
		return ;
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
	player->px_move = 0;
	screen->player = player;
}

void	set_collectible(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	if (!screen || ! tile)
		return ;
	tile->asset = COLLECTION;
	tile->frame = 0;
	tile->direction = 0;
	asset = screen->assets[tile->asset];
	tile->offx = 16;
	tile->offy = 16;
	asset->offx = 0;
	asset->offy = 32;
	asset->wid_per_frame = 32;
	asset->wid_per_frame = 32;
	overwrite_asset(tile, asset);
}

void	set_tiles_more(t_screen *screen, t_image *tile)
{
	if (!screen || ! tile)
		return ;
	if (screen->map[tile->y][tile->x] == '1')
		set_tree(screen, tile);
	else if (screen->map[tile->y][tile->x] == 'P')
		set_player(screen, tile);
	else if (screen->map[tile->y][tile->x] == 'C')
		set_collectible(screen, tile);
	else if (screen->map[tile->y][tile->x] == 'E')
		set_exit_point(screen, tile, 5);
}

void	set_tiles(t_screen *screen, t_image *tile)
{
	if (!screen || ! tile)
		return ;
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
	else
		set_tiles_more(screen, tile);
}
