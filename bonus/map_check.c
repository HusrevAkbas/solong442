/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:06 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/28 12:12:34 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
/*
check if map valid
1 check rectengular
2 check reachable
*/

int	is_line_valid(char *line, t_mapcheck *checker, int y, int is_last)
{
	int	i;

	if (line[0] != '1')
		return (0);
	i = 1;
	while (line[i])
	{
		if ((y == 0 || is_last == 1) && line[i] != '1')
			return (0);
		if (line[i] != '0' && line[i] != '1' && line[i] != 'P'
			&& line[i] != 'C' && line[i] != 'E' && line[i] != 'F')
			return (0);
		if (line[i] == 'C')
			checker->collectibles++;
		if (line[i] == 'P')
			checker->player++;
		if (line[i] == 'E')
			checker->exit++;
		i++;
	}
	if (line[i - 1] != '1')
		return (0);
	return (1);
}

void	fill_map(char **map_copy, int y, int x)
{
	if (!map_copy || !map_copy[y] || !map_copy[y][x] || map_copy[y][x] == '1'
		|| y < 0 || x < 0)
		return ;
	map_copy[y][x] = '1';
	fill_map(map_copy, y, x - 1);
	fill_map(map_copy, y, x + 1);
	fill_map(map_copy, y + 1, x);
	fill_map(map_copy, y - 1, x);
}

int	check_map_after_fill_map(char **mapcopy)
{
	int	y;
	int	x;

	y = 0;
	while (mapcopy[y])
	{
		x = 0;
		while (mapcopy[y][x])
		{
			if (mapcopy[y][x] == 'E' || mapcopy[y][x] == 'C')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	can_be_finished(char **map, t_mapcheck *checker)
{
	char	**map_copy;
	int		i;
	int		res;

	map_copy = ft_calloc((checker->line + 1), sizeof(char *));
	if (!map_copy)
		return (0);
	i = 0;
	while (i < checker->line)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			clear_map(map_copy, i);
			return (0);
		}
		i++;
	}
	find_player_coordinates(map_copy, checker);
	fill_map(map_copy, checker->line, checker->width);
	res = check_map_after_fill_map(map_copy);
	clear_map(map_copy, i - 1);
	return (res);
}

int	validate_map(char **map)
{
	t_mapcheck	checker;
	int			i;

	if (!map || !*map)
		return (0);
	ft_memset(&checker, 0, sizeof(t_mapcheck));
	checker.width = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != checker.width)
			return (0);
		if (!is_line_valid(map[i], &checker, i, 0))
			return (0);
		i++;
	}
	checker.line = i;
	if (!checker.collectibles || checker.player != 1 || checker.exit != 1
		|| !is_line_valid(map[i - 1], &checker, i - 1, 1)
		|| !can_be_finished(map, &checker))
		return (0);
	return (checker.collectibles);
}
