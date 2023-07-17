#ifndef PHILOSOPHERS_h
# define PHILOSOPHERS_h

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
typedef int pfork_t;
typedef struct s_table
{
    long long philo_n;
    long long time_to_die;
    long long time_to_eat;
    long long time_to_sleep;
    long long n_of_eats;
    long *forks;
    pthread_t *philosophers;
} t_table;

typedef struct s_convertion_usec_to_ms
{
    long long microseconds;
    long long miliseconds;
} t_convertion_usec_to_ms;


//parsing
long	ft_atoi(const char *str);
t_table *table(void);
int	setup(t_table *table, char **av);
void parse_error(t_table *table, char *msg);

#endif
