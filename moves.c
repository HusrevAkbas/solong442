/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:48:10 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/16 17:23:21 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	move_up(t_screen *screen)
{
	t_image	*player;
	t_image	*this_img;
	t_image	*src_img;
	t_image	*dest_img;
	t_image	*asset;

	player = screen->player;
	if (screen->map[player->y - 1][player->x] == '1')
		return ;
	this_img = screen->images;
	asset = screen->assets[player->asset];
	while (this_img)
	{
		if (this_img->x == player->x && this_img->y == player->y)
			src_img = this_img ;
		if (this_img->x == player->x && this_img->y == player->y - 1)
			dest_img = this_img;
		this_img = this_img->next;
	}
	player->y--;
	overwrite(src_img, src_img->bg);
	overwrite(dest_img, dest_img->bg);
	put_tiles_to_big_pic(screen->big_picture, src_img);
	put_tiles_to_big_pic(screen->big_picture, dest_img);
	asset->frame = 2;
	asset->offy = asset->frame * asset->wid_per_frame;
	asset->offx = asset->frame * asset->wid_per_frame;
	dest_img->offx = 16;
	dest_img->offy = 16;
	overwrite_asset(dest_img, asset);
	dest_img->offx = 0;
	dest_img->offy = 0;
}
