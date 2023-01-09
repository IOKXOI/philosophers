/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:20:08 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/09 02:12:49 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

typedef struct s_global
{
	int fd1;
	int fd2;
	int fd3;
	int fd4;
	int fd5;
	size_t			start;
	bool			death;
	struct s_philo	*philos;
	pthread_t		*wait_id;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*time_to_die_mutex;
	size_t			i;
	int				nb;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			meal_to_eat;
	struct timeval	*time;
}	t_global;

typedef struct s_philo
{
	struct timeval	time_start;
	int				id;
	int				meals;
	int				end;
	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			last_eat;
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	right_fork_mutex;
	t_global		*global;
}	t_philo;

//ARGS
int		args_traitment(int argc, char *argv[], t_global *global);
void	*routine(void *arg);
void	*monitoring(void *arg);
int		s_atoi(char *str, void *nb);

// mutex.c //
int		is_dead(t_global *global);

// init.c //
int		init(t_global *global);

// manager.c //
size_t		gettime(struct timeval start);
void		mutex_print(int nb, char *str, t_global *global);
void		custom_sleep(t_philo *philo, size_t action_time);

// routine.c //
void		*only_one(void *arg);
#endif
