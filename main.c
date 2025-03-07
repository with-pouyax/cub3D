#include "cub3d.h"

void ft_perror(char *msg, int err)
{
    if (err)
        errno = err;
    perror(msg);
}

void extentions_check(char *file)
{
    printf("File: %s\n", file);
}

void arg_check(int ac)
{
    if (ac != 2)
    {
        ft_perror("Error", EINVAL);
        exit(1);
    }
}

int parse_args(int ac, char **av)
{
    arg_check(ac);
    extentions_check(av[1]);
    return (0);
}

int main(int ac, char **av)
{
    if (!parse_args(ac, av))
        return (1);
    return (0);
}