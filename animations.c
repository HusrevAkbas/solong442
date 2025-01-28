/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:18:32 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/28 12:01:33 by huakbas          ###   ########.fr       */
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

t_list	*set_next_frame(t_screen *screen, t_list *list)
{
	t_image	*this_img;

	this_img = list->content;
	if (screen->count_collectible == 0
		&& screen->map[this_img->y][this_img->x] == 'E'
		&& this_img->asset == GRASS)
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
	return (list->next);
}

int	animate(t_screen *screen)
{
	t_list	*list;

	list = screen->images;
	while (list)
		list = set_next_frame(screen, list);
	if (screen->player->px_move)
		move_player(screen);
	else
	{
		if (check_enemy_touch(screen))
			clean_exit(screen);
		screen->big_picture->offy = screen->player->y * TILE_SIZE + 15;
		screen->big_picture->offx = screen->player->x * TILE_SIZE + 15;
		overwrite_asset(screen->big_picture,
			screen->assets[screen->player->asset]);
	}
	move_enemy(screen);
	mlx_put_image_to_window(screen->mlx, screen->win,
		screen->big_picture->img, 0, 0);
	put_counter(screen);
	usleep(80000);
	return (0);
}
