/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:03:03 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/21 15:43:52 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H
# include "libft/libft.h"
# include "mlx.h"
// # include "mlx_linux/mlx.h" //for WSL2
# include "math.h"
#include "fcntl.h"
//#include "limits.h"

# define TILE_SIZE	63
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
# define FLOWERS	8
# define FLOWERS_PATH	"assets/flowers.xpm"


typedef struct s_image
{
	void	*img;
	struct s_image	*bg;
	int		asset;	//player, collectible, passable, unpassable
	unsigned int		frame;
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
	//folded 0: down, 1: right, 2: up, 3: left
	//opened 0: right, 1: down, 2: up, 3: left
	int		direction;
	int		px_move;
	struct s_image	*player_dest;
	struct s_image	*player_start;
	struct s_image	*next;
}	t_image;

typedef struct s_screen
{
	void	*mlx;
	void	*win;
	int		map_w;
	int		map_h;
	int		count_moves;
	int		count_collectible;
	struct s_image	*big_picture;
	struct s_image	*images;
	struct s_image	*assets[9];
	struct s_image	*player;
	char	**map;
}	t_screen;

typedef struct s_mapcheck
{
	int	width;
	int	player;
	int	exit;
	int	collectibles;
	int	line;
}	t_mapcheck;

/*
	1	get arg			filename: char*
	2	set map tiles	map: char**
	3	create images	images: void*
	4	put images to window
	5	set event - hooks
*/

//ANIMATIONS
int		animate(t_screen *screen);
void	animate_tree(t_screen *screen, t_image *image);
void	move_player(t_screen *screen);

//HOOKS
void	move_down(t_screen *screen);
void	move_left(t_screen *screen);
void	move_right(t_screen *screen);
void	move_up(t_screen *screen);
int		run_key_hook(int keycode, t_screen *args);

//IMAGE
void	overwrite(t_image *bg, t_image *img);
void	overwrite_asset(t_image *bg, t_image *asset);
void	put_tiles_to_big_pic(t_image *bg, t_image *img);
void	put_images(t_screen *screen);
void	set_tiles(t_screen *screen, t_image *tile);
void	set_img_addr(t_image *img);
void	set_map_size(t_screen *screen);

//MAP
char	**set_map(char *arg);

//UTILS
void	clean_exit(t_screen *args);
int		clean_exit_button(t_screen *args);

#endif //SOLONG_H