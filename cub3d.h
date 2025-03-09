#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
# include <fcntl.h>

#include "libraries/libft/libft.h"


typedef struct s_file
{
    char **map;
    char **texture;
    struct s_file *next;
} t_file;


#endif
