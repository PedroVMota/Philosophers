#ifndef PHILOSOPHERS_h
# define PHILOSOPHERS_h

# include <ft_colors.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define HERE printf("HERE\n\n");
typedef struct s_philo
{
	int				id;
	bool			is_dead;
	int				eat_count;
	int				last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	bool			left_fork_taken;
	bool			right_fork_taken;
	struct s_philo	*next;
}					t_philo;

typedef struct s_table
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	pthread_t		*threads;
	t_philo			*head;
	t_philo			*tail;
}					t_table;

long				ft_atoi(const char *str);
void				print_philo(t_table *center);
void				addlast_philo(t_table **table, int id);
#endif
