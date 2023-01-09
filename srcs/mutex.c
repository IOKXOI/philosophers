/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:32:26 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/09 08:40:01 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_global *global)
{
	pthread_mutex_lock(&global->death_mutex);
	if (global->death)
	{
		pthread_mutex_unlock(&global->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&global->death_mutex);
	return (0);
}
