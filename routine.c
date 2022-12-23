#include "philosopher.h"

static int think(int i, t_philo *philo)
{
	if (check_death(philo))
		mutex_print(i, "is thinking", philo);
	usleep(100);
	return (1);
}

static int eat(int i, t_philo *philo)
{
	if (check_death(philo))
		pthread_mutex_lock(&philo->fork_mutex[i - 1]);
	if (check_death(philo))
		pthread_mutex_lock(&philo->fork_mutex[i]);
	if (check_death(philo))
		mutex_print(i, "has taken a fork", philo);
	if (check_death(philo))
		mutex_print(i, "is eating", philo);
	philo->philo_last_eat[i - 1] = gettime();
	// if (!philo->philo_last_eat[i - 1])
	//{
	//	write(probleme gettime of day);
	//	return (0);
	// }
	usleep(philo->time_to_eat);
	if (check_death(philo))
		pthread_mutex_unlock(&philo->fork_mutex[i]);
	if (check_death(philo))
		pthread_mutex_unlock(&philo->fork_mutex[i - 1]);
	return (1);
}

static int sleeping(int i, t_philo *philo)
{
	if (check_death(philo))
		mutex_print(i, "is sleeping", philo);
	if (check_death(philo))
		usleep(philo->time_to_sleep);
	return (1);
}

/*
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
*/
void *routine(void *arg)
{
	t_philo *philo = arg;
	int i = philo->i + 1;
	usleep(1000);
	while (check_death(philo))
	{
		eat(i, philo);
		sleeping(i, philo);
		think(i, philo);
		// if (philo->meal_to_eat)
		//{
		// philo->meal_to_eat--;
		// if (!philo->meal_to_eat)
		// end;
		//}
	}
	return (NULL);
}
