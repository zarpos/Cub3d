/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drubio-m <drubio-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:52:12 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/21 14:12:32 by drubio-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

typedef	struct s_color
{
    int red;
    int green;
    int blue;
    int alpha;
}	t_color;


typedef	struct s_map
{
	char	**map;
	char	**map_copy;
	int		rows;
	int		cols;
	char	*texture_no;
    char	*texture_so;
    char	*texture_we;
    char	*texture_ea;
    t_color floor;
    t_color ceiling;
}	t_map;

void check_args(int argc, char **argv);
void convert_map(char *argv, t_map *map);

#endif