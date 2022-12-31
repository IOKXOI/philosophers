#include "philosopher.h"

//creer tout les threads
int create_philo(t_global *global)
{
	int i;

	i = 0;
	while (i < global->nb)
	{
		if (pthread_create(&global->wait_id[i], NULL, &routine, &global->philos[i]))
			printf("error\n");
		i++;
		usleep(200);
	}
	if (pthread_create(&global->wait_id[global->i], NULL, &monitoring, global))
	   printf("error\n");
	i = 0;
	while (i < global->nb)
	{
		pthread_join(global->wait_id[i], NULL);
		i++;
	}
	return(1);
}

int	clean(t_global *global)
{
	free(global->wait_id);
	return (1);
}

int main(int argc, char *argv[])
{
	t_global global;
	global.nb = 0;
	global.death = 0;
	if (!args_traitment(argc, argv, &global))
		return (1);
	if(!init(&global))
		return(1);
	if (!create_philo(&global))
		return(1);
	clean(&global);
	return (0);
}
