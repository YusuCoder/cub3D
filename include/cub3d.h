
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
# define WIDTH 800
# define HEIGHT 600
# define VIEW 60
# define GRIDSIZE 64

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
	char		**map2d;
	char		player_direction;
	t_point_int	player_position;
}	t_map;

/*-----------------*/
/*  Player struct  */
/*-----------------*/
typedef struct s_player
{
	t_point_int	pos;
	int			pov;
	double		fov;
}	t_player;

/*---------------*/
/*  Data struct  */
/*---------------*/
typedef struct s_data
{
	int			width;
	int			height;
	t_map		map;
	t_player	player;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_data;

/*-------------*/
/*  Functions  */
/*-------------*/
void	init_data(t_data *data);
void	init_map(t_map *map);
void	init_player(t_player *player, t_map *map);
void	run_simulation(t_data *data);
double	radian(int degree);
void	ft_perror(char *error_msg);
void	error_exit(t_data *data);
void	free_array(char **array);
void	free_exit(t_data *data);

#endif
