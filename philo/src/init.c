/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:05:25 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/14 13:24:02 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(char **av, t_table *table)
{
	table->nbr_philo = ft_atoi(av[1]);
	table->time_die = ft_atoi(av[2]);
	table->time_eat = ft_atoi(av[3]);
	table->time_sleep = ft_atoi(av[4]);
	if (av[5] == NULL)
		table->must_eat = -42;
	else if (ft_atoi(av[5]) >= 1)
		table->must_eat = ft_atoi(av[5]);
	else
		return (1);
	table->dead = 1;
	table->day_start = get_time();
	return (0);
}

void	init_philo(t_philo *philo, t_table *table, int i)
{
	philo->id = i;
	philo->nbr_philo = table->nbr_philo;
	if (-1 == i - 1)
	{
		philo->left = table->nbr_philo - 1;
	}
	else
		philo->left = i - 1;
	if (table->nbr_philo == i + 1)
		philo->right = 0;
	else
		philo->right = i + 1;
	philo->last_meal = time_now(table);
	philo->eat_count = table->must_eat;
	philo->table = table;
}
