
#include "include/cub3d.h"

int	main(int argc, char **argv)
{

	t_data data;

	if (argc != 2)
	{
		printf("Error!\n");
		return (-1);
	}
	if (parse(&data, argv) != 0)
		return (1);
	printf("Hello. This is 🎮 cub3D\n");
	return (0);
}
