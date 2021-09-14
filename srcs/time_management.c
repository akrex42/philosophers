#include "../includes/philo.h"

void	get_time(t_philo *phi, int code)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (code == 0)
	{
		phi->current_time = (current_time.tv_sec * 1000
				+ current_time.tv_usec / 1000) - phi->time_init;
	}
	else if (code == 1)
	{
		phi->last_meal = (current_time.tv_sec * 1000
				+ current_time.tv_usec / 1000) - phi->time_init;
	}
	else if (code == 2)
	{
		gettimeofday(&current_time, NULL);
		phi->time_left_fork = (current_time.tv_sec * 1000
				+ current_time.tv_usec / 1000) - phi->time_init;
	}
}

void	ft_usleep(int time)
{
	struct timeval	current_time;
	long			start;

	gettimeofday(&current_time, NULL);
	start = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	while (current_time.tv_sec * 1000
		+ current_time.tv_usec / 1000 < start + time)
	{
		gettimeofday(&current_time, NULL);
		usleep(100);
	}
}

int	check_if_dead(t_philo *phi, int i)
{
	pthread_mutex_lock(&g_print);
	get_time(&phi[i], 0);
	if (phi[i].current_time - phi[i].last_meal > phi[i].arg.time_to_die)
	{
		return (FAILURE);
	}
	pthread_mutex_unlock(&g_print);
	return (SUCCESS);
}

void	create_timestamp(t_philo *phi)
{
	pthread_mutex_lock(&g_print);
	get_time(phi, 1);
	printf("%ld %s %d %s", phi->current_time,
		   "Philosopher", phi->id, "is eating\n");
	pthread_mutex_unlock(&g_print);
	ft_usleep(phi->arg.time_to_eat);
	phi->full = 1;
	if (phi->arg.num_of_meals != INT_MIN)
		phi->arg.num_of_meals--;
	drop_forks(phi);
	pthread_mutex_lock(&g_print);
	get_time(phi, 0);
	printf("%ld %s %d %s", phi->current_time,
		   "Philosopher", phi->id, "is sleeping\n");
	pthread_mutex_unlock(&g_print);
	ft_usleep(phi->arg.time_to_sleep);
	pthread_mutex_lock(&g_print);
	get_time(phi, 0);
	printf("%ld %s %d %s", phi->current_time,
		   "Philosopher", phi->id, "is thinking\n");
	pthread_mutex_unlock(&g_print);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	res;
	int			minus;

	i = 0;
	minus = 1;
	res = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == ' '
		   || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * minus);
}
