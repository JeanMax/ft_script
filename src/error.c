/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 19:39:48 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/17 02:58:59 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** error handling
*/

#include "ft_script.h"

static void		error_msg(char e, char *msg)
{
	if (e == OPEN)
		fail("./ft_script: open failed: ");
	failn(msg);
}

t_bool			error(char e, char *msg)
{
	if (e == OPEN)
		error_msg(e, msg);
	else if (e == USAGE)
		failn("Usage: ./ft_script [-aq] [file [command ...]]");
	return (FALSE);
}
