#include "cub3d.h"

void get_map_data(char **file_con, t_map *map_data)
{
    int i;
    
    for (i = 0; i < 6; i++)
    {
        if (ft_strnstr(file_con[i], "NO", 2))
            map_data->texture_no = get_texture_value(file_con[i]);
        else if (ft_strnstr(file_con[i], "SO", 2))
            map_data->texture_so = get_texture_value(file_con[i]);
        else if (ft_strnstr(file_con[i], "WE", 2))
            map_data->texture_we = get_texture_value(file_con[i]);
        else if (ft_strnstr(file_con[i], "EA", 2))
            map_data->texture_ea = get_texture_value(file_con[i]);
        else if (ft_strnstr(file_con[i], "F", 1))
            map_data->floor = get_color_value(file_con[i]);
        else if (ft_strnstr(file_con[i], "C", 1))
            map_data->ceiling = get_color_value(file_con[i]);
    }
}
