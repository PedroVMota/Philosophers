/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:21:32 by pedro             #+#    #+#             */
/*   Updated: 2023/09/24 08:47:28 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

//	alloc_err
#define ALLOC_THREAD "ERROR WHILE ALLOCATING THREADS IDs"
#define ALLOC_PHILO "ERROR WHILE ALLOCATING PHILOS"
#define ALLOC_FORK "ERROR WHILE ALLOCATING FORKS"
//	input_err
#define ERR_INVALID_INPUT "INVALID INPUT CHARACTER"
#define ERR_INVALID_VALUES "INVALID INPUT VALUES"
//	pthread_err
#define TH_ERR "ERROR WHILE CREATING THREADS"
#define JOIN_ERR "ERROR WHILE JOINING THREADS"
#define INIT_ERR_1 "ERROR WHILE INIT FORKS"
//	time_err
#define TIME_ERR "UNABLE TO RETRIVE UTC"
//	philo_msg
#define TAKE_FORKS "has taken a fork"
#define THINKING "is thinking"
#define SLEEPING "is sleeping"
#define EATING "is eating"
#define DIED "died"

#define INFO(msg) printf("\033[0;33m%s\033[0m", msg)

typedef struct s_philo
{
	struct s_main *database;
	pthread_t thread_id;

	int _id;
	int _eat_count;
	int _mode;
	bool _is_eating;
	__uint64_t _time_to_die;
	pthread_mutex_t lock;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
} t_philo;

typedef struct s_main
{
	pthread_t *philosophers;
	pthread_mutex_t *forks;
	t_philo *philo;

	int _number_of_philosophers;
	long long _time_to_die;
	long long _time_to_eat;
	long long _time_to_sleep;
	long long _number_of_times_each_philosopher_must_eat;

	int _is_dead;
	int _is_full;

	__uint64_t start;

	pthread_mutex_t write;
	pthread_mutex_t lock;

} t_data;

long ft_atoi(const char *str);
int input(char **argv);

int input(char **argv);
bool init(char **av, t_data *database);
bool error(char *msg, t_data *database);
void ft_exit(t_data *database);
__uint64_t get_time(void);
void *routine(void *ph_ptr);

void take_forks(t_philo *philo);
void drop_forks(t_philo *philo);
void eat(t_philo *philo);
int ft_usleep(useconds_t time);
void messages(char *str, t_philo *philo);
int ft_strcmp(const char *s1, const char *s2);
#endif