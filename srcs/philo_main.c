#include "../includes/philo.h"

pthread_mutex_t *forks;
pthread_mutex_t waiter;

void	ft_usleep(int time)
{
	struct 	timeval current_time;
	gettimeofday(&current_time, NULL);
	long start = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;

	while (current_time.tv_sec * 1000 + current_time.tv_usec / 1000 < start + time)
	{
		gettimeofday(&current_time, NULL);
		usleep(1000);
	}
}

void 	check_if_dead(t_philo *phi)
{
	struct 	timeval current_time;
	gettimeofday(&current_time, NULL);
	if (phi->time_in_mill - phi->time_in_mill_before > phi->arg.time_to_die || phi->time_in_mill_before - phi->prev_meal > phi->arg.time_to_die)
	{
		phi->time_in_mill =
				current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		printf("%ld\t%d\t%s", phi->time_in_mill, phi->id, "died\n");
		exit (FAILURE);
	}
}

void 	create_timestamp(t_philo *phi, int code)
{
	struct 	timeval current_time;

	gettimeofday(&current_time, NULL);
	phi->time_in_mill =
			current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	if (code == 0)
	{
		phi->prev_meal = phi->time_in_mill_before;
		if (phi->time_in_mill_before == 0)
			phi->prev_meal = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		phi->time_in_mill_before =
				current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		check_if_dead(phi);
		printf("%ld\t%d\t%s", phi->time_in_mill_before, phi->id, "is eating\n");
		ft_usleep(phi->arg.time_to_eat);
	}
	else if (code == 1)
	{
		printf("%ld\t%d\t%s", phi->time_in_mill, phi->id, "is sleeping\n");
		ft_usleep(phi->arg.time_to_sleep);
	}
	else
	{
		printf("%ld\t%d\t%s", phi->time_in_mill, phi->id, "is thinking\n");
//		ft_usleep(1000);
	}

}

int right(int n, t_philo *phi)
{
	if (n == 1)
		return (phi->arg.num_philo);
	return ((n - 1 + phi->arg.num_philo) % phi->arg.num_philo);
}

int left(int n, t_philo *phi)
{
	return ((n + 1) % phi->arg.num_philo);
}

void 	drop_forks(t_philo *phi, int code)
{
	if (code == 0)
	{
		pthread_mutex_unlock(&(forks[phi->id]));
		pthread_mutex_unlock(&(forks[right(phi->id, phi)]));
	}
	else if (code == 1)
	{
		pthread_mutex_unlock(&(forks[right(phi->id, phi)]));
	}
}

int 	take_forks(t_philo *phi)
{
	pthread_mutex_lock(&waiter);
	if (pthread_mutex_lock(&(forks[phi->id])) == 0)
	{
		printf("%d\t%s", phi->id, "has taken the left fork\n");
		if (pthread_mutex_lock(&(forks[right(phi->id, phi)])) == 0)
		{
			printf("%d\t%s", phi->id, "has taken the right fork\n");
			return (0);
		}
		else
			return (1);
	}
	return (-1);
}

void	*philosopher(void *args)
{
	t_philo *phi = (t_philo*) args;
	int		result;

//	struct 	timeval current_time;
//
//	gettimeofday(&current_time, NULL);
//	phi->time_in_mill =
//			current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	check_if_dead(phi);
	result = take_forks(phi);
	if (result == 0)
	{
//		printf("%ld\n", phi->time_in_mill_before);
//		printf("%ld\n", phi->time_in_mill);
//		printf("%ld\n", phi->prev_meal);
		check_if_dead(phi);
		create_timestamp(phi, 0);
		drop_forks(phi, 0);
//		printf("%ld\n", phi->time_in_mill_before);
//		printf("%ld\n", phi->time_in_mill);
//		printf("%ld\n", phi->prev_meal);
		check_if_dead(phi);
		create_timestamp(phi, 1);
		check_if_dead(phi);
		create_timestamp(phi, 2);
		pthread_mutex_unlock(&waiter);
	}
	else if (result == 1)
		drop_forks(phi, 1);
	else
	{
		printf("error");
		exit (-1);
	}
	check_if_dead(phi);
	return ((void *)SUCCESS);
}

void check_args(t_philo *phi, int argc, char **argv)
{
	(void)argc;
	phi->arg.num_philo = atoi(argv[1]);
	phi->arg.time_to_die = atoi(argv[2]);
	phi->arg.time_to_eat = atoi(argv[3]);
	phi->arg.time_to_sleep = atoi(argv[4]);
}

int main(int argc, char **argv)
{
	int status;
	int j;
	int status_addr = 0;
	t_philo phi;
	check_args(&phi, argc, argv);
	t_philo args[atoi(argv[1])];
	pthread_t threads[3];
	phi.arg.num_philo = atoi(argv[1]);
	pthread_mutex_init(&waiter, NULL);
//	pthread_mutex_init(&death, NULL);
//	j = 0;
//
//	status = pthread_create(&phi.threads[j], NULL, philosopher, (void *) &args[j]);
//	printf("%d", status);
	struct 	timeval current_time;

	gettimeofday(&current_time, NULL);

	for (j = 0; j < atoi(argv[1]); j++) {
		args[j].id = j + 1;
		args[j].arg.num_philo = atoi(argv[1]);
		args[j].arg.time_to_die = atoi(argv[2]);
		args[j].arg.time_to_eat = atoi(argv[3]);
		args[j].arg.time_to_sleep = atoi(argv[4]);
		args[j].time_in_mill = 0;
		args[j].prev_meal = 0;
		args[j].time_in_mill_before = 0;
	}
	forks = malloc(sizeof(forks) * atoi(argv[1]));
	for (j = 0; j < atoi(argv[1]) + 1; j++)
	{
		int res = pthread_mutex_init(&forks[j], NULL);
//		printf("%d", res);
		if (res != 0)
		{
			printf("error");
			exit(-1);
		}
	}

	j = 0;
	int flag = 0;
	while (j < atoi(argv[1]))
	{
		status = pthread_create(&threads[j], NULL, philosopher, (void *) &args[j]);
//		printf("%d", status);
		if (status == FAILURE)
		{
			printf("main error: can't create thread, status = %d\n", status);
			while (j > 0)
			{
				pthread_mutex_destroy(&forks[j]);
				j--;
			}
			exit(FAILURE);
		}
		if (j + 2 >= atoi(argv[1]) && flag == 0)
		{
			ft_usleep(1000);
			j = -1;
			flag = 1;
		}
		if (j + 2 >= atoi(argv[1]) && flag == 1)
		{
			j = -2;
			flag = 0;
		}
		j+=2;
	}

	for (int k = 0; k < atoi(argv[1]); k++)
	{
		pthread_join(threads[j], (void *)&status_addr);
		if (status_addr == FAILURE)
		{
			printf("main error: can't join thread, status = %d\n", status);
			while (k > 0)
			{
				pthread_mutex_destroy(&forks[k]);
				k--;
			}
			exit(ERROR_JOIN_THREAD);
		}
	}
	free (forks);
	return (0);
}

// TODO death mutex