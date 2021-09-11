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
		if (phi->full == 1)
		{
			usleep(100);
			phi->full = 0;
		}
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
			return ((void *)FAILURE);
		}
		if (phi->arg.num_of_meals == -1)
		{
			pthread_mutex_lock(&print);
			printf("%s", "End of simulation!\n");
			return ((void *)FAILURE);
		}
	}
}

int create_threads(t_philo *args, pthread_t *threads, char **argv)
{
	int status;
	int i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
//		if (i % 2 != 0)
//			usleep(100);
		status = pthread_create(&threads[i], NULL, philosopher, (void *) &args[i]);
		pthread_detach(threads[i]);
		if (status == FAILURE)
		{
			printf("Error in threads creation, status = %d\n", status);
			while (i > 0)
			{
				pthread_mutex_destroy(&forks[i]);
				i--;
			}
			return (FAILURE);
		}
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