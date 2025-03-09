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


int extentions_check(char *file)
{
    int len;
    
    if (!file)
        return(ft_perror("Error", EINVAL), 1);
    len = ft_strlen(file);
    while (len > 0 && (file[len - 1] == ' ' || file[len - 1] == '\t'))
        len--;
    if (len < 5 )
       return(ft_perror("Error", EINVAL), 1);
    if (ft_strncmp(file + len - 4, ".cub", 4)) // strncmp returns 0 if the strings are equal
        return(ft_perror("Error", EINVAL), 1);
    if (len > 4 && file[len - 5] == '/')
        return(ft_perror("Error", EINVAL), 1);
    return (0);
}

int arg_check(int ac)
{
    if (ac != 2)
    {
        ft_perror("Error", EINVAL);
        return (1);
    }
    return (0);
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
        return (ft_perror("", errno), -1);
    ret = read(fd, &c, 1);
    while (ret > 0)
    {
        length++;
        ret = read(fd, &c, 1);
    }
    if (ret < 0)
    {
        safe_close(fd);
        return (ft_perror("", errno), -1);
    }
    return (length);
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
    

char *get_string(int *file_len, char **av)
{
    char *tmp;

    tmp = NULL;
    *file_len = file_length(av[1]);
    if (*file_len < 0)
        return (NULL);
    tmp = malloc(*file_len + 1);
    if (!tmp)
        return (ft_perror("malloc", errno), NULL);
    if (copy_file(av[1], &tmp, *file_len))
    {
        free(tmp);
        tmp = NULL;
    }
    return (tmp);
}

int map_is_empty(char **map)
{
    int i;
    int j;

    i = 0;
    if (!map || !map[0])
        return (ft_perror("empty map", EINVAL), 1);
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] != ' ' && map[i][j] != '\t')
                return (0);
            j++;
        }
        i++;
    }
    
    return (ft_perror("empty map", EINVAL), 1);
}


int exceeds_size(char **map)
{
    int i;
    int j;
    int len;
    int height;

    i = 0;
    len = 50;
    height = 50;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
            j++;
        if (j > len)
            return (ft_perror("line too long", EINVAL), 1);
        i++;
    }
    i = 0;
    while (map[i])
        i++;
    if (i > height)
        return (ft_perror("map too high", EINVAL), 1);
    return (0);
}

int is_last_line_empty(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
        i++;
    i--;
    j = 0;
    while (map[i][j])
    {
        if (map[i][j] != ' ' && map[i][j] != '\t')
            return (0);
        j++;
    }
    return (ft_perror("last line empty", EINVAL), 1);
}

void skip_empty_lines(char **map, int *index)
{
    int j;
    while (map[*index])
    {
        j = 0;
        while (map[*index][j])
        {
            if (map[*index][j] != ' ' && map[*index][j] != '\t')
                return;
            j++;
        }
        (*index)++;
    }
}

int no_xpm_extension(char *line)
{
    int len;
    
    if (!line)
        return(ft_perror("Error", EINVAL), 1);
    len = ft_strlen(line);
    while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'))
        len--;
    if (len < 5 )
       return(ft_perror("Error", EINVAL), 1);
    if (ft_strncmp(line + len - 4, ".xmp", 4)) // strncmp returns 0 if the strings are equal
        return(ft_perror("Error", EINVAL), 1);
    if (len > 4 && line[len - 5] == '/')
        return(ft_perror("Error", EINVAL), 1);
    return (0);
}
    

int wrong_direction(char **map, int *index, t_dir_flags *flags)
{
    if (map[*index][0] == 'N' && map[*index][1] == 'O' && \
    (map[*index][2] == ' ' || map[*index][2] == '\t'))
        flags->no++;
    else if (map[*index][0] == 'S' && map[*index][1] == 'O' && \
    (map[*index][2] == ' ' || map[*index][2] == '\t'))
        flags->so++;
    else if (map[*index][0] == 'W' && map[*index][1] == 'E' && \
    (map[*index][2] == ' ' || map[*index][2] == '\t'))
        flags->we++;
    else if (map[*index][0] == 'E' && map[*index][1] == 'A' && \
    (map[*index][2] == ' ' || map[*index][2] == '\t'))
        flags->ea++;
    else
        return (ft_perror("wrong direction", EINVAL), 1);
    if (flags->no > 2 || flags->so > 2 || flags->we > 2 || flags->ea > 2)
        return (ft_perror("duplicate direction", EINVAL), 1);
    if (no_xpm_extension(map[*index]))
        return (ft_perror("wrong extension", EINVAL), 1);
    (*index)++;
    return (0);
}

int is_duplicate(t_dir_flags *flags)
{
    if (flags->no != 1 || flags->so != 1 || flags->we != 1 || flags->ea != 1)
        return (ft_perror("missing direction", EINVAL), 1);
    return (0);
}       

int not_textures(char **map, int *index)
{
    int i;
    t_dir_flags flags;

    (void)flags;
    i = 0;
    flags = (t_dir_flags){0, 0, 0, 0};
    skip_empty_lines(map, index);

    printf("index: %d\n", *index);
    printf("map[index]: %s\n", map[*index]);
    
    while (i < 4)
    {
        if(wrong_direction(map, index, &flags))
            return (1);
        skip_empty_lines(map, index);
        i++;
    }
    if (is_duplicate(&flags))
        return (ft_perror("duplicate direction", EINVAL), 1);

    printf("index: %d\n", *index);
    printf("map[index]: %s\n", map[*index]);



    
    return 0;
}

int parse_map(t_file **map)
{
    int index;

    index = 0;
    if(map_is_empty((*map)->map))
        return (1);
    if(exceeds_size((*map)->map))
        return (1);
    if (is_last_line_empty((*map)->map))
        return (1);
    if (not_textures((*map)->map, &index))
        return (1);

    return (0);
}




int parse_args(int ac, char **av, t_file **map)
{
    int file_len;
    char *tmp;

    (void)tmp;
    (void)av;
    (void)file_len;
    (void)map;
    if (arg_check(ac))
        return (1);
    if(extentions_check(av[1]))
         return (1);
    tmp = get_string(&file_len, av);
    //printf("tmp: %s\n", tmp);
    (*map)->map = ft_split(tmp, '\n');
    if (!(*map)->map)
        return (free(tmp), ft_perror("malloc", errno), 1);
    // we print the map
    // for (int i = 0; (*map)->map[i]; i++)
    // {
    //     printf("%s\n", (*map)->map[i]);
    // }
    
   if (parse_map(map))
      return (free(tmp), 1);

    free(tmp);
    return (0);
}

int init_map(t_file **map)
{
    *map = malloc(sizeof(t_file));
    if (!*map)
        return(ft_perror("malloc", errno), 1);
    (*map)->map = NULL;
    (*map)->texture = NULL;
    (*map)->next = NULL;
    return (0);
}

void map_clean(t_file **map)
{
    int i;

    i = 0;
    if ((*map)->map)
    {
        while ((*map)->map[i])
            free((*map)->map[i++]);
        free((*map)->map);
        free(*map);
        *map = NULL;
    }
    else
    {
        free(*map);
        *map = NULL;
    }
}

int main(int ac, char **av)
{
    t_file *map;

    if(init_map(&map))
        return (1);
    if (parse_args(ac, av, &map))
    {
        map_clean(&map);
        return (1);
    }
    printf("we are good to go\n");
    map_clean(&map);
    return (0);
}