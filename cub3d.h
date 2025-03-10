#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
# include <fcntl.h>

#include "libraries/libft/libft.h"


typedef struct s_texture_paths
{
	char *north;
	char *south;
	char *west;
	char *east;
} t_texture_paths;

typedef struct s_file
{
	char **map;
	t_texture_paths textures;
	struct s_file *next;
} t_file;

typedef struct s_dir_flags
{
	int no;
	int so;
	int we;
	int ea;
} t_dir_flags;


#endif
