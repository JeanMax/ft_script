/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 17:54:46 by mcanal            #+#    #+#             */
/*   Updated: 2015/03/09 01:46:32 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** checks for an uppercase letter.
*/

#include "libft.h"

int	ft_isupper(int c)
{
	if (c >= 65 && c <= 90)
		return (TRUE);
	return (FALSE);
}