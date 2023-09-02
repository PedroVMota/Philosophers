#ifndef PHILOSOPHERS_h
# define PHILOSOPHERS_h

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
#include <sys/types.h>

# include <unistd.h>

# define MEMDEB(content) printf("%s:%p\n", content, content);

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t       t1;
	int             id;
	int             eat_cont;
	int             status;
	int             eating;
	uint64_t        time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} t_philo;

struct			s_table
{
	pthread_t	*thread_id;
	int			philo_n;
	int			meals_n;
	int			dead;
	int			finished;
	t_philo		*philo;
	int64_t		death_time;
	int64_t		eat_time;
	int64_t		sleep_time;
	int64_t		start_time;
    pthread_mutex_t *forks;
	pthread_mutex_t lock;
	pthread_mutex_t write;
};

// parsing
long			ft_atoi(const char *str);

#endif
