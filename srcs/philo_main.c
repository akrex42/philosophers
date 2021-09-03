#include "../includes/philo.h"

static pthread_mutex_t state_fork_1;
//static pthread_mutex_t state_fork_2;
//static pthread_mutex_t state_fork_3;

int right(int n, t_philo *phi)
{
	return ((n - 1 + phi->arg.num_philo) % phi->arg.num_philo);
}

int left(int n, t_philo *phi)
{
	return ((n + 1) % phi->arg.num_philo);
}

void	*philosopher(void *args)
{
	t_philo *phi = (t_philo*) args;
	struct  timeval current_time;
	double  temp;

	if (phi->already_eaten == 0 && phi->time_in_mill_init - phi->time_in_mill > phi->arg.time_to_die)
	{
		printf("%d\t%s\n", phi->id, "died");
		fflush(stdout);
		exit (FAILURE);
	}
	if (phi->forks[phi->id] == 0)
	{
		pthread_mutex_lock(&state_fork_1);
		phi->forks[phi->id] = 1;
		printf("%d\t%s", phi->id, "has taken fork 1\n");
		if (phi->forks[right(phi->id, phi)] == 0)
		{
//			pthread_mutex_lock(&state_fork_2);
			phi->forks[right(phi->id, phi)] = 1;
			printf("%d\t%s", phi->id, "has taken fork 2\n");
			gettimeofday(&current_time, NULL);
			phi->time_in_mill_before =
					(double)(current_time.tv_sec) * 1000 + (double)(current_time.tv_usec) / 1000;
			printf("%f\t%d\t%s", phi->time_in_mill_before, phi->id, "is eating\n");
			usleep(phi->arg.time_to_eat);
			pthread_mutex_unlock(&state_fork_1);
//			pthread_mutex_unlock(&state_fork_2);
			phi->forks[phi->id] = 0;
			phi->forks[right(phi->id, phi)] = 0;
		}
		else if (phi->forks[left(phi->id, phi)] == 0)
		{
//			pthread_mutex_lock(&state_fork_3);
			phi->forks[left(phi->id, phi)] = 1;
			printf("%d\t%s", phi->id, "has taken fork 3\n");
			gettimeofday(&current_time, NULL);
			phi->time_in_mill_before =
					(double)(current_time.tv_sec) * 1000 + (double)(current_time.tv_usec) / 1000;
			printf("%f\t%d\t%s", phi->time_in_mill_before, phi->id, "is eating\n");
			usleep(phi->arg.time_to_eat);
			pthread_mutex_unlock(&state_fork_1);
//			pthread_mutex_unlock(&state_fork_3);
			phi->forks[phi->id] = 0;
			phi->forks[left(phi->id, phi)] = 0;
		}
	}
	if ((phi->forks[phi->id] == 1 && phi->forks[right(phi->id, phi)] == 1) || (phi->forks[phi->id] == 1 && phi->forks[left(phi->id, phi)] == 1))
	{
		phi->forks[phi->id] = 0;
//		if (phi->forks[right(phi->id, phi)] == 1)
//		{
//			pthread_mutex_unlock(&state_fork_2);
//			phi->forks[right(phi->id, phi)] = 0;
//		}
//		else
//		{
//			pthread_mutex_unlock(&state_fork_3);
//			phi->forks[left(phi->id, phi)] = 0;
//		}
		phi->already_eaten = 1;
		gettimeofday(&current_time, NULL);
		phi->time_in_mill =
				(double)(current_time.tv_sec) * 1000 + (double)(current_time.tv_usec) / 1000;
		printf("%f\t%d\t%s", phi->time_in_mill, phi->id, "is sleeping\n");
		usleep(phi->arg.time_to_sleep);
		gettimeofday(&current_time, NULL);
		phi->time_in_mill =
				(double)(current_time.tv_sec) * 1000 + (double)(current_time.tv_usec) / 1000;
		printf("%f\t%d\t%s", phi->time_in_mill, phi->id, "is thinking\n");
	}
//	printf("%f\t", temp);
	temp = phi->time_in_mill_before;
	phi->time_in_mill_before =
			(double)(current_time.tv_sec) * 1000 + (double)(current_time.tv_usec) / 1000;
//	printf("%f\n", phi->time_in_mill_before);
    if (phi->already_eaten == 1 && phi->time_in_mill_before - temp > phi->arg.time_to_die)
    {
        printf("%d\t%s\n", phi->id, "died");
        fflush(stdout);
        exit (FAILURE);
    }
	if (phi->time_in_mill - temp > phi->arg.time_to_die) // not sure, we need to count time form the initialization of the prog + from eating to eating
	{
		printf("%d\t%s\n", phi->id, "died");
		fflush(stdout);
		exit (FAILURE);
	}
	return ((void *)SUCCESS);
}

void check_args(t_philo *phi, int argc, char **argv)
{
	(void)argc;
	phi->arg.num_philo = atoi(argv[1]);
	phi->arg.time_to_die = atoi(argv[2]);
	phi->arg.time_to_eat = atoi(argv[3]);
	phi->arg.time_to_sleep = atoi(argv[4]);
//	printf("%d%d%d%d", phi->arg.num_philo, phi->arg.time_to_die, phi->arg.time_to_eat, phi->arg.time_to_sleep);
}

int main(int argc, char **argv)
{
//	printf("here");
	pthread_mutex_init(&state_fork_1, NULL);
//	pthread_mutex_init(&state_fork_2, NULL);
	pthread_t threads[atoi(argv[1])];
	int status;
	int j;
	int status_addr = 0;
	t_philo phi;
	check_args(&phi, argc, argv);
	t_philo args[atoi(argv[1])];
	phi.already_eaten = 0;
	memset(phi.forks, 0, phi.arg.num_philo);
	for (j = 0; j < atoi(argv[1]); j++) {
		args[j].id = j;
		args[j].arg.num_philo = atoi(argv[1]);
		args[j].arg.time_to_die = atoi(argv[2]);
		args[j].arg.time_to_eat = atoi(argv[3]);
		args[j].arg.time_to_sleep = atoi(argv[4]);
	}

	j = 0;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	phi.time_in_mill_init = (double)(current_time.tv_sec) * 1000 + (double)(current_time.tv_usec) / 1000;
	for (j = 0; j < phi.arg.num_philo; j++)
	{
		status = pthread_create(&threads[j], NULL, philosopher, (void *) &args[j]);
		if (status == FAILURE)
		{
			printf("main error: can't create thread, status = %d\n", status);
			pthread_mutex_destroy(&state_fork_1);
//			pthread_mutex_destroy(&state_fork_2);
			exit(FAILURE);
		}
		if (j + 1 == phi.arg.num_philo)
			j = 0;
	}
	for (int k = 0; k < j; k++)
	{
		pthread_join(threads[j], (void *)&status_addr);
		if (status_addr == FAILURE)
		{
			printf("main error: can't join thread, status = %d\n", status);
			pthread_mutex_destroy(&state_fork_1);
//			pthread_mutex_destroy(&state_fork_2);
			exit(ERROR_JOIN_THREAD);
		}
	}
	return (0);
}