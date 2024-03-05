/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:10 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/04 13:49:39 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* int	main(int ac, char **av)
{
	if (!(ac == 5 || ac == 6))
		return (EXIT_FAILURE);
	av[0] = NULL;
	ft_printf("masum\n");

	return (EXIT_SUCCESS);
} */

int primes[10] = {2, 3, 5 , 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
	sleep(1);
	int index = *(int *)arg;
	printf("%d \n", primes[index]);

	return NULL;
}

int main()
{
	pthread_t th[10];
	int i = 0;
	while (i < 10)
	{	
		int *a = malloc (sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("failed:");
		}
		i++;
	}
	i = 0;
	while (i < 10)
	{	
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("failed:");
		}
		i++;
	}
	return (0);
}
