/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:21:32 by pedro             #+#    #+#             */
/*   Updated: 2023/12/10 17:37:49 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

//	alloc_err
# define ALLOC_THREAD "ERROR WHILE ALLOCATING THREADS IDs"
# define ALLOC_PHILO "ERROR WHILE ALLOCATING PHILOS"
# define ALLOC_FORK "ERROR WHILE ALLOCATING FORKS"
//	input_err
# define ERR_INVALID_INPUT "INVALID INPUT CHARACTER"
# define ERR_INVALID_VALUES "INVALID INPUT VALUES"
//	pthread_err
# define TH_ERR "ERROR WHILE CREATING THREADS"
# define JOIN_ERR "ERROR WHILE JOINING THREADS"
# define INIT_ERR_1 "ERROR WHILE INIT FORKS"
//	time_err
# define TIME_ERR "UNABLE TO RETRIVE UTC"
//	philo_msg
# define TAKE_FORKS "has taken a fork"
# define DROP_FORKS "has dropped a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_philo
{
	int				_id;
	pthread_t		thread_id;

	__uint64_t		_time_to_die;
	__uint64_t		_time_to_eat;
	__uint64_t		_time_to_sleep;
	__uint64_t		last_meal;

	int				_eat_count;
	int				_meals_eaten;

	bool			_is_eating;

	int				*any_died;

	unsigned long	time_start;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*edit;
	struct s_main	*database;
}					t_philo;

typedef struct s_main
{
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*edit;
	t_philo			*philo;

	int				n_p;
	long long		t_die;
	long long		t_eat;
	long long		t_sle;
	long long		n_eat;

	int				b_dead;
	int				f_ph;

	__uint64_t		start;

	pthread_mutex_t	write;
	pthread_mutex_t	lock;

}					t_data;

// Solo Thread Functions.
void				*soloroutine(void *ph_ptr);
void				print_dead(t_philo *philo);

long				ft_atoi(const char *str);
int					input(char **argv);

int					input(char **argv);
bool				init(char **av, t_data *database);
bool				error(char *msg, t_data *database);
void				ft_exit(t_data *database);
__uint64_t			get_time(void);
void				routine_setup(t_data *db);

int					ft_usleep(useconds_t time);
void				messages(char *str, t_philo *philo);
int					ft_strcmp(const char *s1, const char *s2);
void				*soloroutine(void *ph_ptr);
void				*monitor(void *ph_ptr);
#endif