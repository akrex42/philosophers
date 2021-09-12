#include "../includes/philo.h"

int	left(int n, t_philo *phi)
{
	if (n == 1)
		return (phi->arg.num_philo);
	return ((n - 1 + phi->arg.num_philo) % phi->arg.num_philo);
}

void 	drop_forks(t_philo *phi)
{
	if (phi->id % 2 == 0)
	{
		pthread_mutex_unlock(&(forks[left(phi->id, phi)]));
		pthread_mutex_unlock(&(forks[phi->id]));
	}
	else if (phi->id % 2 != 0)
	{
		pthread_mutex_unlock(&(forks[phi->id]));
		pthread_mutex_unlock(&(forks[left(phi->id, phi)]));
	}
}

void 	take_forks(t_philo *phi)
{
	if (phi->id % 2 == 0)
	{
		pthread_mutex_lock(&(forks[phi->id]));
		pthread_mutex_lock(&print);
		get_time(phi, 0);
//		printf("%ld %s %d %s", phi->current_time, "Philosopher", phi->id, "has taken the right fork\n");
		printf("%ld %d %s", phi->current_time, phi->id, "has taken the right fork\n");
		pthread_mutex_unlock(&print);
		pthread_mutex_lock(&(forks[left(phi->id, phi)]));
		pthread_mutex_lock(&print);
		get_time(phi, 2);
//		printf("%ld %s %d %s", phi->time_left_fork, "Philosopher", phi->id, "has taken the left fork\n");
		printf("%ld %d %s", phi->time_left_fork, phi->id, "has taken the left fork\n");
		pthread_mutex_unlock(&print);
	}
	else if (phi->id % 2 != 0)
	{
		pthread_mutex_lock(&(forks[left(phi->id, phi)]));
		pthread_mutex_lock(&print);
		get_time(phi, 2);
//		printf("%ld %s %d %s", phi->time_left_fork, "Philosopher", phi->id, "has taken the left fork\n");
		printf("%ld %d %s", phi->time_left_fork, phi->id, "has taken the left fork\n");
		pthread_mutex_unlock(&print);
		pthread_mutex_lock(&(forks[phi->id]));
		pthread_mutex_lock(&print);
		get_time(phi, 0);
//		printf("%ld %s %d %s", phi->current_time, "Philosopher", phi->id, "has taken the right fork\n");
		printf("%ld %d %s", phi->current_time, phi->id, "has taken the right fork\n");
		pthread_mutex_unlock(&print);
	}
//	else if (phi->id == 1)
//	{
//		pthread_mutex_lock(&(forks[phi->id]));
//		pthread_mutex_lock(&print);
//		get_time(phi, 0);
////		printf("%ld %s %d %s", phi->current_time, "Philosopher", phi->id, "has taken the right fork\n");
//		printf("%ld %d %s", phi->current_time, phi->id, "has taken the right fork\n");
//		pthread_mutex_unlock(&print);
//		pthread_mutex_lock(&(forks[left(phi->id, phi)]));
//		pthread_mutex_lock(&print);
//		get_time(phi, 2);
////		printf("%ld %s %d %s", phi->time_left_fork, "Philosopher", phi->id, "has taken the left fork\n");
//		printf("%ld %d %s", phi->time_left_fork, phi->id, "has taken the left fork\n");
//		pthread_mutex_unlock(&print);
//	}
}