/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husrevakbas <husrevakbas@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:18:32 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/24 17:00:32 by husrevakbas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	animate_tree(t_screen *screen, t_image *image)
{
	t_image	*asset;

	asset = screen->assets[TREE];
	overwrite_bg(image);
	image->frame++;
	asset->offx = (image->frame % 16) * asset->wid_per_frame;
	overwrite_asset(image, asset);
	put_tiles_to_big_pic(screen->big_picture, image);
}

void	animate_collectible(t_screen *screen, t_image *image)
{
	t_image	*asset;

	asset = screen->assets[COLLECTION];
	overwrite_bg(image);
	image->offx = 16;
	image->offy = 10;
	if (image->direction == 0)
	{
		image->offy += image->frame;
		image->frame += 2;
		if (image->frame >= 10)
			image->direction = 1;
	}
	else
	{
		image->offy += image->frame;
		image->frame -= 2;
		if (image->frame <= 0)
			image->direction = 0;
	}
	overwrite_asset(image, asset);
	image->offx = 0;
	image->offy = 0;
	put_tiles_to_big_pic(screen->big_picture, image);
}

void	move_player(t_screen *screen)
{
	t_player	*player;
	t_image		*asset;
	//t_image		*start;
	t_image		*dest;

	player = screen->player;
	asset = screen->assets[player->asset];
	//start = player->start;
	dest = player->dest;
	player->px_move -= 8;
	screen->big_picture->offx = player->x * TILE_SIZE + 15;
	screen->big_picture->offy = player->y * TILE_SIZE + 15;
	if (player->direction == 2)
		screen->big_picture->offy += player->px_move;
	if (player->direction == 0)
		screen->big_picture->offy -= player->px_move;
	if (player->direction == 1)
		screen->big_picture->offx -= player->px_move;
	if (player->direction == 3)
		screen->big_picture->offx += player->px_move;
	asset->offx = player->direction * asset->wid_per_frame;
	asset->offy = (player->frame % 4) * asset->wid_per_frame;
	player->frame++;
	overwrite_asset(screen->big_picture, asset);
	if (screen->count_collectible == 0 && screen->map[dest->y][dest->x] == 'E' && player->px_move == 0)
		clean_exit(screen);
}

int	animate(t_screen *screen)
{
	t_list	*list;
	t_image	*this_img;
	//t_image	*asset;
	static unsigned long	i = 0;

	if (i % 100 == 0)
	{
		list = screen->images;
		while (list)
		{
			this_img = list->content;
			//asset = screen->assets[this_img->asset];
			if (screen->count_collectible == 0 && screen->map[this_img->y][this_img->x] == 'E' && this_img->asset == GRASS)
				set_exit_point(screen, this_img, 0);
			if (screen->map[this_img->y][this_img->x] != '1')
			{
				overwrite_bg(this_img);
				put_tiles_to_big_pic(screen->big_picture, this_img);
			}
			if (this_img->asset == TREE)
				animate_tree(screen, this_img);
			else if (this_img->asset == COLLECTION)
				animate_collectible(screen, this_img);
			list = list->next;
		}
		if (screen->player->px_move)
			move_player(screen);
		else
		{
			screen->big_picture->offy = screen->player->y * TILE_SIZE + 15;
			screen->big_picture->offx = screen->player->x *TILE_SIZE + 15;
			overwrite_asset(screen->big_picture, screen->assets[screen->player->asset]);
		}
		mlx_put_image_to_window(screen->mlx, screen->win, screen->big_picture->img, 0, 0);
	}
	i++;
	return (i);
}
