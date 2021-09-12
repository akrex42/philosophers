#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>

# define SUCCESS 0
# define FAILURE 1
# define ERROR_JOIN_THREAD -10

pthread_mutex_t forks[201]; // FIXME
pthread_mutex_t print;

typedef struct s_args {
	int 	time_to_die;
	int 	time_to_eat;
	int 	time_to_sleep;
	int		num_philo;
	int		num_of_meals;
} t_args;

typedef struct s_philo {
	int		id;
	long	current_time;
	long	last_meal;
	long	time_left_fork;
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
int		ft_atoi(const char *str);
int		create_threads(t_philo *args, pthread_t *death_watcher, pthread_t *threads, char **argv);
int		init_mutexes(t_philo *phi, int j);

#endif