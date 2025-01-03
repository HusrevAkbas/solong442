/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:03:03 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/03 16:03:50 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H
# include "libft/libft.h"
# include "mlx.h"

typedef struct s_image
{
	void	*img;
	int		type; //player, collectible, passable, unpassable
	struct s_image	*sprite;
	int		frame;
	int		wid_per_frame;
	int		width;
	int		heigth;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}	t_image;

typedef struct s_screen
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	struct s_image	**images;
	struct s_image	*sprites;
}	t_screen;

typedef struct s_player
{
	int	x;
	int	y;
	int	xold;
	int	yold;
}	t_player;

/*
	1	get arg			filename: char*
	2	set map tiles	map: char**
	3	create images	images: void*
	4	put images to window
	5	set event - hooks
*/

void	clean_exit(t_screen *args);
int		clean_exit_button(t_screen *args);
int		run_key_hook(int keycode, t_screen *args);
void	set_images(t_screen *screen);

#endif //SOLONG_H