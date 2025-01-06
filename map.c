/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:06 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/06 12:35:47 by huakbas          ###   ########.fr       */
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
	map[0] = "111";
	map[1] = "101";
	map[2] = "111";
	map[3] = NULL;
	return (map);
}
