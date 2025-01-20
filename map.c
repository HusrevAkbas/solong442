/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:06 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/20 11:44:30 by huakbas          ###   ########.fr       */
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

char	**set_map(char *arg)
{
	char	**map;
	int		fd;
	int		line_count;
	char	*line;
	(void) arg;

	if (!is_filename_ok(arg))
		return (NULL);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line_count = count_lines(fd);
	line = get_next_line(fd);
	if (!line)
		return (NULL);
ft_printf("%s", line);
	map = malloc(6 * sizeof(char *));
	map[0] = "111111";
	map[1] = "100011";
	map[2] = "11C001";
	map[3] = "100101";
	map[4] = "1P01E1";
	map[5] = "111111";
	map[6] = NULL;
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
	{
		heigth++;
	}
	screen->map_h = heigth;
	screen->map_w = width;
}
