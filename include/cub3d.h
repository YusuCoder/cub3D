
#ifndef CUB3D_H
# define CUB3D_H

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[24m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[97m"
# define RESET "\x1b[0m"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
#include <fcntl.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

enum e_output
{
	SUCCESS = 0,
	FAIL = 1,
	ERROR = 2,
};

typedef struct s_map_info
{
	int		fd;
	int		line_count;
	char	*path;
	char	**file;
	int		height;
	int		width;
	int		eom;
}			t_map_info;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	t_map_info	map_info;

}			t_data;


int	error_msg(char *str, char *msg, int e_code);
int	parse(t_data *data, char **argv);

#endif
