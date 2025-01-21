/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:06 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/21 16:35:06 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
/*
check if map valid
1 check rectengular
2 check reachable
*/

int	is_filename_ok(char *arg)
{
	int	length;

	if (!arg)
		return (0);
	length = ft_strlen(arg);
	if (length <= 4)
		return (0);
	if (arg[length - 4] != '.' || arg[length - 3] != 'b'|| arg[length - 2] != 'e'|| arg[length - 1] != 'r')
		return (0);
	return (1);
}

int	count_lines(int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

char	**clear_map(char **map, int index)
{
	(void) index;
	// while (index >= 0)
	// {
	// 	free(map[index]);
	// 	index--;
	// }
	free(map);
	return (NULL);
}

char	**set_map_lines(char **map, char *filename)
{
	char	*line;
	int		fd;
	int		i;

	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	if (!line)
		return (clear_map(map, -1));
	i = 0;
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	is_line_valid(char *line, t_mapcheck *checker,int last)
{
	int	i;

	if (line[0] != '1')
		return (0);
	i = 1;
	while (line[i])
	{
		if ((checker->line == 0 || last) && line[i] != '1')
			return (0);
		if (line[i] != '0' && line[i] != '1' && line[i] != 'P'
			&& line[i] != 'C' && line[i] != 'E')
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

void	find_player_coordinates(char **map, t_mapcheck *checker)
{
	checker->line = 0;
	while (map[checker->line])
	{
		checker->width = 0;
		while (map[checker->line][checker->width])
		{
			if (map[checker->line][checker->width] == 'P') return ;
			checker->width++;
		}
		checker->line++;
	}
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

int	check_map(char **mapcopy)
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

	map_copy = malloc(checker->line * sizeof(char *));
	if (!map_copy)
		return (0);
	i = 0;
	while (map[i])
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			clear_map(map_copy, i);
			return (0);
		}
		i++;
	}
	map_copy[i] = NULL;
	find_player_coordinates(map_copy, checker);
	fill_map(map_copy, checker->line, checker->width);
	res = check_map(map_copy);
	clear_map(map_copy, i - 1);
	return (res);
}

int	validate_map(char **map)
{
	t_mapcheck	checker;
	int			i;

	if (!map)
		return (0);
	checker.width = ft_strlen(map[0]);
	checker.player = 0;
	checker.collectibles = 0;
	checker.exit = 0;
	i = 0;
	while (map[i])
	{
		checker.line = i;
		if ((int)ft_strlen(map[i]) != checker.width)
			return (0);
		if (!is_line_valid(map[i], &checker, 0))
			return (0);
		i++;
	}
	if (!checker.collectibles || checker.player != 1 || checker.exit != 1
		|| !is_line_valid(map[i-1], &checker, 1) || !can_be_finished(map, &checker))
		return (0);
	return (1);
}

char	**set_map(char *arg)
{
	char	**map;
	int		line_count;
	int		fd;

	if (!arg)
		return (NULL);
	if (!is_filename_ok(arg))
		return (NULL);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line_count = count_lines(fd);
	close(fd);
	if (line_count < 3)
		return (NULL);
	map = malloc(line_count * sizeof(char *));
	map = set_map_lines(map, arg);
	fd = validate_map(map);
	if (!fd)
		return (clear_map(map, line_count));
	return (map);
}

void	set_map_size(t_screen *screen)
{
	int	heigth;
	int	width;

	heigth = 0;
	width = 0;
	width = ft_strlen(screen->map[0]);
	while (screen->map[heigth])
		heigth++;
	screen->map_h = heigth;
	screen->map_w = width;
}
