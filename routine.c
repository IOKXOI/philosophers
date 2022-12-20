#include "philosopher.h"

void *routine(void *arg)
{
	t_philo *philo = arg;
	int i = philo->i + 1;
	printf("Hello philosopher numero %d fork = %d\n", i, philo->fork[i]);
	while(!philo->death)
	{
		think(i, philo);
		eat();
		sleep();
	}
	return (NULL);
}

void think(int i, t_philo *philo)
{
	if (!philo->death)
		check_timer(philo);
	if (!philo->death)
		pthread_mutex_lock(philo->fork[i]);
	if (!philo->death)
		pthread_mutex_lock(philo->fork[i - 1]);
	if (!check_timer(philo))
		philo->death == 1;
}

void eat(int i, t_philo *philo)
{
	usleep(philo->mealtime);
	if (philo)
	{
		philo->meal_to_eat--;
		if (!philo->meal_to_eat)
			end;
	}
}

void sleep(int i, t_philo *philo)
{
	usleep(philo->sleep_time);
	if (!check_timer)
		philo->death == 1;
}

int	check_timer(t_philo * philo)
{
	while(true)
	{
		gettimeoftheday
	}
}

int monitoring(void *arg)
{
	int limit_time;
	int	start;

	start = (int)*arg;
	if ()
	{
		philo->death = 1;
	}
}

debut + temps < limits;
