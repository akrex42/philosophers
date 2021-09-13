#include "../includes/philo.h"

void	*philosopher(void *args)
{
	t_philo	*phi;

	phi = (t_philo *) args;
	while (1)
	{
		if (phi->priority == 0)
		{
			usleep(10);
		}
		if (phi->full == 1)
		{
			usleep(10);
			phi->full = 0;
		}
		take_forks(phi);
		create_timestamp(phi);
	}
}

void	*death_routine(void *args)
{
	int		i;
	t_philo	*phi;
	int		amount;

	i = 1;
	phi = (t_philo *) args;
	amount = phi[i].arg.num_philo;
	while (1)
	{
		i = 1;
		while (i < amount + 1)
		{
			if (check_if_dead(phi, i) == 1)
			{
				get_time(&phi[i], 0);
				printf("%ld %s %d %s", phi[i].current_time,
					   "Philosopher", phi[i].id, "died\n");
				return ((void *) FAILURE);
			}
			if (phi[1].arg.num_of_meals == -2)
			{
				pthread_mutex_lock(&print);
				printf("%s", "End of simulation!\n");
				return ((void *) FAILURE);
			}
			i++;
		}
	}
}

int	create_threads(t_philo *args, pthread_t *threads, char **argv)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	pthread_create(&threads[0], NULL, death_routine, (void *) args);
	while (i < ft_atoi(argv[1]) + 1)
	{
		pthread_create(&threads[i], NULL, philosopher, (void *) &args[i]);
		pthread_detach(threads[i]);
		i++;
	}
	pthread_join(threads[0], (void *) &result);
	return (SUCCESS);
}

int	init_mutexes(t_philo *phi, int j)
{
	int	res;

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
