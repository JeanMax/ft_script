/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/16 21:55:33 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/17 03:18:48 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** yep, this is the main! mostly some parsing around here
*/

#include "ft_script.h"

//debug
void			debug_t_env(t_env *e)
{
	char	**cmd_swap;

	if (e->flags)
	{
		if ((e->flags & FLAG_A))
			ft_debugnbr("FLAG A", (int)e->flags);
		if ((e->flags & FLAG_Q))
			ft_debugnbr("FLAG Q", (int)e->flags);
	}
	else
		ft_debugnbr("NO FLAG", (int)e->flags);

	ft_debugstr("file", e->file ? e->file : DEFAULT_FILE);

	ft_debugstr("shell", e->shell ? e->shell : DEFAULT_SHELL);

	if ((cmd_swap = e->cmd))
		while (*cmd_swap)
			ft_debugstr("cmd", *(cmd_swap++));
	else
		ft_debugstr("cmd", NULL);
}
//\debug

static t_bool	parse_flags(char *s, t_env *e)
{
	if (*(s + 1) && !*(s + 2))
	{
		if (*(s + 1) == 'a')
			e->flags |= FLAG_A;
		else if (*(s + 1) == 'q')
			e->flags |= FLAG_Q;
		else
			return (error(USAGE, NULL)); //TODO: send *s / s[0]?
	}
	else if (*(s + 1) && *(s + 2) && !*(s + 3))
	{
		if ((*(s + 1) == 'a' && *(s + 2) == 'q') || \
			(*(s + 1) == 'q' && *(s + 2) == 'a'))
			e->flags |= (FLAG_A | FLAG_Q);
		else
			return (error(USAGE, NULL)); //TODO: send *s / s[0]?
	}
	else
		return (error(USAGE, NULL)); //TODO: send *s / s[0]?
	return (TRUE);
}

static t_bool	parse_av(char **av, t_env *e)
{
	t_bool	checking_flags;

	checking_flags = TRUE;
	while (*av)
	{
		if (checking_flags && **av == '-')
		{
			if (!parse_flags(*av, e))
				return (FALSE);
		}
		else
		{
			if (!e->file)
				e->file = *av;
			else
			{
				e->cmd = av;
				return (TRUE);
			}
			checking_flags = FALSE;
		}
		av++;
	}
	return (TRUE);
}

static t_bool	get_file_fd(t_env *e)
{
	if ((e->file_fd = open(e->file ? e->file : DEFAULT_FILE, \
			(((e->flags & FLAG_A) ? O_APPEND : O_TRUNC) | O_WRONLY | O_CREAT), \
			0664)) == -1)
		return (error(OPEN, e->file ? e->file : DEFAULT_FILE));
	return (TRUE);
}

static void		parse_ae(char **ae, t_env *e)
{
	while (*ae)
	{
		if (!ft_strncmp(*ae, "SHELL=", 5))
		{
			if (*(*ae + 6))
				e->shell = *ae + 6;
			return ;
		}
		ae++;
	}
}

int				main(int ac, char **av, char **ae)
{
	t_env	e;

	(void)ac;
	e.flags = NO_FLAG;
	e.file_fd = STDERR_FILENO;
	e.file = NULL; //BTW: if NULL after parsing, use "typescript" value (define)
	e.shell = NULL; //BTW: if NULL after parsing, use "sh" value (define)
	e.cmd = NULL; //BTW: don't try checking *(e->cmd) if empty, otherwise SEGV
	if	(!parse_av(++av, &e) || !get_file_fd(&e))
		return (EXIT_FAILURE);
	parse_ae(ae, &e);

	put_date_start(&e);
	debug_t_env(&e); //debug
	put_date_end(&e);

	return (EXIT_SUCCESS);
}
