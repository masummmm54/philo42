/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:10 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/07 10:17:50 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}


void	init_launch(t_table *table)
{
	int			i;


	table->threads = malloc (sizeof(pthread_t) * table->nbr_philo);
	table->philos = malloc (sizeof(t_philo ) * table->nbr_philo);
	table->forks = malloc (sizeof(pthread_mutex_t) * table->nbr_philo);
	i = 0;
	pthread_mutex_init(&table->dead_mtx, NULL);
	while (i < table->nbr_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < table->nbr_philo)
	{
		table->philos[i].table = table;
		init_philo(&table->philos[i], i);
		pthread_create(&table->threads[i], NULL, thread_func, (void *)(&table->philos[i]));
		i++;
	}
	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(table->threads[i], NULL);
		i++;
	}

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}




int	main(int ac, char **av)
{
	t_table	table;

	if (!(ac == 5 || ac == 6))
		ft_error("Wrong argument size");
	if (check_args(av) == FALSE)
		ft_error("Numeric arguments required");
	init_table(av, &table);
	init_launch(&table);



	return (EXIT_SUCCESS);
}
