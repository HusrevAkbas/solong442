/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:48:10 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/27 13:32:19 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	set_enemy(t_screen *screen, t_image *tile)
{
	t_list		*list;
	t_player	*enemy;
	t_image		*asset;
	t_enemycheck	checker;

	ft_memset(&checker, 0, sizeof(t_enemycheck));
	checker.x = tile->x;
	checker.y = tile->y;
	checker.up = find_horizontal_space(screen->map, &checker);
	checker.left = find_vertical_space(screen->map, &checker);
	enemy = ft_calloc(1, sizeof(t_player));
	if (!enemy)
		clean_exit(screen);
	enemy->direction = set_enemy_direction(&checker);
	enemy->x = tile->x;
	enemy->y = tile->y;
	enemy->asset = EYEMONSTER;
	enemy->frame = 0;
	asset = screen->assets[enemy->asset];
	asset->wid_per_frame = 64;
	asset->offx = 0;
	asset->offy = 0;
	enemy->px_move = 0;
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

int	find_horizontal_space(char **map, t_enemycheck *checker)
{
	int	i;

	i = checker->y + 1;
	while (map[i][checker->x])
	{
		if (map[i][checker->x] == '0')
			checker->up++;
		else
			break;
		if (map[i][checker->x + 1] == '0' || map[i][checker->x - 1] == '0')
			checker->up_plus++;
		i++;
	}
	i = checker->y - 1;
	while (i > 0)
	{
		if (map[i][checker->x] == '0')
			checker->up++;
		else
			break;
		if (map[i][checker->x + 1] == '0' || map[i][checker->x - 1] == '0')
			checker->up_plus++;
		i--;
	}
	return (checker->up);
}

int	find_vertical_space(char **map, t_enemycheck *checker)
{
	int	i;

	i = checker->x + 1;
	while (map[checker->y][i])
	{
		if (map[checker->y][i] == '0')
			checker->left++;
		else
			break;
		if (map[checker->y + 1][i] == '0' || map[checker->y - 1][i] == '0')
			checker->left_plus++;
		i++;
	}
	i = checker->x - 1;
	while (i > 0)
	{
		if (map[checker->y][i] == '0')
			checker->left++;
		else
			break;
		if (map[checker->y + 1][i] == '0' || map[checker->y - 1][i] == '0')
			checker->left_plus++;
		i--;
	}
	return (checker->left);
}

int	set_enemy_direction(t_enemycheck *checker)
{
	if (checker->left == 0 && checker->up == 0)
		checker->direction = 0;
	else if (checker->left >= checker->up)
		checker->direction = 1;
	else
		checker->direction = 2;
	return (checker->direction);
}

void	fill_enemy_path(char **map, t_enemycheck *checker)
{
	int	i;

	checker->direction = set_enemy_direction(checker);
	if (checker->direction == 0)
		return ;
	if (checker->direction == 1 && checker->left_plus < 2)
	{
		i = checker->y;
		while (map[checker->y][i - 1] == '0')
			i--;
		while (map[checker->y][i])
		{
			if (map[checker->y][i] == '0' || map[checker->y][i] == 'F')
				map[checker->y][i] = '1';
			else
				break;
			i++;
		}
	}
	if (checker->direction == 2 && checker->up_plus < 2)
	{
		i = checker->x;
		while (map[i - 1][checker->x] == '0')
			i--;
		while (map[i][checker->x])
		{
			if (map[i][checker->x] == '0' || map[i][checker->x] == 'F')
				map[i][checker->x] = '1';
			else
				break;
			i++;
		}
	}
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
				checker.up = find_horizontal_space(map, &checker);
				checker.left = find_vertical_space(map, &checker);
				fill_enemy_path(map, &checker);
			}
			checker.x++;
		}
		checker.y++;
	}
int	i = 0;
while (map[i])
{
	ft_printf("%s\n", map[i]);
	i++;
}

	return (1);
}
