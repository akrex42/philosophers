#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

# define SUCCESS 0
# define FAILURE 1
# define ERROR_JOIN_THREAD -10

pthread_mutex_t forks[201]; // FIXME
pthread_mutex_t waiter;
pthread_mutex_t print;
pthread_mutex_t death_check;

typedef struct s_args {
	int 	time_to_die;
	int 	time_to_eat;
	int 	time_to_sleep;
	int		num_philo;
} t_args;

typedef struct s_philo {
	int		id;
	long	time_in_mill;
	long	time_in_mill_before;
	long 	prev_meal;
	long	time_in_mill_left;
	long	time_init;
	int 	priority;
	int 	full;
	t_args	arg;
} t_philo;

void	*philosopher(void *args);
void 	take_forks(t_philo *phi);
void 	create_timestamp(t_philo *phi);
void 	drop_forks(t_philo *phi);
int 	check_if_dead(t_philo *phi);
void	*death_routine(void *args);
void 	get_time(t_philo *phi, int code);

#endif