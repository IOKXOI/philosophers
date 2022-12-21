#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct s_philo
{
	int				start;
	bool			*fork;
	bool			death;
	int				*philo_last_eat;
	pthread_t		*id;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*time_to_die_mutex;
	pthread_mutex_t	*death_mutex;
	size_t			i;
	size_t			nb;
	size_t			time_to_die;
	size_t			mealtime;
	size_t			sleep_time;
	size_t			meal_to_eat;
	struct timeval	*time;
}	t_philo;

//ARGS
int		args_traitment(int argc, char *argv[], t_philo *philo);
void	*routine(void *arg);
void	*monitoring(void *arg);
int		s_atoi(char *str, void *nb);
size_t	gettime(void);

#endif
