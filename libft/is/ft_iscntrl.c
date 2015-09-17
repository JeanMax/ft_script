/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscntrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 04:10:56 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/11 18:47:00 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** checks for a control character.
*/

#include "libft.h"

int				ft_iscntrl(int c)
{
	if (c < 32 || c == 127)
		return (TRUE);
	return (FALSE);
}