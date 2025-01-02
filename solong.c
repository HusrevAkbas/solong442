/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:01:55 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/02 13:37:35 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	my_pixel_put(t_data *image, int x, int y, int color)
{
	char	*dst;

	dst = image->address + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	void	*mlx;
	void	*mlx_win;
	t_data	image;
	void	*tree;
	int hei = 64;
	int wid = 1024;
	char	*relative_path="assets/AnimatedAutum.xpm";

	mlx = mlx_init();
	if (!mlx)
		return (0);
	image.img = mlx_new_image(mlx, 500, 250);
	image.address = mlx_get_data_addr(image.img,
									&image.bits_per_pixel,
									&image.line_length,
									&image.endian);
	mlx_win = mlx_new_window(mlx, 1000, 500, "lets go baby");
	int i = 50;
	int y = 50;
	while (i< 100)
	{
		my_pixel_put(&image, i, y, 0x11FF00FF);
		my_pixel_put(&image, 100 - i, y, 0x11FF00FF);
		y++;
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, image.img, 10, 10);
	tree = mlx_xpm_file_to_image(mlx, relative_path, &hei, &wid);
	if (!tree)
		return (0);
	mlx_put_image_to_window(mlx, mlx_win, tree, 200, 200);
	mlx_loop(mlx);
	return (0);
}
