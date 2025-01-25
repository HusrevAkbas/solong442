/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:06 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/25 16:20:23 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
/*
check if map valid
1 check rectengular
2 check reachable
*/

int	count_lines(char *filename)
{
	char	*line;
	int		i;
	int		fd;

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

char	**clear_map(char **map, int index)
{
	if (!map)
		return (NULL);
	while (*map && index >= 0)
	{
		free(map[index]);
		index--;
	}
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

void	find_player_coordinates(char **map, t_mapcheck *checker)
{
	checker->line = 0;
	while (map[checker->line])
	{
		checker->width = 0;
		while (map[checker->line][checker->width])
		{
			if (map[checker->line][checker->width] == 'P')
				return ;
			checker->width++;
		}
		checker->line++;
	}
}

char	**set_map(char *arg, int *collectible_count)
{
	char	**map;
	int		line_count;
	int		is_valid;

	if (!arg)
		return (NULL);
	if (!is_filename_ok(arg))
		return (NULL);
	line_count = count_lines(arg);
	if (line_count < 3)
		return (NULL);
	map = malloc((line_count + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	map = set_map_lines(map, arg);
	is_valid = validate_map(map);
	if (!is_valid)
		return (clear_map(map, line_count));
	*collectible_count = is_valid;
	return (map);
}
