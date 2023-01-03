/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:24:41 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/03 09:28:01 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
An atoi who set the number with a pointer to let the return for error value.
Only manage decimals numbers or return an error
*/

int	s_atoi(char *str, int *nb)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	if (!str || str[i] == '\0')
		return (0);
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - 48);
		if (number + 1 < 0)
			return (0);
		i++;
	}
	*nb = number;
	if (str[i] && (!(str[i] >= '0' && str[i] <= '9')))
		return (0);
	return (1);
}
