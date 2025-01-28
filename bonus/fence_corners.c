/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fence_corners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:06:07 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/28 12:24:21 by huakbas          ###   ########.fr       */
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
	overwrite_asset(tile, asset);
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
	overwrite_asset(tile, asset);
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

void	put_counter(t_screen *screen)
{
	char	*moves;

	moves = ft_itoa(screen->count_moves);
	if (!moves)
		return ;
	mlx_string_put(screen->mlx, screen->win, 68, 24, 0xffffff, "Your moves: ");
	mlx_string_put(screen->mlx, screen->win, 136, 24, 0xffffff, moves);
	free(moves);
}
