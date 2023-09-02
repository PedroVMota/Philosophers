#include <philosophers.h>

struct s_table g_table;

int arrange(void)
{
    if(g_table.philo_n < 2)
        return 1;
    else if(g_table.death_time == 0)
        return 1;
    else if(g_table.eat_time == 0)
        return 1;
    else if(g_table.sleep_time== 0)
        return 1;
    else if(g_table.meals_n == 0)
        return 1;
    g_table.thread_id = malloc(sizeof(pthread_t) * g_table.philo_n);
    if(!g_table.thread_id)
        return 1;
    g_table.forks = malloc(sizeof(pthread_mutex_t) * g_table.philo_n);
    if(!g_table.forks)
        return 1;
    g_table.philo = malloc(sizeof(t_philo) * g_table.philo_n);
    if(!g_table.philo)
        return 1;
    
}
int setup(char **av)
{
    g_table.philo_n = ft_atoi(av[0]);
    g_table.death_time = ft_atoi(av[1]);
    g_table.eat_time = ft_atoi(av[2]);
    g_table.sleep_time= ft_atoi(av[3]);
    g_table.meals_n = ft_atoi(av[4]);
    if(g_table.meals_n == 0)
        g_table.meals_n = 1;
    arrange();
    return 0;
}


int main(int ac, char **av)
{
    if (ac < 5 || ac > 7)
    {
        write(2, "Wrong Params\n", 14);
        return 1;
    }
    if(setup(&av[1]))
    { 
        write(2, "Something went wrong make sure the params are correct\n", 54);
        return 2;
    }
    write(1, "\n", 1);
    return 0;
}