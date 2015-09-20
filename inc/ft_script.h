/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 13:23:15 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/18 00:12:00 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H

/*
** DEFINE
*/
# define FT_SCRIPT_H

# define DEFAULT_FILE	"typescript"
# define DEFAULT_SHELL	"/bin/sh"

# define PATH_SIZE		256

# define NO_FLAG		0
# define FLAG_A			1
# define FLAG_K			2
# define FLAG_Q			4
# define FLAG_T			8

/*
** INCLUDE
*/
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
** ENUM
*/
enum	e_error
{
	USAGE,
	OPEN,
	FORK,
	EXECV
};

/*
** STRUCT && TYPEDEF
*/
typedef struct s_env	t_env;
struct		s_env
{
	t_char	flags;
	int		file_fd;
	char	*file;
	char	*shell;
	char	**cmd;
};

/*
** PROTOTYPES
**  -error.c
*/
t_bool				error(char error, char *msg);

/*
**	-put_date.c
*/
void				put_date_start(t_env *e);
void				put_date_end(t_env *e);

/*
**	-parsing.c
*/
t_bool				parse_flags(char *s, t_env *e);
t_bool				parse_av(char **av, t_env *e);
void				parse_ae(char **ae, t_env *e);

/*
**	-exec.c
*/
t_bool				exec_cmd(t_env *e);


//ZBOUB
void				debug_t_env(t_env *e); //debug

#endif
