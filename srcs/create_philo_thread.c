#include "../includes/philo.h"

void	*philosopher(void *args)
{
	t_philo *phi = (t_philo*) args;

	while (1)
	{
		if (phi->priority == 0)
		{
			usleep(100);
		}
//		if (phi->full == 1)
//		{
//			usleep(10);
//			phi->full = 0;
//		}
		take_forks(phi);
		create_timestamp(phi);
	}
}

void	*death_routine(void *args)
{
	t_philo *phi = (t_philo*) args;

	while (1)
	{
		if (check_if_dead(phi) == 1)
		{
			pthread_mutex_lock(&print);
			get_time(phi, 0);
//		printf("%ld %s %d %s", phi->current_time, "Philosopher", phi->id, "died\n");
			printf("%ld %d %s", phi->current_time, phi->id, "died\n");
			pthread_mutex_unlock(&print);
			return ((void *)FAILURE);
		}
		if (phi->arg.num_of_meals == -1)
		{
			pthread_mutex_lock(&print);
			printf("%s", "End of simulation!\n");
//			pthread_mutex_unlock(&print);
			return ((void *)FAILURE);
		}
	}
	return ((void *)SUCCESS);
}

int create_threads(t_philo *args, pthread_t *death_watcher, pthread_t *threads, char **argv)
{
	int status;
	int i;
//	(void)phi;
	(void)death_watcher;
	i = 0;
	status = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_create(&threads[i], NULL, philosopher, (void *) &args[i]);
		pthread_detach(threads[i]);
		i++;
	}
	return (SUCCESS);
}

int init_mutexes(t_philo *phi, int j)
{
	int res;

	pthread_mutex_init(&print, NULL);
	while (j < phi->arg.num_philo + 1)
	{
		res = pthread_mutex_init(&forks[j], NULL);
		if (res != 0)
		{
			printf("Error in mutexes creation\n");
			return (FAILURE);
		}
		j++;
	}
	return (SUCCESS);
}