/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:18:32 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/16 20:34:53 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	animate_tree(t_screen *screen, t_image *image)
{
	t_image	*asset;

	asset = screen->assets[TREE];
	overwrite(image, image->bg);
	image->frame++;
	asset->offx = (image->frame % 16) * asset->wid_per_frame;
	overwrite_asset(image, asset);
	put_tiles_to_big_pic(screen->big_picture, image);
}

void	move_player(t_screen *screen)
{
	t_image	*player;
	t_image	*asset;
	t_image	*list;
	t_image	*start;
	t_image	*dest;

	player = screen->player;
	asset = screen->assets[player->asset];
	list = screen->images;
	while (list)
	{
		if (list->x == player->x && list->y == player->y)
			start = list;
		if (list->x == player->x && list->y == player->y + 1)
			dest = list;
		list = list->next;
	}
	player->px_move -= 4;
	overwrite(start, start->bg);
	overwrite(dest, dest->bg);
	put_tiles_to_big_pic(screen->big_picture, start);
	put_tiles_to_big_pic(screen->big_picture, dest);
	screen->big_picture->offx = player->x * TILE_SIZE + 15;
	screen->big_picture->offy = player->y * TILE_SIZE + 15 + player->px_move;
	asset->offx = player->player_direction * asset->wid_per_frame;
	asset->offy = (player->frame % 4) * asset->wid_per_frame;
	player->frame++;
	overwrite_asset(screen->big_picture, asset);
	screen->big_picture->offx = 0;
	screen->big_picture->offy = 0;
}

int	animate(t_screen *screen)
{
	t_image	*image_list;
	t_image	*this_img;
	t_image	*asset;
	static unsigned int		i = 0;

	if (i % 12000 == 0)
	{
		image_list = screen->images;
		this_img = image_list;
		while (this_img)
		{
			asset = screen->assets[this_img->asset];
			if (this_img->asset == TREE)
				animate_tree(screen, this_img);
			this_img = this_img->next;
		}
		if (screen->player->px_move)
			move_player(screen);
		mlx_put_image_to_window(screen->mlx, screen->win, screen->big_picture->img, 0, 0);
	}
	i++;
	return (i);
}
