#include "../includes/philo.h"

int	left(int n, t_philo *phi)
{
	if (n == 1)
		return (phi->arg.num_philo);
	return ((n - 1 + phi->arg.num_philo) % phi->arg.num_philo);
}

void	drop_forks(t_philo *phi)
{
	if (phi->id % 2 == 0 || phi->id == phi->arg.num_philo)
	{
		pthread_mutex_unlock(&(g_forks[left(phi->id, phi)]));
		pthread_mutex_unlock(&(g_forks[phi->id]));
	}
	else if (phi->id % 2 != 0)
	{
		pthread_mutex_unlock(&(g_forks[phi->id]));
		pthread_mutex_unlock(&(g_forks[left(phi->id, phi)]));
	}
}

void	take_forks_odd(t_philo *phi)
{
	pthread_mutex_lock(&(g_forks[left(phi->id, phi)]));
	pthread_mutex_lock(&g_print);
	get_time(phi, 2);
	printf("%ld %s %d %s", phi->time_left_fork,
		   "Philosopher", phi->id, "has taken the left fork\n");
	pthread_mutex_unlock(&g_print);
	pthread_mutex_lock(&(g_forks[phi->id]));
	pthread_mutex_lock(&g_print);
	get_time(phi, 0);
	printf("%ld %s %d %s", phi->current_time,
		   "Philosopher", phi->id, "has taken the right fork\n");
	pthread_mutex_unlock(&g_print);
}

void	take_forks(t_philo *phi)
{
	if (phi->id % 2 == 0 || phi->id == phi->arg.num_philo)
	{
		pthread_mutex_lock(&(g_forks[phi->id]));
		pthread_mutex_lock(&g_print);
		get_time(phi, 0);
		printf("%ld %s %d %s", phi->current_time,
			   "Philosopher", phi->id, "has taken the right fork\n");
		pthread_mutex_unlock(&g_print);
		pthread_mutex_lock(&(g_forks[left(phi->id, phi)]));
		pthread_mutex_lock(&g_print);
		get_time(phi, 2);
		printf("%ld %s %d %s", phi->time_left_fork,
			   "Philosopher", phi->id, "has taken the left fork\n");
		pthread_mutex_unlock(&g_print);
	}
	else if (phi->id % 2 != 0)
		take_forks_odd(phi);
}
