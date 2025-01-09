/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:03:03 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/09 14:12:27 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H
# include "libft/libft.h"
# include "mlx.h"
# include "math.h"

# define TILE_SIZE	64
# define GRASS		0
# define GRASS_PATH	"assets/Grass_Dirt_Tile.xpm"
# define TREE		1
# define TREE_PATH	"assets/AnimatedTree.xpm"
# define FENCE		2
# define FENCE_PATH	"assets/fence_tiles.xpm"
# define PEACOCK_FL	3
# define PEACOCK_FL_PATH	"assets/Peacock-folded-tail.xpm"
# define PEACOCK_OP	4
# define PEACOCK_OP_PATH	"assets/Peacock-walk.xpm"
# define BUTTERFLY	5
# define BUTTERFLY_PATH		"assets/Yellow.xpm"
# define EYEMONSTER	6
# define EYEMONSTER_PATH	"assets/Eyemonster.xpm"
# define COLLECTION	7
# define COLLECTION_PATH	"assets/christmasicons.xpm"


typedef struct s_image
{
	void	*img;
	int		type; //player, collectible, passable, unpassable
	struct s_image	*bg;
	int		asset;
	int		frame;
	int		wid_per_frame;
	int		width;
	int		heigth;
	char	*address;
	int		bits_p_px;
	int		linelen;
	int		endian;
	int		x;
	int		y;
	int		offx;
	int		offy;
	struct s_image	*next;
}	t_image;

typedef struct s_screen
{
	void	*mlx;
	void	*win;
	int		map_w;
	int		map_h;
	struct s_image	*big_picture;
	struct s_image	*images;
	struct s_image	*assets[9];
	char	**map;
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

//MAP
char	**get_map(void);

//HOOKS
int		run_key_hook(int keycode, t_screen *args);

//IMAGE
void	overwrite(t_image *bg, t_image *img);
void	put_images(t_screen *screen);
void	set_borders(t_screen *screen, t_image *tile);
void	set_img_addr(t_image *img);
void	set_map_size(t_screen *screen);

//UTILS
void	clean_exit(t_screen *args);
int		clean_exit_button(t_screen *args);

#endif //SOLONG_H