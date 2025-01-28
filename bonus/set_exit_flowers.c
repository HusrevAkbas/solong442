/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_flowers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:06:07 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/25 16:16:38 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	put_flowers(t_screen *screen, t_image *tile, int growth)
{
	t_image	*asset;

	asset = screen->assets[FLOWERS];
	asset->wid_per_frame = 12;
	asset->offx = 0 * asset->wid_per_frame;
	asset->offy = growth * asset->wid_per_frame;
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
	tile->offy = 48;
}

void	set_exit_point(t_screen *screen, t_image *tile, int growth)
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
	put_flowers(screen, tile, growth);
}
