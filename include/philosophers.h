#ifndef PHILOSOPHERS_h
# define PHILOSOPHERS_h

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include "ft_colors.h"
#include <stdbool.h>

typedef struct s_forks
{
    int is_using;
    pthread_mutex_t *forks;
}                   t_forks;

typedef struct s_philo
{
	int				id;
	bool is_life;
    struct timeval  start;
	struct timeval	last_meal;
	struct timeval	current_time;
	int				n_of_eats;
	t_forks	*left_fork;
	t_forks	*right_fork;
}					t_philo;



typedef struct s_table
{
	int				philo_n;
	int				time_to_die_ms;
	int				time_to_eat_ms;
	int				time_to_sleep_ms;
	int				n_of_eats;
	pthread_t		*phi_thread;
	t_philo			*arr_phi;
    t_forks         *forks;

}					t_table;

// parsing
long				ft_atoi(const char *str);
t_table				*table(void);
int					setup(t_table *table, char **av);
void				parse_error(t_table *table, char *msg);

#endif
