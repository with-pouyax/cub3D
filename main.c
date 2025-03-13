#include "cub3d.h"

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
