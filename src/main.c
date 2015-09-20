/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/16 21:55:33 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/18 07:56:00 by mcanal           ###   ########.fr       */
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

static t_bool	get_file_fd(t_env *e)
{
	if ((e->file_fd = open(e->file ? e->file : DEFAULT_FILE, \
			(((e->flags & FLAG_A) ? O_APPEND : O_TRUNC) | O_WRONLY | O_CREAT), \
			0664)) == -1)
		return (error(OPEN, e->file ? e->file : DEFAULT_FILE));
	return (TRUE);
}

#include <term.h>
#include <sys/ioctl.h>

void			init_term(struct termios *term)
{
	char	term_buf[2048];

//	ioctl(0, TIOCGETA, term); //debug
	if (!isatty(STDIN_FILENO))
		_exit(EXIT_FAILURE);
//		error(ISATTY, NULL);
	if (tgetent(term_buf, getenv("TERM")) == -1)
		_exit(EXIT_FAILURE);
//		error(TERM, NULL);
	if (tcgetattr(STDIN_FILENO, term))
		_exit(EXIT_FAILURE);
//		error(GETATTR, NULL);

//	term->c_lflag &= (unsigned int)~(ICANON);
//	term->c_lflag &= (unsigned int)~(ECHO);
 //raw mod
    term->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
							| INLCR | IGNCR | ICRNL | IXON);
    term->c_oflag &= ~OPOST;
    term->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    term->c_cflag &= ~(CSIZE | PARENB);
    term->c_cflag |= CS8;

	term->c_cc[VTIME] = 0;
	term->c_cc[VMIN] = 1;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, term))
		_exit(EXIT_FAILURE);
//		error(SETATTR, NULL);
//	ioctl(0, TIOCSETA, term); //debug
}
/*
void			restore_term(void)
{
	g_env->term->c_lflag |= ICANON;
	g_env->term->c_lflag |= ECHO;
	if (tcsetattr(STDIN_FILENO, 0, g_env->term))
		error(SETATTR, NULL);
}
*/

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
	debug_t_env(&e); //debug

	struct termios	term;
//	init_term(&term); //debug
	if (!(e.flags & FLAG_Q))
		put_date_start(&e);

	if (!exec_cmd(&e))
		return (EXIT_FAILURE);

	if (!(e.flags & FLAG_Q))
		put_date_end(&e);

	close(e.file_fd);
	return (EXIT_SUCCESS);
}
