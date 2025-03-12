 1- we call save_textures to save the textures
   1- we loop through the file, first we skip the empty lines
   2- for each line we call try_all_textures to try to process the texture
     1- we call process_north_south to process the north and south textures
       1- we call try_process_texture with NO
          1- we call process_texture to process the texture
             1- we skip the empty lines
             2- if line contains NO:
               1- if line starts with NO (direction)
               2- we call extract_and_assign_path to extract the path
                  1- first we skip the direction and whitespaces
                  2- using ft_strdup we copy the path to dest
                  3- we return 0 if we copied the path successfully
                  4- we return 1 if we didn't copy the path successfully
                3- if we failed to extract the path we return 1
                4- otherwise we increment the index (going to the next line)
                5- and we return 0
                6- if line doesn't start with NO we return 2
           2- if process_texture is successful
           3- we increment the directions_found
           4- we update the index
           5- we return 0
           6- if process_texture was not successful
           7- we return 1
           8- otherwise (result == 2), the line doesn't start with NO, so we return 2
        2- if try_process_texture is successful
        3- we return 0
        4- if try_process_texture is not successful
        5- we return 1
        6- we call try_process_texture with SO
           1- it is the same as NO
        7- if it is successful
        8- we return 0
        9- if it is not successful
        10- we return 1
        11- at the end if result == 2 (meaning the line doesn't start with NO or SO)
        12- we return 2
    2- if process_north_south is successful
    3- we return 0
    4- if process_north_south is not successful
    5- we return 1
    6- we call process_west_east to process the west and east textures
       1- it is the same as process_north_south
    7- if process_west_east is successful
    8- we return 0
    9- if process_west_east is not successful
    10- we return 1
    11- if none of the above(result == 2) (meaning the line doesn't start with NO, SO, WE or EA), we return 2
  3- if try_all_textures is not successful
  4- we return 1
  5- if try_all_textures returns 2 (result == 2) (meaning the line doesn't start with NO, SO, WE or EA), we print an error and return 1
  6-  we set the index to i because we didn't process any texture on this line (i is the index of the line we are currently on)
  7- if directions_found != 4
  8- we return an error weith return value of 1
  9- we return 0
2- if save_textures is not successful
3- we return 1
3- if successful we return 0


