/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 17:17:22 by mcanal            #+#    #+#             */
/*   Updated: 2015/07/14 14:10:07 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** print a string on stderr
*/

#include "libft.h"

void	*fail(char const *s)
{
	ft_putstr_fd(s, 2);
	return (NULL);
}