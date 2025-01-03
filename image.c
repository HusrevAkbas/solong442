/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:36:00 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/03 14:23:15 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	set_images(t_screen *screen)
{
	t_image	image;

	image.img = mlx_xpm_file_to_image(screen->mlx, "assets/Eyemonster.xpm", &image.width, &image.heigth);
	if (image.img)
		mlx_put_image_to_window(screen->mlx, screen->win, image.img, 0, 0);
	//mlx_destroy_image(screen->mlx ,image.img);
	//free(image.img);
}
