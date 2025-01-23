/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:48:10 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/23 15:10:22 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	move_up(t_screen *screen)
{
	t_player	*player;
	t_image		*list;

	player = screen->player;
	if (screen->map[player->y - 1][player->x] == '1')
		return ;
	list = screen->images;
	while (list)
	{
		if (list->x == player->x && list->y == player->y)
			player->player_start = list;
		if (list->x == player->x && list->y == player->y - 1)
			player->player_dest = list;
		list = list->next;
	}
	if (player->player_dest->asset == COLLECTION)
	{
		player->player_dest->asset = -1;
		screen->count_collectible--;
	}
	player = screen->player;
	player->y--;
	player->frame = 1;
	player->direction = 2;
	player->px_move = 64;
	screen->count_moves++;
	ft_printf("You moved: %d\n",screen->count_moves);
}

void	move_down(t_screen *screen)
{
	t_player	*player;
	t_image		*list;

	player = screen->player;
	if (screen->map[player->y + 1][player->x] == '1')
		return ;
	list = screen->images;
	while (list)
	{
		if (list->x == player->x && list->y == player->y)
			player->player_start = list;
		if (list->x == player->x && list->y == player->y + 1)
			player->player_dest = list;
		list = list->next;
	}
	if (player->player_dest->asset == COLLECTION)
	{
		player->player_dest->asset = -1;
		screen->count_collectible--;
	}
	player->y++;
	player->frame = 1;
	player->direction = 0;
	player->px_move = 64;
	screen->count_moves++;
	ft_printf("You moved: %d\n",screen->count_moves);
}

void	move_right(t_screen *screen)
{
	t_player	*player;
	t_image		*list;

	player = screen->player;
	if (screen->map[player->y][player->x + 1] == '1')
		return ;
	list = screen->images;
	while (list)
	{
		if (list->x == player->x && list->y == player->y)
			player->player_start = list;
		if (list->x == player->x + 1 && list->y == player->y)
			player->player_dest = list;
		list = list->next;
	}
	if (player->player_dest->asset == COLLECTION)
	{
		player->player_dest->asset = -1;
		screen->count_collectible--;
	}
	player = screen->player;
	player->x++;
	player->frame = 1;
	player->direction = 1;
	player->px_move = 64;
	screen->count_moves++;
	ft_printf("You moved: %dn",screen->count_moves);
}

void	move_left(t_screen *screen)
{
	t_player	*player;
	t_image		*list;

	player = screen->player;
	if (screen->map[player->y][player->x - 1] == '1')
		return ;
	list = screen->images;
	while (list)
	{
		if (list->x == player->x && list->y == player->y)
			player->player_start = list;
		if (list->x == player->x - 1 && list->y == player->y)
			player->player_dest = list;
		list = list->next;
	}
	if (player->player_dest->asset == COLLECTION)
	{
		player->player_dest->asset = -1;
		screen->count_collectible--;
	}
	player = screen->player;
	player->x--;
	player->frame = 1;
	player->direction = 3;
	player->px_move = 64;
	screen->count_moves++;
	ft_printf("You moved: %d\n",screen->count_moves);
}
