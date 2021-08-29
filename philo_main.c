#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>


//# define NUM_THREADS 4
# define NUM_PHILO 5
# define SUCCESS 0
# define FAILURE 1
# define ERROR_JOIN_THREAD -10
# define TIME_TO_DIE 40
# define TIME_TO_EAT 10
# define TIME_TO_SLEEP 10
# define TIME_TO_THINK 10

static pthread_mutex_t state_mutex;

typedef struct s_philo {
	int		id;
	int		forks[NUM_PHILO];
	double	time_in_mill;
	double	time_in_mill_before;
	double	time_in_mill_init;
	int 	already_eaten;
} t_philo;

int right(int n)
{
	return ((n - 1 + NUM_PHILO) % NUM_PHILO);
}

int left(int n)
{
	return ((n + 1) % NUM_PHILO);
}

void	*philosopher(void *args)
{
	t_philo *phi = (t_philo*) args;
	struct timeval current_time;

	if (phi->already_eaten && phi->time_in_mill_init - phi->time_in_mill > TIME_TO_DIE)
	{
		printf("%d\t%s\n", phi->id, "died");
		fflush(stdout);
		exit (FAILURE);
	}
	pthread_mutex_lock(&state_mutex);
	phi->forks[phi->id] = 1;
	printf("%d\t%s", phi->id, "has taken a fork\n");
	phi->forks[right(phi->id)] = 1;
	printf("%d\t%s", phi->id, "has taken a fork\n");
	if (right(phi->id) == 1)
		phi->forks[left(phi->id)] = 1;
	gettimeofday(&current_time, NULL);
	phi->time_in_mill_before =
			(double)(current_time.tv_sec) * 1000 + (double)(current_time.tv_usec) / 1000;
	printf("%f\t%d\t%s", phi->time_in_mill_before, phi->id, "is eating\n");
	usleep(TIME_TO_EAT);
	phi->already_eaten = 1;
	pthread_mutex_unlock(&state_mutex);
	phi->forks[phi->id] = 0;
	if (right(phi->id) == 1)
		phi->forks[right(phi->id)] = 0;
	else
		phi->forks[left(phi->id)] = 0;
	gettimeofday(&current_time, NULL);
	phi->time_in_mill =
			(double)(current_time.tv_sec) * 1000 + (double)(current_time.tv_usec) / 1000;
	printf("%f\t%d\t%s", phi->time_in_mill, phi->id, "is sleeping\n");
	usleep(TIME_TO_SLEEP);
	gettimeofday(&current_time, NULL);
	phi->time_in_mill =
			(double)(current_time.tv_sec) * 1000 + (double)(current_time.tv_usec) / 1000;
	printf("%f\t%d\t%s", phi->time_in_mill, phi->id, "is thinking\n");

	usleep(TIME_TO_THINK);
	if (phi->time_in_mill - phi->time_in_mill_before > TIME_TO_DIE) // not sure, we need to count time form the initialization of the prog + from eating to eating
	{
		printf("%d\t%s\n", phi->id, "died");
		fflush(stdout);
		exit (FAILURE);
	}
	return ((void *)SUCCESS);
}

int main()
{
	pthread_mutex_init(&state_mutex, NULL);
	pthread_t threads[NUM_PHILO];
	int status;
	int j;
	int status_addr = 0;
	t_philo args[NUM_PHILO];
	int i;
	t_philo phi;
	phi.already_eaten = 0;

	for (j = 0; j < NUM_PHILO; j++) {
		args[j].id = j;
	}

	j = 0;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	phi.time_in_mill_init = (double)(current_time.tv_sec) * 1000 + (double)(current_time.tv_usec) / 1000;
	for (j = 0; j < NUM_PHILO; j++)
	{
		status = pthread_create(&threads[j], NULL, philosopher, (void *) &args[j]);
		if (status == FAILURE)
		{
			printf("main error: can't create thread, status = %d\n", status);
			pthread_mutex_destroy(&state_mutex);
			exit(FAILURE);
		}
		if (j + 1 == NUM_PHILO)
			j = 0;
	}
	for (int k = 0; k < j; k++)
	{
		pthread_join(threads[j], (void *)&status_addr);
		if (status_addr == FAILURE)
		{
			printf("main error: can't join thread, status = %d\n", status);
			pthread_mutex_destroy(&state_mutex);
			exit(ERROR_JOIN_THREAD);
		}
	}
	return (0);
}