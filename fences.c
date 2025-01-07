/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fences.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:06:07 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/07 16:38:41 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	set_borders(t_screen *screen, t_image *tile)
{
	if (tile->x == 0 && tile->y == 0)
		ft_printf("set top left corner\n");
	else if (tile->x == screen->map_w - 1 && tile->y == 0)
		ft_printf("set top right corner\n");
	else if (tile->x == 0 && tile->y == screen->map_h - 1)
		ft_printf("set bottom left corner\n");
	else if (tile->x == screen->map_w - 1 && tile->y == screen->map_h - 1)
		ft_printf("set bottom right corner\n");
	else if (tile->x == 0)
		ft_printf("set left border\n");
	else if (tile->x == screen->map_w - 1)
		ft_printf("set rigth border\n");
	else if (tile->y == 0)
		ft_printf("set top border\n");
	else if (tile->y == screen->map_h - 1)
		ft_printf("set bottom border\n");	
	else
		ft_printf("somethin else\n");
}
