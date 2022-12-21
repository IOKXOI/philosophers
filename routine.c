#include "philosopher.h"

void think(int i, t_philo *philo)
{
	if (!philo->death)
		pthread_mutex_unlock(philo->mutex);
	if (!philo->death)
		pthread_mutex_unlock(philo->mutex);
	if (!philo->death)
		printf("%ld %d is thinking\n", gettime(), i);
}

void eat(int i, t_philo *philo)
{
	if (!philo->death)
		pthread_mutex_lock(philo->mutex);
	if (!philo->death)
		pthread_mutex_lock(philo->mutex);
	if (!philo->death)
		printf("%ld %d has taken a fork\n", gettime(), i);
	if (!philo->death)
		printf("%ld %d is eating\n", gettime(), i);
	philo->philo_last_eat[i - 1] = gettime();
	usleep(philo->mealtime);
}

void sleeping(int i, t_philo *philo)
{
	if (!philo->death)
		printf("%ld %d is sleeping\n", gettime(), i);
	if (!philo->death)
		usleep(philo->sleep_time);
}


void *monitoring(void *arg)
{
	int				i;
	int				sleep;
	int 			time;
	int				start;
	t_philo 		*philo;

	i = 0;
	philo = arg;
	pthread_mutex_lock(philo->time_to_die_mutex);
	sleep = philo->time_to_die;
	pthread_mutex_lock(philo->time_to_die_mutex);
	usleep(sleep / 2);
	while (i < (int)philo->nb)
	{
		start = philo->philo_last_eat[i];
		time = gettime();
		if ((start + time) >= ((int)(philo->start + philo->time_to_die)))
		{
			printf("%ld %d died\n", gettime(), i + 1);
			philo->death = 1;
		}
		i++;
		if (i == (int)philo->nb && !philo->death)
			i = 0;
	}
	return (NULL);
}

void *routine(void *arg)
{
	t_philo *philo = arg;
	int i = philo->i + 1;
	while(!philo->death)
	{
		think(i, philo);
		eat(i, philo);
		sleeping(i, philo);
		//if (philo->meal_to_eat)
		// {
			// philo->meal_to_eat--;
			// if (!philo->meal_to_eat)
				// end;
		// }
	}
	return (NULL);
}
