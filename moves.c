/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:48:10 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/16 20:35:29 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	move_up(t_screen *screen)
{
	t_image	*player;
	t_image	*list;
	t_image	*start;
	t_image	*dest;

	player = screen->player;
	list = screen->images;
	while (list)
	{
		if (list->x == player->x && list->y == player->y)
			start = list;
		if (list->x == player->x && list->y == player->y + 1)
			dest = list;
		list = list->next;
	}
	player = screen->player;
	if (screen->map[player->y - 1][player->x] == '1')
		return ;
	player->y--;
	player->frame = 1;
	player->player_direction = 2;
	player->px_move = 64;
}
