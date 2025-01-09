/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fences.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:06:07 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/09 14:21:37 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	set_top_left_corner(t_screen *screen, t_image *tile)
{
	t_image	*asset;

	tile->asset = FENCE;
	asset = screen->assets[tile->asset];
	overwrite(tile, tile->bg);
	tile->offx = 32;
	tile->offy = 32;
	overwrite(tile, screen->assets[tile->asset]);
}

void	set_borders(t_screen *screen, t_image *tile)
{
	if (tile->x == 0 && tile->y == 0)
		set_top_left_corner(screen, tile);
	else if (tile->x == screen->map_w - 1 && tile->y == 0)
		ft_printf("set top right corner\n");
	else if (tile->x == 0 && tile->y == screen->map_h - 1)
		ft_printf("set bottom left corner\n");
	else if (tile->x == screen->map_w - 1 && tile->y == screen->map_h - 1)
		ft_printf("set bottom right corner\n");
	else if (tile->x == 0)
		ft_printf("set left border\n");
	else if (tile->x == screen->map_w - 1)
		ft_printf("set right border\n");
	else if (tile->y == 0)
		ft_printf("set top border\n");
	else if (tile->y == screen->map_h - 1)
		ft_printf("set bottom border\n");
	else
		ft_printf("somethin else\n");
}
