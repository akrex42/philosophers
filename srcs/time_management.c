#include "../includes/philo.h"

void 	get_time(t_philo *phi, int code)
{
	struct 	timeval current_time;

	gettimeofday(&current_time, NULL);
	if (code == 0)
	{
		phi->time_in_mill =
				(current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - phi->time_init;
	}
	else if (code == 1)
	{
		phi->time_in_mill_before =
				(current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - phi->time_init;
	}
	else if (code == 2)
	{
		gettimeofday(&current_time, NULL);
		phi->time_in_mill_left =
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
	if (phi->time_in_mill - phi->time_in_mill_before > phi->arg.time_to_die)
	{
		get_time(phi, 0);
		pthread_mutex_lock(&print);
		printf("%ld %d %s", phi->time_in_mill, phi->id, "died\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

void 	create_timestamp(t_philo *phi)
{
	get_time(phi, 1);
	pthread_mutex_lock(&print);
	printf("%ld %d %s", phi->time_in_mill_before, phi->id, "is eating\n");
	pthread_mutex_unlock(&print);
	ft_usleep(phi->arg.time_to_eat);
	phi->full = 1;
	drop_forks(phi);
	get_time(phi, 0);
	pthread_mutex_lock(&print);
	printf("%ld %d %s", phi->time_in_mill, phi->id, "is sleeping\n");
	pthread_mutex_unlock(&print);
	ft_usleep(phi->arg.time_to_sleep);
	get_time(phi, 0);
	pthread_mutex_lock(&print);
	printf("%ld %d %s", phi->time_in_mill, phi->id, "is thinking\n");
	pthread_mutex_unlock(&print);
}