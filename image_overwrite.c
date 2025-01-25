/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_overwrite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:00 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/25 15:45:03 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	overwrite(t_image *bg, t_image *img)
{
	int		x;
	int		y;
	char	*bg_addr;
	char	*img_addr;

	if (!bg || !img || !bg->img || !img->img)
		ft_printf("Something is missing in 'overwrite' func\n");
	x = 1;
	while (x + bg->offx < bg->width && x + img->offx < img->width)
	{
		y = 1;
		while (y + bg->offy < bg->heigth && y + img->offy < img->heigth)
		{
			bg_addr = get_px_addr(bg, x + bg->offx, y + bg->offy);
			img_addr = get_px_addr(img, x + img->offx, y + img->offy);
			if (*img_addr)
				*(unsigned int *)bg_addr = *(unsigned int *)img_addr;
			y++;
		}
		x++;
	}
}

void	overwrite_create_bg(t_bg *bg, t_image *img)
{
	int		x;
	int		y;
	char	*bg_addr;
	char	*img_addr;

	if (!bg || !img || !bg->img || !img->img)
		ft_printf("Something is missing in 'overwrite create bg' func\n");
	x = 0;
	while (x + bg->offx < bg->width && x + img->offx < img->width)
	{
		y = 0;
		while (y + bg->offy < bg->heigth && y + img->offy < img->heigth)
		{
			bg_addr = get_px_addr_bg(bg, x + bg->offx, y + bg->offy);
			img_addr = get_px_addr(img, x + img->offx, y + img->offy);
			if (*img_addr)
				*(unsigned int *)bg_addr = *(unsigned int *)img_addr;
			y++;
		}
		x++;
	}
}

void	overwrite_bg(t_image *img)
{
	int		x;
	int		y;
	char	*bg_addr;
	char	*img_addr;

	if (!img || !img->bg || !img->img)
		ft_printf("Something is missing in 'overwrite' func\n");
	x = 0;
	while (x + img->bg->offx < img->bg->width && x + img->offx < img->width)
	{
		y = 0;
		while (y + img->bg->offy < img->bg->heigth
			&& y + img->offy < img->heigth)
		{
			bg_addr = get_px_addr_bg(img->bg, x + img->bg->offx,
					y + img->bg->offy);
			img_addr = get_px_addr(img, x + img->offx, y + img->offy);
			if (*bg_addr)
				*(unsigned int *)img_addr = *(unsigned int *)bg_addr;
			y++;
		}
		x++;
	}
}

void	overwrite_asset(t_image *bg, t_image *asset)
{
	int		x;
	int		y;
	char	*bg_addr;
	char	*img_addr;

	if (!bg || !asset || !bg->img || !asset->img)
		ft_printf("Something is missing in 'overwrite_asset' func\n");
	x = 0;
	y = 0;
	while (x + bg->offx < bg->width && x + asset->offx < asset->width
		&& x < asset->wid_per_frame)
	{
		y = 0;
		while (y + bg->offy < bg->heigth && y + asset->offy < asset->heigth
			&& y < asset->wid_per_frame)
		{
			bg_addr = get_px_addr(bg, x + bg->offx, y + bg->offy);
			img_addr = get_px_addr(asset, x + asset->offx, y + asset->offy);
			if (*img_addr)
				*(unsigned int *)bg_addr = *(unsigned int *)img_addr;
			y++;
		}
		x++;
	}
}

void	put_tiles_to_big_pic(t_image *big_pic, t_image *img)
{
	int		x;
	int		y;
	char	*bg_addr;
	char	*img_addr;

	if (!big_pic || !img || !big_pic->img || !img->img)
		ft_printf("Something is missing in 'put image to big pic' func\n");
	x = 0;
	y = 0;
	while (x < big_pic->width && x < img->width && x < img->wid_per_frame)
	{
		y = 0;
		while (y < big_pic->heigth && y < img->heigth && y < img->wid_per_frame)
		{
			bg_addr = get_px_addr(big_pic, x + (TILE_SIZE * img->x),
					y + (TILE_SIZE * img->y));
			img_addr = get_px_addr(img, x, y);
			if (*img_addr)
				*(unsigned int *)bg_addr = *(unsigned int *)img_addr;
			y++;
		}
		x++;
	}
}
