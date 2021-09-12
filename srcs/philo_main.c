#include "../includes/philo.h"

int check_args(t_philo *phi, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Please enter 5 or 6 args\n");
		return (FAILURE);
	}
	phi->arg.num_philo = ft_atoi(argv[1]);
	if (phi->arg.num_philo > 200)
	{
		printf("No more than 200 philosophers, please!\n");
		return (FAILURE);
	}
	phi->arg.time_to_die = ft_atoi(argv[2]);
	phi->arg.time_to_eat = ft_atoi(argv[3]);
	phi->arg.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		phi->arg.num_of_meals = INT_MIN;
	else
		phi->arg.num_of_meals = ft_atoi(argv[5]);
	return (SUCCESS);
}

void init_args(t_philo *args, int j, t_philo *phi)
{
	struct 	timeval current_time;

	gettimeofday(&current_time, NULL);
	long time_in = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	for (j = 0; j < phi->arg.num_philo; j++) {
		args[j].id = j + 1;
		args[j].arg.num_philo = phi->arg.num_philo;
		args[j].arg.time_to_die = phi->arg.time_to_die;
		args[j].arg.time_to_eat = phi->arg.time_to_eat;
		args[j].arg.time_to_sleep = phi->arg.time_to_sleep;
		args[j].current_time = 0;
		args[j].last_meal = 0;
		args[j].time_init = time_in;
		args[j].full = 0;
		args[j].arg.num_of_meals = phi->arg.num_of_meals;
		if (j % 2 == 0)
		{
			args[j].priority = 1;
		}
		else
			args[j].priority = 0;
	}
}

int main(int argc, char **argv)
{
	int j;
	t_philo phi;
	if (check_args(&phi, argc, argv) == FAILURE)
		return (-1);
	t_philo args[phi.arg.num_philo];
	pthread_t threads[phi.arg.num_philo];
	pthread_t death_watcher;

	j = 0;
	if (init_mutexes(&phi, j) == FAILURE)
		return (-1);
	init_args(args, j, &phi);
	if (create_threads(args, &death_watcher, threads, argv) == FAILURE)
	{
		return (-1);
	}
	int i = 0;
	int status = 0;
	while (i < phi.arg.num_philo)
	{
		status = pthread_create(&death_watcher, NULL, death_routine, (void *) &args[i]);
		if (status == 1)
		{
			pthread_detach(death_watcher);
			return (FAILURE);
		}
		i++;
	}
	if (pthread_join(death_watcher, NULL) == 1)
		exit (0);
	return (SUCCESS);
}

// TODO death mutex