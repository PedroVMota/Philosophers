#include "philo.h"

void	messages(char *str, t_philo *philo)
{
	u_int64_t time;

	pthread_mutex_lock(&philo->database->write);
	time = get_time() - philo->time_start;
	if (ft_strcmp(DIED, str) == 0 && philo->database->_is_dead == 0)
	{
		printf("%lu %u %s\n", time, philo->_id, str);
		philo->database->_is_dead = 1;
	}
	if (!philo->database->_is_dead)
		printf("%lu %u %s\n", time, philo->_id, str);
	pthread_mutex_unlock(&philo->database->write);
}