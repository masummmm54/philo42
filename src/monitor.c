/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:57:11 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/12 13:39:36 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_lock(&table->eat_lock);
		if ((table->philos[i].eat_count) != 0)
		{
			pthread_mutex_unlock(&table->eat_lock);
			return (false);
		}
		pthread_mutex_unlock(&table->eat_lock);
		i++;
	}
	return (true);
}

int	is_dead(t_philo *philo)
{
	bool	how;

	pthread_mutex_lock(&philo->table->eat_lock);
	if (philo->eat_count == 0)
	{
		pthread_mutex_unlock(&philo->table->eat_lock);
		return (false);
	}
	pthread_mutex_unlock(&philo->table->eat_lock);
	pthread_mutex_lock(&philo->table->time_lock);
	how = time_now(philo->table) - philo->last_meal > philo->table->time_die;
	pthread_mutex_unlock(&philo->table->time_lock);
	if (how)
	{
		pthread_mutex_lock(&philo->table->dead_lock);
		philo->table->dead = false;
		pthread_mutex_unlock(&philo->table->dead_lock);
		printer("is dead", philo);
		return (true);
	}
	return (false);
}

void	*monitor(void *table_t)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)table_t;
	while (1)
	{
		if (all_full(table))
			break ;
		i = 0;
		while (i < table->nbr_philo)
		{
			if (is_dead(&table->philos[i]))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
