/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:48:10 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/27 11:39:51 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	next_move_enemy(t_screen *screen, t_player *enemy)
{
	if (enemy->direction == 2)
		move_down_enemy(screen, enemy);
	else if (enemy->direction == -1)
		move_left_enemy(screen, enemy);
	else if (enemy->direction == -2)
		move_up_enemy(screen, enemy);
	else if (enemy->direction == 1)
		move_right_enemy(screen, enemy);
}

void	move_up_enemy(t_screen *screen, t_player *enemy)
{
	t_list	*list;
	t_image	*image;

	if (screen->map[enemy->y - 1][enemy->x] == '1')
	{
		move_down_enemy(screen, enemy);
		return ;
	}
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
	if (enemy->dest->asset == COLLECTION)
	{
		move_down_enemy(screen, enemy);
		return ;
	}
	enemy->y--;
	enemy->direction = -2;
	enemy->px_move = 64;
}

void	move_down_enemy(t_screen *screen, t_player *enemy)
{
	t_list		*list;
	t_image		*image;

	if (screen->map[enemy->y + 1][enemy->x] == '1')
	{
		move_up_enemy(screen, enemy);
		return ;
	}
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
		move_up_enemy(screen, enemy);
		return ;
	}
	enemy->y++;
	enemy->direction = 2;
	enemy->px_move = 64;
}

void	move_right_enemy(t_screen *screen, t_player *enemy)
{
	t_list		*list;
	t_image		*image;

	if (screen->map[enemy->y][enemy->x + 1] == '1')
	{
		move_left_enemy(screen, enemy);
		return ;
	}
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
	if (enemy->dest->asset == COLLECTION)
	{
		move_left_enemy(screen, enemy);
		return ;
	}
	enemy->x++;
	enemy->direction = 1;
	enemy->px_move = 64;
}

void	move_left_enemy(t_screen *screen, t_player *enemy)
{
	t_list		*list;
	t_image		*image;

	if (screen->map[enemy->y][enemy->x - 1] == '1')
	{
		move_right_enemy(screen, enemy);
		return ;
	}
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
	if (enemy->dest->asset == COLLECTION)
	{
		move_right_enemy(screen, enemy);
		return ;
	}
	enemy->x--;
	enemy->direction = -1;
	enemy->px_move = 64;
}
