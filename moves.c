/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husrevakbas <husrevakbas@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:48:10 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/24 17:00:32 by husrevakbas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	set_commons(t_screen *screen, t_player *player)
{
	player->frame = 1;
	player->px_move = 64;
	screen->count_moves++;
	ft_printf("You moved %d times\n", screen->count_moves);
}

void	move_up(t_screen *screen)
{
	t_player	*player;
	t_list		*list;
	t_image		*image;

	player = screen->player;
	if (screen->map[player->y - 1][player->x] == '1')
		return ;
	list = screen->images;
	while (list)
	{
		image = list->content;
		if (image->x == player->x && image->y == player->y)
			player->start = image;
		if (image->x == player->x && image->y == player->y - 1)
			player->dest = image;
		list = list->next;
	}
	if (player->dest->asset == COLLECTION)
	{
		player->dest->asset = -1;
		screen->count_collectible--;
	}
	player->y--;
	player->direction = 2;
	set_commons(screen, player);
}

void	move_down(t_screen *screen)
{
	t_player	*player;
	t_list		*list;
	t_image		*image;

	player = screen->player;
	if (screen->map[player->y + 1][player->x] == '1')
		return ;
	list = screen->images;
	while (list)
	{
		image = list->content;
		if (image->x == player->x && image->y == player->y)
			player->start = image;
		if (image->x == player->x && image->y == player->y + 1)
			player->dest = image;
		list = list->next;
	}
	if (player->dest->asset == COLLECTION)
	{
		player->dest->asset = -1;
		screen->count_collectible--;
	}
	player->y++;
	player->direction = 0;
	set_commons(screen, player);
}

void	move_right(t_screen *screen)
{
	t_player	*player;
	t_list		*list;
	t_image		*image;

	player = screen->player;
	if (screen->map[player->y][player->x + 1] == '1')
		return ;
	list = screen->images;
	while (list)
	{
		image = list->content;
		if (image->x == player->x && image->y == player->y)
			player->start = image;
		if (image->x == player->x + 1 && image->y == player->y)
			player->dest = image;
		list = list->next;
	}
	if (player->dest->asset == COLLECTION)
	{
		player->dest->asset = -1;
		screen->count_collectible--;
	}
	player->x++;
	player->direction = 1;
	set_commons(screen, player);
}

void	move_left(t_screen *screen)
{
	t_player	*player;
	t_list		*list;
	t_image		*image;

	player = screen->player;
	if (screen->map[player->y][player->x - 1] == '1')
		return ;
	list = screen->images;
	while (list)
	{
		image = list->content;
		if (image->x == player->x && image->y == player->y)
			player->start = image;
		if (image->x == player->x - 1 && image->y == player->y)
			player->dest = image;
		list = list->next;
	}
	if (player->dest->asset == COLLECTION)
	{
		player->dest->asset = -1;
		screen->count_collectible--;
	}
	player->x--;
	player->direction = 3;
	set_commons(screen, player);
}
