/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:18:42 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/14 11:49:30 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
#include <fcntl.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "get_next_line.h"

/*-------------------*/
/*  Constant values  */
/*-------------------*/
# define WIDTH 1600
# define HEIGHT 1200
# define MIN_WIDTH 320
# define MIN_HEIGHT 240
# define VIEW 66
# define GRID 64
# define MOVE 0.07
# define ROTATE 0.05
# define PADDING 0.1

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

/*----------------*/
/*  Table struct  */
/*----------------*/
typedef struct s_table
{
	int	row;
	int	column;
}	t_table;

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
	int			line_count;
	char		**map2d;
	char		player_direction;
	t_point_int	player_position;
	int			color_floor;
	int			color_ceiling;
	char		*path_texture_north;
	char		*path_texture_south;
	char		*path_texture_east;
	char		*path_texture_west;
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
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	int				*rgb_cell;
	int				*rgb_floor;
	int				ceiling;
	int				floor;
	char			**tex_path;
	char			**rgb_codes;
}	t_texture;

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
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*buf;
}	t_data;

/*-------------*/
/*  Functions  */
/*-------------*/
int		parse(t_data *data, char **argv);
int		error_msg(char *msg, int exit_code);
void	copy_map(int row, int column, int i, t_data *data);
void	extract_path(t_data *data);
void	extract_color(t_data *data);
int		map_data(t_data *data);
void	free_it(void **data);
int		get_color(int r, int g, int b, int a);

double	radian(int degree);
void	init_data(t_data *data);
void	init_map(t_data *data);
void	init_player(t_data *data);
void	invert_view(t_player *player);
void	simulation(void *param);
void	close_hook(void *param);
void	resize_hook(int32_t new_width, int32_t new_height, void *param);
void	key_hook(mlx_key_data_t keydata, void *param);
void	movement_hook(t_data *data);
void	move_player(t_data *data, double move_column, double move_row);
void	ray_casting(t_data *data);
void	define_step_direction(t_ray *ray, t_player *player);
void	define_wall_collision(t_data *data, t_ray *ray);
void	define_plane_distance(t_ray *ray, t_player *player);
void	rendering(t_data *data, t_ray *ray, int x);
void	draw_ceiling_floor(t_data *data, t_ray *ray, int x);
void	draw_walls(t_data *data, t_ray *ray, int x, int y);
void	define_texture_values(t_data *data, t_ray *ray, \
								mlx_texture_t **texture, double *wall_x);
int		get_pixel(mlx_texture_t *texture, int x, int y);
void	free_array(char **array);
void	free_exit(t_data *data, int exit_status);
void	ft_perror(char *error_msg);
void	error_free_exit(t_data *data, char *error_msg);

#endif
