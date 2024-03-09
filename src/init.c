/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:05:25 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/09 13:02:42 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(char **av, t_table *table)
{
	table->nbr_philo = ft_atoi(av[1]);
	table->time_die = ft_atoi(av[2]) * 1000;
	table->time_eat = ft_atoi(av[3]) * 1000;
	table->time_sleep = ft_atoi(av[4]) * 1000;
	table->must_eat = ft_atoi(av[5]);
	table->dead = 1;
	table->day_start = get_time();
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
		pthread_mutex_init(&table->forks[i++], NULL);
	i = -1;
	while (++i < table->nbr_philo)
	{
		table->philos[i].table = table;
		init_philo(&table->philos[i], i);
		pthread_create(&table->threads[i], NULL, thread_func, (void *)(&table->philos[i]));
	}
	i = 0;
	while (i < table->nbr_philo)
		pthread_join(table->threads[i++], NULL);
}

void	init_philo(t_philo *philo, int i)
{
	philo->id = i;
	if (-1 == i - 1)
	{
		philo->left = philo->table->nbr_philo - 1;
	}
	else
		philo->left = i - 1;
	if (philo->table->nbr_philo == i + 1)
		philo->right = 0;
	else
		philo->right = i + 1;
	philo->last_meal = time_now(philo->table);
}
