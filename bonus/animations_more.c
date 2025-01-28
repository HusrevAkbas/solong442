/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:18:32 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/28 12:05:12 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	check_enemy_touch(t_screen *screen)
{
	t_list		*list;
	t_player	*enemy;

	list = screen->enemies;
	while (list)
	{
		enemy = list->content;
		if ((screen->player->x == enemy->dest->x
				&& screen->player->y == enemy->dest->y
				&& enemy->px_move <= 40)
			|| (enemy->start && screen->player->x == enemy->start->x
				&& screen->player->y == enemy->start->y
				&& enemy->px_move > 40))
		{
			ft_printf("Game over. You lost!\n");
			return (1);
		}
		list = list->next;
	}
	return (0);
}

int	check_win(t_screen *screen)
{
	if (screen->count_collectible == 0 && screen->player->px_move == 0
		&& screen->map[screen->player->dest->y][screen->player->dest->x] == 'E')
	{
		ft_printf("You won !");
		return (1);
	}
	return (0);
}

void	move_player(t_screen *screen)
{
	t_image		*asset;

	asset = screen->assets[screen->player->asset];
	screen->player->px_move -= 8;
	screen->big_picture->offx = screen->player->x * TILE_SIZE + 16;
	screen->big_picture->offy = screen->player->y * TILE_SIZE + 16;
	if (screen->player->direction == 2)
		screen->big_picture->offy += screen->player->px_move;
	if (screen->player->direction == 1)
		screen->big_picture->offx -= screen->player->px_move;
	if (screen->player->direction == 0)
		screen->big_picture->offy -= screen->player->px_move;
	if (screen->player->direction == 3)
		screen->big_picture->offx += screen->player->px_move;
	asset->offx = screen->player->direction * asset->wid_per_frame;
	asset->offy = (screen->player->frame % 4) * asset->wid_per_frame;
	screen->player->frame++;
	overwrite_asset(screen->big_picture, asset);
	if (check_enemy_touch(screen) || check_win(screen))
		clean_exit(screen);
}

void	set_next_enemy_step(t_player *enemy, t_image *big_pic)
{
	enemy->px_move -= 4;
	if (enemy->direction == 2)
		big_pic->offy -= enemy->px_move;
	if (enemy->direction == -1)
		big_pic->offx += enemy->px_move;
	if (enemy->direction == -2)
		big_pic->offy += enemy->px_move;
	if (enemy->direction == 1)
		big_pic->offx -= enemy->px_move;
}

void	move_enemy(t_screen *screen)
{
	t_image		*asset;
	t_list		*list;
	t_player	*enemy;

	list = screen->enemies;
	while (list)
	{
		enemy = list->content;
		if (enemy->px_move == 0)
			next_move_enemy(screen, enemy);
		asset = screen->assets[enemy->asset];
		screen->big_picture->offx = enemy->x * TILE_SIZE;
		screen->big_picture->offy = enemy->y * TILE_SIZE;
		if (enemy->direction)
			set_next_enemy_step(enemy, screen->big_picture);
		asset->offx = enemy->frame % 10 * asset->wid_per_frame;
		asset->offy = 0;
		enemy->frame++;
		overwrite_asset(screen->big_picture, asset);
		list = list->next;
	}
}
