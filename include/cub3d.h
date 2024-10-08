/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:52:16 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/27 15:45:02 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WALL_SIZE 64
// System libraries
# include <stdio.h> 
# include <readline/readline.h> 
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>			
# include <unistd.h>			
# include <sys/wait.h>		    
# include <signal.h>			
# include <sys/stat.h>		   
# include <fcntl.h>		    	
# include <dirent.h>			
# include <string.h>			
# include <errno.h>			   
# include <termios.h>		    
# include <curses.h>			
# include <limits.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"

// Our libraries
# include "../libft/libft.h"
# include "parser.h"
# include "game.h"
#endif