#include "philo.h"

void	messages(char *str, t_philo *philo)
{
	unsigned long int	time;

	pthread_mutex_lock(&philo->database->write);
	time = get_time() - philo->database->start;
	if (ft_strcmp(DIED, str) == 0 && philo->database->_is_dead == 0)
	{
		printf("%lu %d %s\n", time, philo->_id, str);
		philo->database->_is_dead = 1;
	}
	if (!philo->database->_is_dead)
		printf("%lu %d %s\n", time, philo->_id, str);
	pthread_mutex_unlock(&philo->database->write);
}

void take_forks(t_philo *philo){

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
}

void drop_forks(t_philo *philo){
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	usleep(philo->database->_time_to_sleep * 1000);
}

void	eat(t_philo *philo){
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->_is_eating = true;
	philo->_time_to_die = get_time() + philo->database->_time_to_die;
	messages(EATING, philo);
	philo->_eat_count++;
	ft_usleep(philo->database->_time_to_eat);
	philo->_is_eating = false;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}