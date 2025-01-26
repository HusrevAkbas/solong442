/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husrevakbas <husrevakbas@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:18:32 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/26 19:12:03 by husrevakbas      ###   ########.fr       */
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
	t_image		*asset;

	asset = screen->assets[screen->player->asset];
	screen->player->px_move -= 8;
	screen->big_picture->offx = screen->player->x * TILE_SIZE + 15;
	screen->big_picture->offy = screen->player->y * TILE_SIZE + 15;
	if (screen->player->direction == 2)
		screen->big_picture->offy += screen->player->px_move;
	if (screen->player->direction == 0)
		screen->big_picture->offy -= screen->player->px_move;
	if (screen->player->direction == 1)
		screen->big_picture->offx -= screen->player->px_move;
	if (screen->player->direction == 3)
		screen->big_picture->offx += screen->player->px_move;
	asset->offx = screen->player->direction * asset->wid_per_frame;
	asset->offy = (screen->player->frame % 4) * asset->wid_per_frame;
	screen->player->frame++;
	overwrite_asset(screen->big_picture, asset);
	if (screen->count_collectible == 0
		&& screen->map[screen->player->dest->y][screen->player->dest->x] == 'E'
		&& screen->player->px_move == 0)
	{
		ft_printf("You won !");
		clean_exit(screen);
	}
}

void	move_enemy(t_screen *screen)
{
	t_image		*asset;
	t_list		*node;
	t_player	*enemy;

	node = screen->enemies;
	enemy = node->content;

	asset = screen->assets[enemy->asset];
	//enemy->px_move -= 8;
	screen->big_picture->offx = enemy->x * TILE_SIZE;
	screen->big_picture->offy = enemy->y * TILE_SIZE;
	if (enemy->direction == 0)
		screen->big_picture->offy -= enemy->px_move;
	if (enemy->direction == 1)
		screen->big_picture->offx -= enemy->px_move;
	if (enemy->direction == 2)
		screen->big_picture->offy += enemy->px_move;
	if (enemy->direction == 3)
		screen->big_picture->offx += enemy->px_move;
	asset->offx = enemy->direction * asset->wid_per_frame;
	asset->offy = (enemy->frame % 4) * asset->wid_per_frame;
	enemy->frame++;
	overwrite_asset(screen->big_picture, asset);
	// if (screen->map[enemy->dest->y][enemy->dest->x] == 'E'
	// 	&& enemy->px_move == 0)
	// {
	// 	ft_printf("You lost !");
	// 	clean_exit(screen);
	// }
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
