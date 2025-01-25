/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fence_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:06:07 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/25 15:15:25 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

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
