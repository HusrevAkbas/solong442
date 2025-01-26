/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husrevakbas <husrevakbas@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:48:10 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/26 16:20:28 by husrevakbas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	find_where(char **map, t_enemycheck *checker)
{
	int	i;

	i = 1;
	while (map[checker->y][i] && map[checker->y][i] != 'F')
	{
		checker->left++;
		if (map[checker->y][i] == '1')
			checker->left = 0;
		i++;
	}
	i++;
	while (map[checker->y][i] && map[checker->y][i] != 'F')
	{
		if (map[checker->y][i] == '1')
			break;
		checker->right++;
		i++;
	}
	i = 1;
	while (map[i][checker->x] && map[i][checker->x] != 'F')
	{
		checker->up++;
		if (map[i][checker->x] == '1')
			checker->up = 0;
		i++;
	}
	i++;
	while (map[i][checker->x] && map[i][checker->x] != 'F')
	{
		if (map[i][checker->x] == '1')
			break;
		checker->down++;
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
				checker.direction = find_where(map, &checker);
				if (!can_pass_enemy(map, &checker))
					return (0);
			}
			checker.x++;
		}
		checker.y++;
	}
	return (1);
}
