#include "cub3d.h"

void ft_perror(char *msg, int err)
{
    if (err)
        errno = err;
    perror(msg);
}



void extentions_check(char *file)
{
    int len;
    
    if (!file)
    {
        ft_perror("Error", EINVAL);
        exit(1);
    }
    len = ft_strlen(file);
    while (len > 0 && (file[len - 1] == ' ' || file[len - 1] == '\t'))
        len--;
    if (len < 5 )
    {
        ft_perror("Error", EINVAL);
        exit(1);
    }
    if (ft_strncmp(file + len - 4, ".cub", 4)) // strncmp returns 0 if the strings are equal
    {
        ft_perror("Error", EINVAL);
        exit(1);
    }
    if (len > 4 && file[len - 5] == '/')
    {
        ft_perror("Error", EINVAL);
        exit(1);
    }
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
    if (parse_args(ac, av))
        return (1);
    printf("we are good to go\n");
    return (0);
}