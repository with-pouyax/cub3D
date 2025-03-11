#include "cub3d.h"

int is_direction(char *line, char *dir);
int not_valid_char(char c, int *player_count);
int check_player_count(int player_count);
int get_map_height(char **map, int start_index);
char *ft_strdup_map(char *str);
int copy_map(t_file *map, int index);

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


// int exceeds_size(char **map)
// {
//     int i;
//     int j;
//     int len;
//     int height;

//     i = 0;
//     len = 50;
//     height = 50;
//     while (map[i])
//     {
//         j = 0;
//         while (map[i][j])
//             j++;
//         if (j > len)
//             return (ft_perror("line too long", EINVAL), 1);
//         i++;
//     }
//     i = 0;
//     while (map[i])
//         i++;
//     if (i > height)
//         return (ft_perror("map too high", EINVAL), 1);
//     return (0);
// }

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
    int i;
    
    i = 2;
    if (!line)
        return(ft_perror("Error", EINVAL), 1);
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    if (line[i] == '.' && line[i + 1] == 'x' && line[i + 2] == 'p' && \
    line[i + 3] == 'm')
        return(1);
    len = ft_strlen(line);
    while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'))
        len--;
    if (len < 5 )
       return(ft_perror("Error", EINVAL), 1);
    if (ft_strncmp(line + len - 4, ".xpm", 4)) // strncmp returns 0 if the strings are equal
        return(1);
    if (len > 4 && line[len - 5] == '/')
        return(ft_perror("Error", EINVAL), 1);
    return (0);
}
    

int wrong_dir_and_ex(char **map, int *index, t_dir_flags *flags)
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
    if (flags->no > 1 || flags->so > 1 || flags->we > 1 || flags->ea > 1)
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

int is_direction(char *line, char *dir)
{
	if (line[0] == dir[0] && line[1] == dir[1] && 
		(line[2] == ' ' || line[2] == '\t'))
		return (1);
	return (0);
}

int extract_and_assign_path(char *line, char **dest)
{
	char *path;

	path = line + 3;
	while (*path && (*path == ' ' || *path == '\t'))
		path++;
	*dest = ft_strdup(path);
	if (!*dest)
		return (ft_perror("malloc", errno), 1);
	return (0);
}

int process_texture(t_file *map, int *index, char *dir, char **dest)
{
	char *line;

	skip_empty_lines(map->map, index);
	line = map->map[*index];
	
	if (is_direction(line, dir))
	{
		if (extract_and_assign_path(line, dest))
		{
			return (1);
		}
		(*index)++;
		return (0);
	}
	return (2); // Return 2 if this is not the expected direction
}

int handle_texture_result(int result, int *directions_found)
{
	if (result == 0)
		(*directions_found)++;
	else if (result == 1)
		return (1);
	return (0);
}

int save_textures(t_file *map, int *index)
{
	int result;
	int directions_found;

	directions_found = 0;
	result = process_texture(map, index, "NO", &map->textures.north);
	if (handle_texture_result(result, &directions_found))
		return (1);
	result = process_texture(map, index, "SO", &map->textures.south);
	if (handle_texture_result(result, &directions_found))
		return (1);
	result = process_texture(map, index, "WE", &map->textures.west);
	if (handle_texture_result(result, &directions_found))
		return (1);
	result = process_texture(map, index, "EA", &map->textures.east);
	if (handle_texture_result(result, &directions_found))
		return (1);
	if (directions_found != 4)
		return (ft_perror("Missing texture directions", EINVAL), 1);
	return (0);
}

int not_textures(t_file *map, int *index)
{
    int i;
    t_dir_flags flags;
    int tmp_index;

    i = 0;
    flags = (t_dir_flags){0, 0, 0, 0};
    skip_empty_lines(map->map, index);
    // printf("index: %d\n", *index);
    // printf("map[index]: %s\n", map->map[*index]);
    tmp_index = *index;  
    while (i < 4)
    {
        if(wrong_dir_and_ex(map->map, index, &flags))
            return (1);
        skip_empty_lines(map->map, index);
        i++;
    }
    if (is_duplicate(&flags))
        return (ft_perror("duplicate direction", EINVAL), 1);
    if (save_textures(map, &tmp_index))
        return (1);
    // printf("index: %d\n", *index);
    // printf("map[index]: %s\n", map->map[*index]);
    
    //we print the textures
    printf("North texture: %s\n", map->textures.north);
    printf("South texture: %s\n", map->textures.south);
    printf("West texture: %s\n", map->textures.west);
    printf("East texture: %s\n", map->textures.east);


    
    return 0;
}

int wrong_rgb(char *line)
{
	int i;
	int len;
	int comma_count;

	i = 1;
	len = ft_strlen(line);
	comma_count = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t')) // we skip the spaces and tabs at the beginning of the line
		i++;
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t')) // we skip the spaces and tabs at the end of the line
		len--;
	while (i < len)
	{
		if (line[i] == ',')
			comma_count++;
		else if (!ft_isdigit(line[i]) && line[i] != ' ' && line[i] != '\t') // we check if the character is not a digit and not a space or a tab so we can even have 2 2 2 , 2 2 2 , 2 2 2
			return (1);
		i++; // we increment the
	}
	if (comma_count != 2)
		return (1);
	return (0);
}

int parse_rgb_value(char *str, int *i)
{
	int value;
	int start;

    (void)start;
	start = *i; 
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (!str[*i] || !ft_isdigit(str[*i]))
		return (-1);
	value = 0;
	while (str[*i] && ft_isdigit(str[*i]))
	{
		value = value * 10 + (str[*i] - '0');
		if (value > 255)
			return (-1);
		(*i)++;
	}
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t')) // we skip the spaces and tabs at the end of the line
		(*i)++;
	return (value);
}

int extract_rgb(char *line, int *rgb_value)
{
	int i;
	int r;
	int g;
	int b;

	i = 1;
	while (line[i] && (line[i] == ' ' || line[i] == '\t')) // skip the spaces and tabs at the beginning of the line
		i++;
	r = parse_rgb_value(line, &i);
	if (r < 0 || r > 255 || line[i++] != ',')
		return (1);
	g = parse_rgb_value(line, &i);
	if (g < 0 || g > 255 || line[i++] != ',')
		return (1);
	b = parse_rgb_value(line, &i);
	if (b < 0 || b > 255)
		return (1);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i])
		return (1);
	*rgb_value = (r << 16) | (g << 8) | b; // we convert the rgb value to a single integer
	return (0);
}

int save_colors(t_file *map, int *index)
{
	int i;
	int result;

	i = *index;
	while (map->map[i])
	{
		if (map->map[i][0] == 'F' && (map->map[i][1] == ' ' || \
		map->map[i][1] == '\t'))
		{
			result = extract_rgb(map->map[i], &map->colors.floor); // we extract the rgb value from the line
			if (result)
				return (ft_perror("invalid floor RGB format", EINVAL), 1);
		}
		else if (map->map[i][0] == 'C' && (map->map[i][1] == ' ' || \
		map->map[i][1] == '\t'))
		{
			result = extract_rgb(map->map[i], &map->colors.ceiling);
			if (result)
				return (ft_perror("invalid ceiling RGB format", EINVAL), 1);
		}
		i++;
		if (i >= *index + 2)
			break;
	}
	return (0);
}



int wrong_color_and_rgb(char **map, int *index, t_color_flags *flags)
{
    if (map[*index][0] == 'F' && (map[*index][1] == ' ' || \
    map[*index][1] == '\t'))
        flags->floor++;
    else if (map[*index][0] == 'C' && (map[*index][1] == ' ' || \
    map[*index][1] == '\t'))
        flags->ceiling++;
    else
        return (ft_perror("wrong color", EINVAL), 1);
    if (flags->floor > 1 || flags->ceiling > 1)
        return (ft_perror("duplicate color", EINVAL), 1);
    if (wrong_rgb(map[*index]))
        return (ft_perror("wrong rgb", EINVAL), 1);
    (*index)++;
    return (0);
}

int is_duplicate_colors(t_color_flags *flags)
{
    if (flags->floor != 1 || flags->ceiling != 1)
        return (ft_perror("missing color", EINVAL), 1);
    return (0);
}

int not_colors(t_file *map, int *index)
{
	int tmp_index;
	t_color_flags flags;

	flags = (t_color_flags){0, 0};
	skip_empty_lines(map->map, index);
	tmp_index = *index;
	
	// Process all color definitions until we find a non-color line
	while (map->map[*index] && (map->map[*index][0] == 'F' || map->map[*index][0] == 'C'))
	{
		if(wrong_color_and_rgb(map->map, index, &flags))
			return (1);
		skip_empty_lines(map->map, index);
	}
	
	if (is_duplicate_colors(&flags))
		return (ft_perror("duplicate color", EINVAL), 1);
	if (save_colors(map, &tmp_index))
		return (1);
    printf("index: %d\n", *index);
    printf("map[index]: %s\n", map->map[*index]);
	
	return (0);
}

int not_valid_char(char c, int *player_count)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        (*player_count)++;
    if (*player_count > 1)
        return (ft_perror("multiple players", EINVAL), 1);
    else if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && \
    c != 'W' && c != ' ' && c != '\t')
        return (ft_perror("invalid character", EINVAL), 1);
    return (0);
}

int check_player_count(int player_count)
{
    if (player_count == 0)
        return (ft_perror("no player", EINVAL), 1);
    return (0);
}

int basic_map_check(char **map, int *index)
{
    int i;
    int j;
    int player_count;

    i = *index;
    player_count = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (not_valid_char(map[i][j], &player_count))
                return (1);
            j++;
        }
        i++;
    }
    if (check_player_count(player_count))
        return (1);
    return (0);
}

int	get_map_height(char **map, int start_index)
{
	int	height;

	height = 0;
	while (map[start_index + height])
		height++;
	return (height);
}

char	*ft_strdup_map(char *str)
{
	char	*dup;
	int		i;

	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (ft_perror("malloc", errno), NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	copy_map(t_file *map, int index)
{
	int	i;
	int	height;

	height = get_map_height(map->map, index);
	map->map_copy = malloc(sizeof(char *) * (height + 1));
	if (!map->map_copy)
		return (ft_perror("malloc", errno), 1);
	i = 0;
	while (i < height)
	{
		map->map_copy[i] = ft_strdup_map(map->map[index + i]);
		if (!map->map_copy[i])
		{
			while (--i >= 0)
				free(map->map_copy[i]);
			free(map->map_copy);
			map->map_copy = NULL;
			return (1);
		}
		i++;
	}
	map->map_copy[i] = NULL;
    
	return (0);
}

int wrong_ratio(char **map)
{
    int i;
    size_t MAX_HEIGHT;
    size_t MAX_WIDTH;

    MAX_HEIGHT = 50;
    MAX_WIDTH = 50;
    i = 0;
    while (map[i])
    {
        if (ft_strlen(map[i]) > (size_t)MAX_WIDTH)
            return (ft_perror("wrong width", EINVAL), 1);
        i++;
    }
    if ((size_t)i > MAX_HEIGHT)
        return (ft_perror("wrong height", EINVAL), 1);
    return (0);
}



int not_map(t_file *map, int *index)
{
    if (basic_map_check(map->map, index))
        return(ft_perror("basic map check", EINVAL), 1);
    if (copy_map(map, *index))
        return(ft_perror("copy map", EINVAL), 1);
    if (wrong_ratio(map->map_copy))
        return(ft_perror("wrong ratio", EINVAL), 1);
    
    for (int i = 0; map->map_copy[i]; i++)
    {
        printf("%s\n", map->map_copy[i]);
    }
    if (check_walls(map->map_copy))
        return (ft_perror("wrong walls", EINVAL), 1);
    // we print the map copy after checking the walls
    printf("-----------after checking the walls-----------\n");
    for (int i = 0; map->map_copy[i]; i++)
    {
        printf("%s\n", map->map_copy[i]);
    }
    return (0);
}

int parse_map(t_file **map)
{
    int index;

    index = 0;
    if(map_is_empty((*map)->map))
        return (1);
    // if(exceeds_size((*map)->map))
    //     return (1);
    if (is_last_line_empty((*map)->map))
        return (1);
    if (not_textures(*map, &index))
        return (1);
    if (not_colors(*map, &index))
        return (1);
    if (not_map(*map, &index))
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
	(*map)->textures.north = NULL;
	(*map)->textures.south = NULL;
	(*map)->textures.west = NULL;
	(*map)->textures.east = NULL;
	(*map)->colors.floor = 0;
	(*map)->colors.ceiling = 0;
	(*map)->map_copy = NULL;
	return (0);
}

void map_clean(t_file **map)
{
	int i;

	if (!map || !*map)
		return ;
	if ((*map)->map)
	{
		i = 0;
		while ((*map)->map[i])
			free((*map)->map[i++]);
		free((*map)->map);
	}
	if ((*map)->map_copy)
	{
		i = 0;
		while ((*map)->map_copy[i])
			free((*map)->map_copy[i++]);
		free((*map)->map_copy);
	}
	if ((*map)->textures.north)
		free((*map)->textures.north);
	if ((*map)->textures.south)
		free((*map)->textures.south);
	if ((*map)->textures.west)
		free((*map)->textures.west);
	if ((*map)->textures.east)
		free((*map)->textures.east);
	free(*map);
	*map = NULL;
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