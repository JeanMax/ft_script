/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 19:39:48 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/17 23:28:38 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** error handling
*/

#include "ft_script.h"

static void		error_msg(char error, char *msg)
{
	if (error == OPEN)
		fail("./ft_script: open failed: ");
	else if (error == FORK)
		fail("./ft_script: fork failed with pid: ");
	else if (error == EXECV)
		fail("./ft_script: execv failed with command: ");
	failn(msg);
}

t_bool			error(char error, char *msg)
{
	if (error == OPEN || error == FORK || error == EXECV)
		error_msg(error, msg);
	else if (error == USAGE)
		failn("Usage: ./ft_script [-aq] [file [command ...]]");
	return (FALSE);
}
