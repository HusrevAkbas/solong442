/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husrevakbas <husrevakbas@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:48:10 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/26 23:41:04 by husrevakbas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	move_up_enemy(t_screen *screen, t_player *enemy)
{
	t_list	*list;
	t_image	*image;

	if (screen->map[enemy->y - 1][enemy->x] == '1'
		|| enemy->dest->asset == COLLECTION
		|| screen->map[enemy->y - 1][enemy->x] == 'E')
		return ; //switch direction
	list = screen->images;
	while (list)
	{
		image = list->content;
		if (image->x == enemy->x && image->y == enemy->y)
			enemy->start = image;
		if (image->x == enemy->x && image->y == enemy->y - 1)
			enemy->dest = image;
		list = list->next;
	}
	enemy->y--;
	enemy->direction = -2;
	enemy->frame = 1;
	enemy->px_move = 64;
}

void	move_down_enemy(t_screen *screen, t_player *enemy)
{
	t_list		*list;
	t_image		*image;

	if (screen->map[enemy->y + 1][enemy->x] == '1'
		|| enemy->dest->asset == COLLECTION
		|| screen->map[enemy->y - 1][enemy->x] == 'E')
		return ;
	list = screen->images;
	while (list)
	{
		image = list->content;
		if (image->x == enemy->x && image->y == enemy->y)
			enemy->start = image;
		if (image->x == enemy->x && image->y == enemy->y + 1)
			enemy->dest = image;
		list = list->next;
	}
	if (enemy->dest->asset == COLLECTION)
	{
		enemy->dest->asset = -1;
		screen->count_collectible--;
	}
	enemy->y++;
	enemy->direction = 2;
	enemy->frame = 1;
	enemy->px_move = 64;
}

void	move_right_enemy(t_screen *screen, t_player *enemy)
{
	t_list		*list;
	t_image		*image;

	if (screen->map[enemy->y][enemy->x + 1] == '1'
		|| enemy->dest->asset == COLLECTION
		|| screen->map[enemy->y - 1][enemy->x] == 'E')
		return ;
	list = screen->images;
	while (list)
	{
		image = list->content;
		if (image->x == enemy->x && image->y == enemy->y)
			enemy->start = image;
		if (image->x == enemy->x + 1 && image->y == enemy->y)
			enemy->dest = image;
		list = list->next;
	}
	enemy->x++;
	enemy->direction = 1;
	enemy->frame = 1;
	enemy->px_move = 64;
}

void	move_left_enemy(t_screen *screen, t_player *enemy)
{
	t_list		*list;
	t_image		*image;

	if (screen->map[enemy->y][enemy->x - 1] == '1'
		|| enemy->dest->asset == COLLECTION
		|| screen->map[enemy->y - 1][enemy->x] == 'E')
		return ;
	list = screen->images;
	while (list)
	{
		image = list->content;
		if (image->x == enemy->x && image->y == enemy->y)
			enemy->start = image;
		if (image->x == enemy->x - 1 && image->y == enemy->y)
			enemy->dest = image;
		list = list->next;
	}
	enemy->x--;
	enemy->direction = -1;
	enemy->frame = 1;
	enemy->px_move = 64;
}
