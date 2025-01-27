/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:48:10 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/27 11:45:52 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	set_enemy(t_screen *screen, t_image *tile)
{
	t_list		*list;
	t_player	*enemy;
	t_image		*asset;

	enemy = ft_calloc(1, sizeof(t_player));
	if (!enemy)
		clean_exit(screen);
	enemy->x = tile->x;
	enemy->y = tile->y;
	enemy->asset = EYEMONSTER;
	enemy->frame = 0;
	asset = screen->assets[enemy->asset];
	asset->wid_per_frame = 64;
	asset->offx = 0;
	asset->offy = 0;
	enemy->px_move = 0;
	enemy->direction = 1;
	enemy->dest = tile;
	overwrite_asset(tile, asset);
	list = ft_lstnew(enemy);
	if (!list)
		clean_exit(screen);
	if (screen->enemies)
		ft_lstadd_back(&screen->enemies, list);
	else
		screen->enemies = list;
}

int	find_direction(char **map, t_enemycheck *checker)
{
	int	i;

	i = 1;
	while (map[checker->y][i])
	{
		if (map[checker->y][i] == '1' && checker->char_f)
			break;
		if (map[checker->y][i] == 'F')
			checker->char_f = 1;
		if ((map[checker->y][i] == '1' || map[checker->y][i] == 'E'
			|| map[checker->y][i] == 'C') && !checker->char_f)
			checker->left = 0;
		if (map[checker->y][i] == '0')
			checker->left++;
		i++;
	}
	checker->char_f = 0;
	i = 1;
	while (map[i][checker->x])
	{
		if (map[i][checker->x] == '1' && checker->char_f)
			break;
		if (map[i][checker->x] == 'F')
			checker->char_f = 1;
		if ((map[i][checker->x] == '1' || map[i][checker->x] == 'E'
			|| map[i][checker->x] == 'C') && !checker->char_f)
			checker->up = 0;
		if (map[i][checker->x] == '0')
			checker->up++;
		i++;
	}
	return	(1);
}

int	can_pass_enemy(char **map, t_enemycheck *checker)
{
	(void) map;
	(void) checker;
	return (1);
}

int	check_map_for_enemy(char **map)
{
	t_enemycheck	checker;

	ft_memset(&checker, 0, sizeof(t_enemycheck));
	checker.y = 0;
	while (map[checker.y])
	{
		checker.x = 0;
		while (map[checker.y][checker.x])
		{
			if (map[checker.y][checker.x] == 'F')
			{
				checker.direction = find_direction(map, &checker);
				if (!can_pass_enemy(map, &checker))
					return (0);
			}
			checker.x++;
		}
		checker.y++;
	}
	return (1);
}
