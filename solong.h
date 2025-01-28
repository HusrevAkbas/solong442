/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:03:03 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/28 12:12:45 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H
# include "libft/libft.h"
# include "mlx.h"
// # include "mlx_linux/mlx.h" //for WSL2
# include "math.h"
# include "fcntl.h"

# define TILE_SIZE	63
# define GRASS		0
# define GRASS_PATH	"assets/Grass_Dirt_Tile.xpm"
# define TREE		1
# define TREE_PATH	"assets/AnimatedTree.xpm"
# define FENCE		2
# define FENCE_PATH	"assets/fence_tiles.xpm"
# define PEACOCK_FL	3
# define PEACOCK_FL_PATH	"assets/Peacock-folded-tail.xpm"
# define EYEMONSTER	4
# define EYEMONSTER_PATH	"assets/Eyemonster.xpm"
# define COLLECTION	5
# define COLLECTION_PATH	"assets/christmasicons.xpm"
# define FLOWERS	6
# define FLOWERS_PATH	"assets/flowers.xpm"

typedef struct s_image
{
	void			*img;
	void			*mlx;
	struct s_bg		*bg;
	int				asset;	//player, collectible, passable, unpassable
	unsigned int	frame;
	int				wid_per_frame;
	int				width;
	int				heigth;
	char			*address;
	int				bits_p_px;
	int				linelen;
	int				endian;
	int				x;
	int				y;
	int				offx;
	int				offy;
	int				direction;
}	t_image;

typedef struct s_bg
{
	void	*img;
	int		width;
	int		heigth;
	char	*address;
	int		bits_p_px;
	int		linelen;
	int		endian;
	int		offx;
	int		offy;
}	t_bg;

typedef struct s_player
{
	int				asset;	//player, collectible, passable, unpassable
	unsigned int	frame;
	int				wid_per_frame;
	int				width;
	int				heigth;
	int				x;
	int				y;
	int				offx;
	int				offy;
	//folded 0: down, 1: right, 2: up, 3: left
	//opened 0: right, 1: down, 2: up, 3: left
	//enemy  1 right 2 down -2 up -1 left 0: stay
	int				direction;
	int				px_move;
	struct s_image	*start;
	struct s_image	*dest;
}	t_player;

typedef struct s_screen
{
	void			*mlx;
	void			*win;
	int				map_w;
	int				map_h;
	int				count_moves;
	int				count_collectible;
	struct s_image	*big_picture;
	struct s_list	*images;
	struct s_image	*assets[9];
	struct s_player	*player;
	struct s_list	*enemies;
	char			**map;
}	t_screen;

typedef struct s_mapcheck
{
	int	width;
	int	player;
	int	exit;
	int	collectibles;
	int	line;
}	t_mapcheck;

typedef struct s_enemycheck
{
	int	y;
	int	x;
	int	up;
	int	left_plus;
	int	left;
	int	up_plus;
	int	direction;
	int	char_f;
}	t_enemycheck;

/*
	1	get arg			filename: char*	+
	2	set map tiles	map: char**		+
	3	create images	images: void*	+
	4	put images to window			+
	5	set event - hooks				+
	6	create animations				+
	7	free before exit				+
*/

//ANIMATIONS
int		animate(t_screen *screen);
void	animate_collectible(t_screen *screen, t_image *image);
void	animate_tree(t_screen *screen, t_image *image);
int		check_enemy_touch(t_screen *screen);
void	move_enemy(t_screen *screen);
void	move_player(t_screen *screen);

//HOOKS AND MOVES
void	move_down(t_screen *screen);
void	move_left(t_screen *screen);
void	move_right(t_screen *screen);
void	move_up(t_screen *screen);
void	move_down_enemy(t_screen *screen, t_player *enemy);
void	move_left_enemy(t_screen *screen, t_player *enemy);
void	move_right_enemy(t_screen *screen, t_player *enemy);
void	move_up_enemy(t_screen *screen, t_player *enemy);
void	next_move_enemy(t_screen *screen, t_player *enemy);
int		run_key_hook(int keycode, t_screen *args);

//ENEMY STAFF
int		find_horizontal_space(char **map, t_enemycheck *checker);
int		find_vertical_space(char **map, t_enemycheck *checker);
int		set_enemy_direction(char **map, t_enemycheck *checker);

//IMAGE
void	get_assets(t_screen *screen);
char	*get_px_addr(t_image *img, int x, int y);
char	*get_px_addr_bg(t_bg *bg, int x, int y);
void	overwrite(t_image *bg, t_image *img);
void	overwrite_asset(t_image *bg, t_image *asset);
void	overwrite_bg(t_image *img);
void	overwrite_create_bg(t_bg *bg, t_image *img);
void	put_counter(t_screen *screen);
void	put_images(t_screen *screen);
void	put_tiles_to_big_pic(t_image *bg, t_image *img);
void	set_enemy(t_screen *screen, t_image *tile);
void	set_exit_point(t_screen *screen, t_image *tile, int growth);
void	set_bg_addr(t_bg *bg);
void	set_img_addr(t_image *img);
void	set_map_size(t_screen *screen);
void	set_tiles(t_screen *screen, t_image *tile);

//FENCES
void	set_top_left_corner(t_screen *screen, t_image *tile);
void	set_top_right_corner(t_screen *screen, t_image *tile);
void	set_bottom_left_corner(t_screen *screen, t_image *tile);
void	set_bottom_right_corner(t_screen *screen, t_image *tile);
void	set_left_border(t_screen *screen, t_image *tile);
void	set_rigth_border(t_screen *screen, t_image *tile);
void	set_top_border(t_screen *screen, t_image *tile);
void	set_bottom_border(t_screen *screen, t_image *tile);

//MAP
char	**clear_map(char **map, int index);
void	find_player_coordinates(char **map, t_mapcheck *checker);
int		is_filename_ok(char *arg);
char	**set_map(char *arg, int *collectible_count);
int		validate_map(char **map);

//UTILS
void	clean_exit(t_screen *args);
int		clean_exit_button(t_screen *args);

#endif //SOLONG_H