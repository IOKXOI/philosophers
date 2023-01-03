/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:21:36 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/03 23:46:47 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	gettime(void)
{
	int				time;
	struct timeval	tv;

	time = gettimeofday(&tv, NULL);
	if (time == -1)
	{
		//error("");
		return (0);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec));
}

void	mutex_print(int nb, char *str, t_global *global)
{
	nb++;
	if (!is_dead(global))
	{
		pthread_mutex_lock(&global->print_mutex);
		printf("%ld %d %s\n", gettime(), nb, str);
		pthread_mutex_unlock(&global->print_mutex);
	}
}
