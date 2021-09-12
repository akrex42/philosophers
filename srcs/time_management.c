#include "../includes/philo.h"

void 	get_time(t_philo *phi, int code)
{
	struct 	timeval current_time;

	gettimeofday(&current_time, NULL);
	if (code == 0)
	{
		phi->current_time =
				(current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - phi->time_init;
	}
	else if (code == 1)
	{
		phi->last_meal =
				(current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - phi->time_init;
	}
	else if (code == 2)
	{
		gettimeofday(&current_time, NULL);
		phi->time_left_fork =
				(current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - phi->time_init;
	}
}

void	ft_usleep(int time)
{
	struct 	timeval current_time;
	gettimeofday(&current_time, NULL);
	long start = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;

	while (current_time.tv_sec * 1000 + current_time.tv_usec / 1000 < start + time)
	{
		gettimeofday(&current_time, NULL);
		usleep(100);
	}
}

int 	check_if_dead(t_philo *phi)
{
	get_time(phi, 0);
//	printf("%ld %d %s", phi->current_time, phi->id, "current\n");
//	printf("%ld %d %s", phi->last_meal, phi->id, "last\n");
	if (phi->current_time - phi->last_meal > phi->arg.time_to_die)
	{
		return (FAILURE);
	}
//	pthread_mutex_unlock(&print);
	return (SUCCESS);
}

void 	create_timestamp(t_philo *phi)
{
	pthread_mutex_lock(&print);
	get_time(phi, 1);
//	printf("%ld %s %d %s", phi->current_time, "Philosopher", phi->id, "is eating\n");
	printf("%ld %d %s", phi->current_time, phi->id, "is eating\n");
	pthread_mutex_unlock(&print);
	ft_usleep(phi->arg.time_to_eat);
	phi->full = 1;
	if (phi->arg.num_of_meals != INT_MIN)
		phi->arg.num_of_meals--;
	drop_forks(phi);
	pthread_mutex_lock(&print);
	get_time(phi, 0);
//	printf("%ld %s %d %s", phi->current_time, "Philosopher", phi->id, "is sleeping\n");
	printf("%ld %d %s", phi->current_time, phi->id, "is sleeping\n");
	pthread_mutex_unlock(&print);
	ft_usleep(phi->arg.time_to_sleep);
	pthread_mutex_lock(&print);
	get_time(phi, 0);
//	printf("%ld %s %d %s", phi->current_time, "Philosopher", phi->id, "is thinking\n");
	printf("%ld %d %s", phi->current_time, phi->id, "is thinking\n");
//	usleep(100);
	pthread_mutex_unlock(&print);
}