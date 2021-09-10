#include "../includes/philo.h"

void	*philosopher(void *args)
{
	t_philo *phi = (t_philo*) args;

	while (1)
	{
		if (phi->priority == 0)
			usleep(10);
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
	t_philo *phi = (t_philo*) args;

	while (1)
	{
		if (check_if_dead(phi) == 1)
		{
			return ((void *)FAILURE);
		}
	}
}