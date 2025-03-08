#include "cub3d.h"

void ft_perror(char *msg, int err)
{
    if (err)
    {
        errno = err;
        perror(msg);
    }
    else
    {
        ft_putstr_fd(msg, 2);
        ft_putstr_fd("\n", 2);
    }
}

void pexit(char *msg, int err, int exit_code)
{
    ft_perror(msg, err);
    exit(exit_code);
}


void extentions_check(char *file)
{
    int len;
    
    if (!file)
        pexit("Error", EINVAL, 1);
    len = ft_strlen(file);
    while (len > 0 && (file[len - 1] == ' ' || file[len - 1] == '\t'))
        len--;
    if (len < 5 )
        pexit("Error", EINVAL, 1);
    if (ft_strncmp(file + len - 4, ".cub", 4)) // strncmp returns 0 if the strings are equal
        pexit("Error", EINVAL, 1);
    if (len > 4 && file[len - 5] == '/')
        pexit("Error", EINVAL, 1);
}

void arg_check(int ac)
{
    if (ac != 2)
    {
        ft_perror("Error", EINVAL);
        exit(1);
    }
}

void safe_close(int fd)
{
    if (close(fd) < 0)
        pexit("close", 1, 1);
}

int file_length(char *file_name)
{
    int fd;
    char c;
    int ret;
    int length;

    //(void)file_name;
    length = 0;
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        pexit("", errno, 1);
    ret = read(fd, &c, 1);
    while (ret > 0)
    {
        length++;
        ret = read(fd, &c, 1);
    }
    if (ret < 0)
        pexit("", errno, 1);
    safe_close(fd);
    return length;
}
    
int copy_file(char *file_name, char **file, int file_len)
{
    int fd;
    int ret;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (1);
    ret = read(fd, *file, file_len);
    if (ret < 0)
        return (1);
    (*file)[file_len] = '\0';
    safe_close(fd);
    return (0);
}
    

int parse_args(int ac, char **av, t_file **file)
{
    int file_len;
    char *tmp;

    (void)file;
    arg_check(ac);
    extentions_check(av[1]);
    file_len = file_length(av[1]);
    tmp = malloc(file_len + 1);
    if (!tmp)
        pexit("malloc", errno, 1);
    if (copy_file(av[1], &tmp, file_len))
    {
        free(tmp);
        return (1);
    }
    printf("tmp: %s\n", tmp);
    free(tmp);  // Free after we're done using it
    return (0);
}

int main(int ac, char **av)
{
    t_file *file;

    if (parse_args(ac, av, &file))
        return (1);
    printf("we are good to go\n");
    return (0);
}