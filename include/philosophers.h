#ifndef PHILOSOPHERS_h
# define PHILOSOPHERS_h

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_table
{
    long long philo_n;
    long long time_to_die;
    long long time_to_eat;
    long long time_to_sleep;
    long long n_of_eats;
    pthread_t *philosophers;
} t_table;


//parsing
long	ft_atoi(const char *str);
void parse_error(t_table *table, char *msg);

#endif