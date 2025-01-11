/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husrevakbas <husrevakbas@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:06 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/12 00:15:52 by husrevakbas      ###   ########.fr       */
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

	map = malloc(4 * sizeof(char *));
	map[0] = "1111";
	map[1] = "1011";
	map[2] = "1111";
	map[3] = NULL;
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
