/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husrevakbas <husrevakbas@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:00 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/26 13:47:06 by husrevakbas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

char	*get_px_addr(t_image *img, int x, int y)
{
	return (img->address + (y * img->linelen + x * (img->bits_p_px / 8)));
}

char	*get_px_addr_bg(t_bg *bg, int x, int y)
{
	return (bg->address + (y * bg->linelen + x * (bg->bits_p_px / 8)));
}

void	set_img_addr(t_image *img)
{
	img->address = mlx_get_data_addr(img->img, &img->bits_p_px,
			&img->linelen, &img->endian);
}

void	set_bg_addr(t_bg *bg)
{
	bg->address = mlx_get_data_addr(bg->img, &bg->bits_p_px,
			&bg->linelen, &bg->endian);
}

void	get_assets(t_screen *screen)
{
	t_image	*img;
	char	*pathmap[10];
	int		i;

	pathmap[GRASS] = GRASS_PATH;
	pathmap[TREE] = TREE_PATH;
	pathmap[FENCE] = FENCE_PATH;
	pathmap[PEACOCK_FL] = PEACOCK_FL_PATH;
	pathmap[BUTTERFLY] = BUTTERFLY_PATH;
	pathmap[EYEMONSTER] = EYEMONSTER_PATH;
	pathmap[COLLECTION] = COLLECTION_PATH;
	pathmap[PEACOCK_OP] = PEACOCK_OP_PATH;
	pathmap[FLOWERS] = FLOWERS_PATH;
	pathmap[9] = NULL;
	i = 0;
	while (i < 9)
	{
		img = malloc(sizeof(t_image));
		if (!img)
			ft_printf("malloc fail in get assets");
		ft_memset(img, 0, sizeof(t_image));
		img->img = mlx_xpm_file_to_image(screen->mlx, pathmap[i],
				&img->width, &img->heigth);
		if (!img->img)
			clean_exit(screen);
		set_img_addr(img);
		img->mlx = screen->mlx;
		screen->assets[i] = img;
		i++;
	}
}
