/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:55:18 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/12 14:09:02 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_lunch(t_table *table)
{
	table->forks = malloc (sizeof(pthread_mutex_t) * table->nbr_philo);
	if (table->forks == NULL)
		return (perror("malloc"), exit(EXIT_FAILURE));
	table->philos = malloc (sizeof(t_philo) * table->nbr_philo);
	if (table->philos == NULL)
	{
		free(table->forks);
		return (perror("malloc"), exit(EXIT_FAILURE));
	}
	init_mutex(table);
	thread_create(table);
	init_join(table);
}

void	thread_create(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		init_philo(&table->philos[i], table, i);
		if (pthread_create((&table->philos[i].thread), NULL,
				thread_func, (void *)&table->philos[i]))
			return (free_all(table), ft_error("Thread create error"));
		i++;
	}
	if (pthread_create((&table->monitor), NULL, monitor, (void *)table))
		return (free_all(table), ft_error("Thread create error"));
}

void	init_join(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_join(table->philos[i++].thread, NULL))
			return (free_all(table), ft_error("Thread join error"));
	}
	if (pthread_join(table->monitor, NULL))
		return (free_all(table), ft_error("Thread join error"));
}

void	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			ft_mutexit(table, i, 0);
		i++;
	}
	if (pthread_mutex_init(&table->time_lock, NULL))
		ft_mutexit(table, i, 1);
	if (pthread_mutex_init(&table->dead_lock, NULL))
		ft_mutexit(table, i, 2);
	if (pthread_mutex_init(&table->eat_lock, NULL))
		ft_mutexit(table, i, 3);
}
