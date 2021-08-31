#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

//# define NUM_PHILO 4
# define SUCCESS 0
# define FAILURE 1
# define ERROR_JOIN_THREAD -10
//# define TIME_TO_DIE 410
//# define TIME_TO_EAT 200
//# define TIME_TO_SLEEP 200
# define TIME_TO_THINK 10000

typedef struct s_args {
	int 	time_to_die;
	int 	time_to_eat;
	int 	time_to_sleep;
	int		num_philo;
} t_args;

typedef struct s_philo {
	int		id;
	int		forks[5];
	double	time_in_mill;
	double	time_in_mill_before;
	double	time_in_mill_init;
	int 	already_eaten;
	t_args	arg;
} t_philo;


#endif