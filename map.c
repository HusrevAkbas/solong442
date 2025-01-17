/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:06 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/17 11:49:19 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
/*
check if map valid
1 check rectengular
2 check reachable
*/

char	**get_map(void)
{
	char	**map;

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
