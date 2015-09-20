/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/17 22:41:42 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/17 22:45:06 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** parsing arguments from main (av/ae)
*/

#include "ft_script.h"

t_bool			parse_flags(char *s, t_env *e)
{
	if (*(s + 1) && !*(s + 2))
	{
		if (*(s + 1) == 'a')
			e->flags |= FLAG_A;
		else if (*(s + 1) == 'q')
			e->flags |= FLAG_Q;
		else
			return (error(USAGE, NULL));
	}
	else if (*(s + 1) && *(s + 2) && !*(s + 3))
	{
		if ((*(s + 1) == 'a' && *(s + 2) == 'q') || \
			(*(s + 1) == 'q' && *(s + 2) == 'a'))
			e->flags |= (FLAG_A | FLAG_Q);
		else
			return (error(USAGE, NULL));
	}
	else
		return (error(USAGE, NULL));
	return (TRUE);
}

t_bool			parse_av(char **av, t_env *e)
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

void			parse_ae(char **ae, t_env *e)
{
	while (*ae)
	{
		if (!ft_strncmp(*ae, "SHELL=", 6))
		{
			if (*(*ae + 6))
				e->shell = *ae + 6;
			return ;
		}
		ae++;
	}
}
