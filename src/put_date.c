/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_date.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/17 02:26:52 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/17 02:54:08 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** put first and last messages on specified file and stdout
*/

#include "ft_script.h"

void				put_date_start(t_env *e)
{
	struct timeval	time;

	if ((e->flags & FLAG_Q))
		return ;
	gettimeofday(&time, NULL);
	ft_putstr("Script started, file is ");
	ft_putendl(e->file ? e->file : DEFAULT_FILE);
	ft_putstr_fd("Script started on ", e->file_fd);
	ft_putstr_fd(ctime(&time.tv_sec), e->file_fd);
}

void				put_date_end(t_env *e)
{
	struct timeval	time;

	if ((e->flags & FLAG_Q))
		return ;
	gettimeofday(&time, NULL);
	ft_putstr("Script done, file is ");
	ft_putendl(e->file ? e->file : DEFAULT_FILE);
	ft_putstr_fd("Script done on ", e->file_fd);
	ft_putstr_fd(ctime(&time.tv_sec), e->file_fd);
}
