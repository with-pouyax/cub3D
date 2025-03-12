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

	skip_empty_lines(map->raw_file, index);
	line = map->raw_file[*index];
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

/* 
- check is a pointer to a struct that contains a pointer to the map, a pointer to the index, and a pointer to the directions_found
- dir is the direction we are trying to process
- dest is the destination we are trying to assign the path to
 */

int try_process_texture(t_texture_check *check, char *dir, char **dest)
{
	int temp_i;
	int result;

	if (*dest) 
		return (2); // Already processed this texture
	temp_i = *(check->i);
	result = process_texture(check->map, &temp_i, dir, dest); // we process the texture
	if (result == 0)
	{
		(*(check->directions_found))++;
		*(check->i) = temp_i;
		return (0); // Successfully processed
	}
	else if (result == 1)
		return (1); // Error occurred
	
	return (2); // Not this direction
}

int process_north_south(t_texture_check *check)
{
	int result;

	result = try_process_texture(check, "NO", &check->map->textures.north);
	if (result == 0)
		return (0); // Successfully processed
	if (result == 1)
		return (1); // Error occurred
	result = try_process_texture(check, "SO", &check->map->textures.south);
	if (result == 0)
		return (0); // Successfully processed
	if (result == 1)
		return (1); // Error occurred
	return (2); // No texture processed
}

int process_west_east(t_texture_check *check)
{
	int result;

	// Try west texture
	result = try_process_texture(check, "WE", &check->map->textures.west);
	if (result == 0)
		return (0); // Successfully processed
	if (result == 1)
		return (1); // Error occurred
	// Try east texture
	result = try_process_texture(check, "EA", &check->map->textures.east);
	if (result == 0)
		return (0); // Successfully processed
	if (result == 1)
		return (1); // Error occurred
	return (2); // No texture processed
}

int try_all_textures(t_file *map, int *i, int *directions_found)
{
	t_texture_check check;
	int result;

	check.map = map; // from now check.map is pointing to map
	check.i = i;
	check.directions_found = directions_found;
	result = process_north_south(&check);
	if (result == 0)
		return (0); // Successfully processed
	if (result == 1)
		return (1); // Error occurred
	// Process west and east textures
	result = process_west_east(&check);
	if (result == 0)
		return (0); // Successfully processed
	if (result == 1)
		return (1); // Error occurred
	return (2); // No texture processed on this line
}

int save_textures(t_file *map, int *index)
{
	int i;
	int directions_found;
	int result;

	directions_found = 0;
	i = *index;
	while (map->raw_file[i] && directions_found < 4)
	{
		skip_empty_lines(map->raw_file, &i); 
		if (!map->raw_file[i])
			break;
		
		result = try_all_textures(map, &i, &directions_found);
		if (result == 1)
			return (1); // Error occurred
		if (result == 2)
			return (ft_perror("invalid texture", EINVAL), 1);
	}
	*index = i;
	if (directions_found != 4)
		return (ft_perror("Missing texture directions", EINVAL), 1);
	return (0);
}

int not_textures(t_file *map, int *index)
{
    if (save_textures(map, index))
        return (ft_perror("unable to save textures", EINVAL), 1);
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
	while (map->raw_file[i])
	{
		if (map->raw_file[i][0] == 'F' && (map->raw_file[i][1] == ' ' || \
		map->raw_file[i][1] == '\t'))
		{
			result = extract_rgb(map->raw_file[i], &map->colors.floor); // we extract the rgb value from the line
			if (result)
				return (ft_perror("invalid floor RGB format", EINVAL), 1);
		}
		else if (map->raw_file[i][0] == 'C' && (map->raw_file[i][1] == ' ' || \
		map->raw_file[i][1] == '\t'))
		{
			result = extract_rgb(map->raw_file[i], &map->colors.ceiling);
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
	skip_empty_lines(map->raw_file, index);
	tmp_index = *index;
	
	// Process all color definitions until we find a non-color line
	while (map->raw_file[*index] && (map->raw_file[*index][0] == 'F' || map->raw_file[*index][0] == 'C'))
	{
		if(wrong_color_and_rgb(map->raw_file, index, &flags))
			return (1);
		skip_empty_lines(map->raw_file, index);
	}
	
	if (is_duplicate_colors(&flags))
		return (ft_perror("duplicate color", EINVAL), 1);
	if (save_colors(map, &tmp_index))
		return (1);
    // printf("index: %d\n", *index);
    // printf("map[index]: %s\n", map->raw_file[*index]);
	
	return (0);
}

int not_valid_char(char c, int *player_count, t_file *map, t_coord *pos)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        (*player_count)++;
        if (*player_count == 1)
        {
            map->player_dir = c;
            map->player_x = (*pos).j;
            map->player_y = (*pos).i;
        }
    }
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

int basic_map_check(t_file *map, char **raw_file, int *index)
{
    t_coord pos;
    int player_count;

    pos.i = *index;
    player_count = 0;
    while (raw_file[pos.i])
    {
        pos.j = 0;
        while (raw_file[pos.i][pos.j])
        {
            if (not_valid_char(raw_file[pos.i][pos.j], &player_count, map, &pos))
                return (1);
            pos.j++;
        }
        pos.i++;
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
	int		len;

	if (!str)
		return (NULL);
	
	// Find the length without trailing whitespace
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
		len--;
	
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (ft_perror("malloc", errno), NULL);
	
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	free_game_map(char **game_map, int last_index)
{
	int	i;

	i = 0;
	while (i < last_index)
		free(game_map[i++]);
	free(game_map);
}

size_t	update_max_width(char **map, int i, size_t max_width)
{
	size_t	current_width;

	current_width = ft_strlen(map[i]);
	if (current_width > max_width)
		return (current_width);
	return (max_width);
}

int	copy_map_lines(t_file *map, int index, int height)
{
	int		i;
	size_t	max_width;

	i = 0;
	max_width = 0;
	while (i < height)
	{
		map->game_map[i] = ft_strdup_map(map->raw_file[index + i]);
		if (!map->game_map[i])
		{
			free_game_map(map->game_map, i);
			map->game_map = NULL;
			return (1);
		}
		max_width = update_max_width(map->game_map, i, max_width);
		i++;
	}
	map->game_map[i] = NULL;
	map->map_height = height;
	map->map_width = max_width;
	return (0);
}

int	copy_map(t_file *map, int index)
{
	int	height;

	height = get_map_height(map->raw_file, index);
	map->game_map = malloc(sizeof(char *) * (height + 1));
	if (!map->game_map)
		return (ft_perror("malloc", errno), 1);
	if (copy_map_lines(map, index, height))
		return (1);
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
    if (basic_map_check(map ,map->raw_file, index))
        return(ft_perror("basic map check", EINVAL), 1);
    if (copy_map(map, *index))
        return(ft_perror("copy map", EINVAL), 1);
    if (wrong_ratio(map->game_map))
        return(ft_perror("wrong ratio", EINVAL), 1);
    
    // for (int i = 0; map->game_map[i]; i++)
    // {
    //     printf("%s\n", map->game_map[i]);
    // }
    if (check_walls(map->game_map))
        return (ft_perror("wrong walls", EINVAL), 1);
    // we print the map copy after checking the walls
    // printf("-----------after checking the walls-----------\n");
    // for (int i = 0; map->game_map[i]; i++)
    // {
    //     printf("%s\n", map->game_map[i]);
    // }
    
    // Print player position
    
    return (0);
}

void print_whole_structure_in_order(t_file *map)
{
	int	r, g, b;

	printf("\n========================================\n");
	printf("            CUB3D MAP STRUCTURE         \n");
	printf("========================================\n\n");

	// Texture paths
	printf(">>> TEXTURE PATHS <<<\n");
	printf("  ▸ North : %s\n", map->textures.north);
	printf("  ▸ South : %s\n", map->textures.south);
	printf("  ▸ West  : %s\n", map->textures.west);
	printf("  ▸ East  : %s\n\n", map->textures.east);

	// Colors
	printf(">>> COLORS <<<\n");

	r = (map->colors.floor >> 16) & 0xFF;
	g = (map->colors.floor >> 8) & 0xFF;
	b = map->colors.floor & 0xFF;
	printf("  ▸ Floor  : RGB(%3d, %3d, %3d) | Hex: 0x%06X\n", r, g, b, map->colors.floor);

	r = (map->colors.ceiling >> 16) & 0xFF;
	g = (map->colors.ceiling >> 8) & 0xFF;
	b = map->colors.ceiling & 0xFF;
	printf("  ▸ Ceiling: RGB(%3d, %3d, %3d) | Hex: 0x%06X\n\n", r, g, b, map->colors.ceiling);

	// Map dimensions
	printf(">>> MAP DIMENSIONS <<<\n");
	printf("  ▸ Width : %d\n", map->map_width);
	printf("  ▸ Height: %d\n\n", map->map_height);

	// Player info
	printf(">>> PLAYER INFORMATION <<<\n");
	printf("  ▸ Direction: %c\n", map->player_dir);
	printf("  ▸ Position : (%d, %d)\n\n", map->player_x, map->player_y);

	// Game map
	printf(">>> GAME MAP <<<\n");
	for (int i = 0; map->game_map[i]; i++)
		printf("  %s\n", map->game_map[i]);

	printf("\n========================================\n");
}


int parse_map(t_file **map)
{
    int index;

    index = 0;
    if(map_is_empty((*map)->raw_file))
        return (1);
    // if(exceeds_size((*map)->raw_file))
    //     return (1);
    if (is_last_line_empty((*map)->raw_file))
        return (1);
    if (not_textures(*map, &index))
        return (1);
    if (not_colors(*map, &index))
        return (1);
    if (not_map(*map, &index))
        return (1);
    
    print_whole_structure_in_order(*map);

    
    
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
    (*map)->raw_file = ft_split(tmp, '\n');
    if (!(*map)->raw_file)
        return (free(tmp), ft_perror("malloc", errno), 1);
    // we print the map
    // for (int i = 0; (*map)->raw_file[i]; i++)
    // {
    //     printf("%s\n", (*map)->raw_file[i]);
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
	(*map)->raw_file = NULL;
	(*map)->textures.north = NULL;
	(*map)->textures.south = NULL;
	(*map)->textures.west = NULL;
	(*map)->textures.east = NULL;
	(*map)->colors.floor = 0;
	(*map)->colors.ceiling = 0;
	(*map)->game_map = NULL;
	(*map)->map_height = 0;
	(*map)->map_width = 0;
	(*map)->player_dir = '\0';
	(*map)->player_x = 0;
	(*map)->player_y = 0;
	return (0);
}

void	clean_string_array(char ***array)
{
	int	i;

	if (!array || !*array)
		return ;
	i = 0;
	while ((*array)[i])
		free((*array)[i++]);
	free(*array);
	*array = NULL;
}

void	clean_texture_paths(t_texture_paths *textures)
{
	if (!textures)
		return ;
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
}

void	cleanup(t_file **map)
{
	if (!map || !*map)
		return ;
	clean_string_array(&((*map)->raw_file));
	clean_string_array(&((*map)->game_map));
	clean_texture_paths(&((*map)->textures));
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
        cleanup(&map);
        return (1);
    }
    // now that we parsed the map, we can start the game
    // but should we start raycasting first or should we start the game first?
    // i think we should start the game first
    // because we need to load the textures first
    // and then we can start the game
    // but we need to load the textures first
    // so we need to start the game first
    // so we need to start the game first


    printf("\nwe are good to go\n");
    cleanup(&map);
    return (0);
}
