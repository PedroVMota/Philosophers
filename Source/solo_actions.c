#include "philo.h"

void print_dead(t_philo *philo)
{
    pthread_mutex_lock(&philo->database->write);
    printf("%lu %u %s\n", philo->_time_to_die, philo->_id, DIED);
    philo->database->_is_dead = 1;
    pthread_mutex_unlock(&philo->database->write);
}