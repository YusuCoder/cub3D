/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:37:53 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/18 11:12:05 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

/*---------------*/
/*  Text colors  */
/*---------------*/
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[24m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[97m"
# define RESET "\x1b[0m"

/*----------------------*/
/*  Included libraries  */
/*----------------------*/
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "get_next_line.h"

/*-------------------*/
/*  Constant values  */
/*-------------------*/
# define WIDTH 1600
# define HEIGHT 1200
# define MIN_WIDTH 1024
# define MIN_HEIGHT 768
# define VIEW 66
# define GRID 64
# define MOVE 0.07
# define ROTATE 0.05
# define PADDING 0.1
# define MINIMAP_W 320
# define MINIMAP_H 240
# define MINIMAP_TILE 10
# define MINIMAP_PLAYER 0xFF0000FF
# define MINIMAP_EMPTY 0x000000FF
# define MINIMAP_WALL 0xFFFFFFFF
# define MOUSE_SPEED 0.002
# define ANIMATION_SPEED 6

/*-------------*/
/*  Side enum  */
/*-------------*/
typedef enum s_side
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	VERTICAL,
	HORIZONTAL,
}	t_side;

/*-------------*/
/*  Type enum  */
/*-------------*/
typedef enum s_weapon
{
	RIFLE,
	PISTOL,
	KNIFE,
}	t_weapon;

/*---------------*/
/*  Status enum  */
/*---------------*/
typedef enum s_status
{
	OPEN,
	OPENING,
	CLOSED,
	CLOSING,
}	t_status;

/*----------------*/
/*  Table struct  */
/*----------------*/
typedef struct s_table
{
	int	row;
	int	column;
}	t_table;

/*---------------------------*/
/*  Point struct (uint32_t)  */
/*---------------------------*/
typedef struct s_point_uint
{
	uint32_t	x;
	uint32_t	y;
}	t_point_uint;

/*----------------------*/
/*  Point struct (int)  */
/*----------------------*/
typedef struct s_point_int
{
	int	x;
	int	y;
}	t_point_int;

/*-------------------------*/
/*  Point struct (double)  */
/*-------------------------*/
typedef struct s_point_double
{
	double	x;
	double	y;
}	t_point_double;

/*--------------*/
/*  Map struct  */
/*--------------*/
typedef struct s_map
{
	int			fd;
	char		**map_file;
	char		**temp_map;
	char		**map2d;
	int			line_count;
	char		player_direction;
	t_point_int	player_position;
	int			color_floor;
	int			color_ceiling;
	char		*path_texture_north;
	char		*path_texture_south;
	char		*path_texture_east;
	char		*path_texture_west;
	int			width;
	int			height;
}	t_map;

/*-----------------*/
/*  Player struct  */
/*-----------------*/
typedef struct s_player
{
	double			angle;
	double			fov;
	t_side			pov;
	t_point_double	pos;
}	t_player;

/*--------------*/
/*  Ray struct  */
/*--------------*/
typedef struct s_ray
{
	double			angle;
	t_point_double	direction;
	t_table			map;
	t_point_double	delta_dist;
	t_point_int		step;
	t_point_double	side_dist;
	t_side			side;
	t_side			wall;
	double			plane_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
}	t_ray;

/*------------------*/
/*  Texture struct  */
/*------------------*/
typedef struct s_texture
{
	mlx_texture_t	*door_left[5];
	mlx_texture_t	*door_right[5];
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	int				ceiling;
	int				floor;
	char			**tex_path;
	char			**rgb_codes;
	int				*rgb_cell;
	int				*rgb_floor;
	mlx_texture_t	*test;
}	t_texture;

/*-----------------*/
/*  Sprite struct  */
/*-----------------*/
typedef struct s_sprite
{
	mlx_image_t	*aim;
	mlx_image_t	*rifle[6];
	mlx_image_t	*bullet[6];
	mlx_image_t	*pistol[9];
	mlx_image_t	*knife[7];
}	t_sprite;

/*---------------*/
/*  Door struct  */
/*---------------*/
typedef struct s_door
{
	bool		is_close;
	double		dist;
	t_point_int	pos;
	t_status	status;
	int			frame;
}	t_door;

/*---------------*/
/*  Data struct  */
/*---------------*/
typedef struct s_data
{
	int			width;
	int			height;
	t_map		map;
	t_player	player;
	t_texture	texture;
	t_sprite	sprite;
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*buf;
	t_weapon	weapon;
	bool		is_minimap;
	bool		is_door;
	t_door		door;
}	t_data;

/*-------------*/
/*  Functions  */
/*-------------*/
int			parse(t_data *data, char **argv);
int			error_msg(char *msg, int exit_code);
void		copy_map(int row, int column, int i, t_data *data);
void		extract_path(t_data *data);
void		extract_color(t_data *data);
int			map_data(t_data *data);
void		free_it(void **data);
int			get_color(int r, int g, int b, int a);
void		extract_map(t_data *data);
void		filter_map(t_data *data);
void		free_map(char **data);
void		free_and_exit(char **data);
void		check_components(t_data *data);
void		check_walls(t_data *data);
void		get_player_dir(t_data *data);

double		radian(int degree);
void		init_data(t_data *data);
void		init_map(t_data *data);
void		init_player(t_data *data);
void		init_texture(t_data *data);
void		init_sprites(t_data *data);
void		init_sprite_rifle(t_data *data, t_sprite *sprite);
void		init_sprite_pistol(t_data *data, t_sprite *sprite);
void		init_sprite_knife(t_data *data, t_sprite *sprite);
void		invert_view(t_player *player);
void		simulation(void *param);
void		close_hook(void *param);
void		resize_hook(int32_t new_width, int32_t new_height, void *param);
void		key_hook(mlx_key_data_t keydata, void *param);
void		movement_handler(t_data *data);
void		move_player(t_data *data, double move_column, double move_row);
void		movement_mouse(t_data *data);
void		ray_casting(t_data *data);
void		define_step_direction(t_ray *ray, t_player *player);
void		define_wall_collision(t_data *data, t_ray *ray);
void		define_plane_distance(t_ray *ray, t_player *player);
void		rendering(t_data *data, t_ray *ray, int x);
void		draw_ceiling_floor(t_data *data, t_ray *ray, int x);
void		draw_walls(t_data *data, t_ray *ray, int x, int y);
void		define_texture_values(t_data *data, t_ray *ray, \
								mlx_texture_t **texture, double *wall_x);
int			get_pixel(mlx_texture_t *texture, int x, int y);
void		free_array(char **array);
void		free_exit(t_data *data, int exit_status);
void		ft_perror(char *error_msg);
void		error_free_exit(t_data *data, char *error_msg);
void		draw_minimap(t_data *data);
void		draw_minimap_tiles(t_map *map, t_point_int offset, \
								mlx_image_t *img);
int			set_color(char **map, uint32_t *color, t_point_int pos, \
								char symbol);
void		set_tile_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void		draw_sprite(mlx_image_t *img, mlx_image_t *spr, int start_x, \
					int start_y);
void		draw_aim(mlx_image_t *img, mlx_image_t *aim);
void		draw_weapon(t_data *data, t_sprite *sprite);
void		draw_weapon_frame(t_data *data, mlx_image_t *curr, int frame);
void		draw_bullet(mlx_image_t *img, t_sprite *sprite, int frame);
t_point_int	set_start_point(t_weapon weapon, mlx_image_t *img, \
							mlx_image_t *curr);
int			set_frame_limit(t_weapon weapon);
mlx_image_t	*set_current_frame(t_weapon weapon, t_sprite *sprite, int frame);

#endif
