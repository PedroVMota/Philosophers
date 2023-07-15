#include "philosophers.h"

int are_valid(char **av, int ac)
{
    int i = 0;
    while(i < ac)
    {
        if(!av[i])
            return 1;
    }
    return 0;
}

int main (int ac, char **av)
{
    if(ac != 5 || are_valid(&av[1], ac - 1))
        return 1;
    return 0;
}