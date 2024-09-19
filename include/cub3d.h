
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
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

/*-------------------*/
/*  Constant values  */
/*-------------------*/
# define WIDTH 1920
# define HEIGHT 1080
# define VIEW 60
# define GRID 64
# define MOVE 0.02
# define ROTATE 0.02

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

/*-------------------------*/
/*  Point struct (double)  */
/*-------------------------*/
typedef struct s_ray
{
	double			angle;
	t_point_double	direction;
	t_point_int		map;
	t_point_double	delta_dist;
	t_point_int		step;
	t_point_double	side_dist;
	int				hit;
	int				side;
	double			plane_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				wall_color;
}	t_ray;

/*--------------*/
/*  Map struct  */
/*--------------*/
typedef struct s_map
{
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
	t_point_double	pos;
	double			pov;
	double			fov;
}	t_player;

/*------------------*/
/*  Texture struct  */
/*------------------*/
typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	int				ceiling;
	int				floor;
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
	t_ray		ray;
	t_texture	texture;
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*buf;
}	t_data;

/*-------------*/
/*  Functions  */
/*-------------*/
void	init_data(t_data *data);
void	init_map(t_data *data);
void	init_player(t_data *data);
void	rendering(void *param);
double	radian(int degree);
void	free_array(char **array);
void	free_exit(t_data *data, int exit_status);
void	ft_perror(char *error_msg);
void	error_free_exit(t_data *data, char *error_msg);

#endif
