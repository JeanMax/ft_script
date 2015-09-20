/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/17 23:09:08 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/18 08:02:02 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** exec cmd given in argv, or launch shell if there's no cmd
*/

#include "ft_script.h"

static t_bool	call_execve(char **cmd, char *shell)
{
	extern char		**environ;
	char			path[PATH_SIZE];
	char			*cmd_swap;
	char			*av[3];

	*(av + 1) = ft_strdup("-i"); //debug
	*(av + 2) = NULL;
//	if (!cmd && (*av = ft_strcpy(path, shell ? shell : DEFAULT_SHELL)) \
//		&& execve(shell ? shell : DEFAULT_SHELL, av, environ))
	if (!cmd && (*av = ft_strcpy(path, DEFAULT_SHELL)) \
		&& execve(DEFAULT_SHELL, av, environ)) //debug
		return (error(EXECV, DEFAULT_SHELL));
	if (**cmd == '.' && *(*cmd + 1) == '/' && execve(*cmd, cmd, environ))
		return (error(EXECV, *cmd));
	if (ft_strlen(*cmd) > PATH_SIZE) //TODO: check joined size
		return (error(EXECV, *cmd));
	cmd_swap = *cmd;
	*cmd = path; //TODO: seriouslee, check path from env...
	if (ft_strcpy(*cmd, "/bin/") && ft_strcat(*cmd, cmd_swap))
		execve(*cmd, cmd, environ);
	if (ft_strcpy(*cmd, "/sbin/") && ft_strcat(*cmd, cmd_swap))
		execve(*cmd, cmd, environ);
	if (ft_strcpy(*cmd, "/usr/bin/") && ft_strcat(*cmd, cmd_swap))
		execve(*cmd, cmd, environ);
	if (ft_strcpy(*cmd, "/usr/sbin/") && ft_strcat(*cmd, cmd_swap))
		execve(*cmd, cmd, environ);
	return (error(EXECV, cmd_swap));
}

#include <sys/ioctl.h>

t_bool			fork_cmd(t_env *e, int *pipe_fd)
{
	pid_t	pid;
	int		status;

	status = 42;
	if ((pid = fork()) < 0)
		error(FORK, ft_itoa(pid));
	else if (!pid)
	{
		setsid();
		ioctl(pipe_fd[1], TIOCSCTTY, NULL); //debug
//		dup2(pipe_fd[1], STDIN_FILENO); //debug
		dup2(pipe_fd[1], STDOUT_FILENO);
//		dup2(pipe_fd[1], STDERR_FILENO); //TODO: handle stderr
//		close(pipe_fd[0]);
		close(pipe_fd[1]);
		call_execve(e->cmd, e->shell); //TODO: check return
		_exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status) ? FALSE : TRUE);
}

t_bool			fork_log(int file_fd, int *pipe_fd)
{
	pid_t	pid;
	int		status;
	char	buf[BUFF_SIZE + 1];
	ssize_t	i;

	status = 42;
	close(pipe_fd[1]);
	if ((pid = fork()) < 0)
		error(FORK, ft_itoa(pid));
	else if (!pid)
	{
		while ((i = read(pipe_fd[0], buf, BUFF_SIZE)) > 0)
		{
			write(STDOUT_FILENO, buf, i);
			write(file_fd, buf, i);
		}
		_exit(i < 0 ? EXIT_FAILURE : EXIT_SUCCESS); //TODO: handle error
	}
	else
		waitpid(pid, &status, 0);
	close(pipe_fd[0]);
	return (WEXITSTATUS(status) ? FALSE : TRUE);
}

t_bool			exec_cmd(t_env *e)
{
	int		pipe_fd[2];
	t_bool	ret;

	pipe(pipe_fd);  //TODO: check return
	ret = fork_cmd(e, pipe_fd); //TODO: check return
	if (ret)
		ret = fork_log(e->file_fd, pipe_fd);
	return (ret);
}
