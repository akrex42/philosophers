#include "../includes/philo.h"

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
	struct 	timeval current_time;
	t_philo phi;
	check_args(&phi, argc, argv);
	t_philo args[atoi(argv[1])];
	pthread_t threads[atoi(argv[1])];
	pthread_t death_watcher;
	phi.arg.num_philo = atoi(argv[1]);

	pthread_mutex_init(&waiter, NULL);
	pthread_mutex_init(&print, NULL);

	gettimeofday(&current_time, NULL);

	for (j = 0; j < atoi(argv[1]) + 1; j++)
	{
		int res = pthread_mutex_init(&forks[j], NULL);
		if (res != 0)
		{
			printf("error");
			return (FAILURE);
		}
	}

	long time_in = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	for (j = 0; j < atoi(argv[1]); j++) {
		args[j].id = j + 1;
		args[j].arg.num_philo = atoi(argv[1]);
		args[j].arg.time_to_die = atoi(argv[2]);
		args[j].arg.time_to_eat = atoi(argv[3]);
		args[j].arg.time_to_sleep = atoi(argv[4]);
		args[j].time_in_mill = 0;
		args[j].prev_meal = 0;
		args[j].time_in_mill_before = 0;
		args[j].time_init = time_in;
		args[j].full = 0;
		if (j % 2 == 0)
		{
			args[j].priority = 1;
		}
		else
			args[j].priority = 0;
	}

	pthread_create(&death_watcher, NULL, death_routine, (void *) &args);
	j = 0;

	while (j < atoi(argv[1]))
	{
		status = pthread_create(&threads[j], NULL, philosopher, (void *) &args[j]);
		pthread_detach(threads[j]);
		if (status == FAILURE)
		{
			printf("main error: can't create thread, status = %d\n", status);
			while (j > 0)
			{
				pthread_mutex_destroy(&forks[j]);
				j--;
			}
			return (FAILURE);
		}
		j++;
	}

	for (int k = 0; k < atoi(argv[1]); k++)
	{
		if (pthread_join(death_watcher, (void *)&status_addr) == FAILURE)
		{
			while (k > 0)
			{
				pthread_mutex_destroy(&forks[k]);
				k--;
			}
		}
		else
			pthread_join(threads[k], (void *)&status_addr);
	}
	return (0);
}

// TODO death mutex
// TODO parsing
// TODO last arg with num of meals
// TODO refactor function names