
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

/*----------------*/
/*  Window sizes  */
/*----------------*/
# define WIDTH 800
# define HEIGHT 600
/*------------------*/
/* enums for status */
/*------------------*/
enum e_output
{
	SUCCESS = 0,
	FAIL = 1,
	ERROR = 2,
};

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
	char	**map;
	char	**map2d;
	char	*colors;
	int		fd;
	int		line_count;
	char	*path;
	int		height;
	int		width;
	int		eom;
}	t_map;

/*-----------------*/
/*  Player struct  */
/*-----------------*/
typedef struct s_player
{
	char		c;
	t_point_int	pos;
}	t_player;

/*-------------------*/
/*  Textures struct  */
/*-------------------*/
typedef struct s_texture
{
	int				*floor;
	int				*cell;
	unsigned long	floor_color;
	unsigned long	cell_color;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			**tex_path;
	t_point_double	pos;
}		t_texture;
/*---------------*/
/*  Data struct  */
/*---------------*/
typedef struct s_data
{
	int			width;
	int			height;
	void		*window;
	t_map		map_info;
	mlx_t		*mlx;
	t_texture	tex_info;
	mlx_image_t	*img;
	t_player	player;
}	t_data;

/*-------------*/
/*  Functions  */
/*-------------*/
void	init_data(t_data *data);
void	ft_perror(char *error_msg);
void	error_exit(t_data *data);
void	free_exit(t_data *data);

/*-----------PARSING------------*/
int		error_msg(char *str, char *msg, int e_code);
int		parse(t_data *data, char **argv);
void	validate_map(char *file, t_data *data);
int		map_data(t_data *data, char **map);
void	free_it(void **data);
void	check_map_contents(t_data *data, char **map);

#endif
