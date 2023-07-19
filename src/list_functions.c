#include "philosophers.h"

t_philo	*put_philo(void)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->id = 0;
	new_philo->is_dead = false;
	new_philo->eat_count = 0;
	new_philo->last_eat = 0;
	new_philo->left_fork = NULL;
	new_philo->right_fork = NULL;
	new_philo->left_fork_taken = false;
	new_philo->right_fork_taken = false;
	new_philo->next = NULL;
	return (new_philo);
}

void	addlast_philo(t_table **table, int id)
{
	t_philo	*new_philo = put_philo();
    new_philo->id = id;
    if(!(*table)->head)
    {
        (*table)->head = new_philo;
        (*table)->tail = new_philo;
        return ;
    }
    (*table)->tail->next = new_philo;
    (*table)->tail = new_philo;
}

void print_philo(t_table *center)
{
    t_philo *local;

    local = center->head;
    printf("Head: %d\n", center->head->id);
    printf("Tail: %d\n", center->tail->id);
    while(local)
    {
        printf("\tPhil. %d > %p\n", local->id, local);
        local = local->next;
    }
}
