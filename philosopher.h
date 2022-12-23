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
	size_t			*philo_last_eat;
	pthread_t		*id;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*time_to_die_mutex;
	pthread_mutex_t	death_mutex;
	size_t			i;
	size_t			nb;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			meal_to_eat;
	struct timeval	*time;
}	t_philo;

//ARGS
int		args_traitment(int argc, char *argv[], t_philo *philo);
void	*routine(void *arg);
void	*monitoring(void *arg);
int		s_atoi(char *str, void *nb);
size_t	gettime(void);

// mutex.c //
int		check_death(t_philo *philo);

// init.c //
int		init(t_philo *philo);

// manager.c //
size_t	gettime(void);
int		mutex_print(int nb, char *str, t_philo *philo);

#endif
