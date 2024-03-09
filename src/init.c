/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:05:25 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/06 18:02:23 by muhakose         ###   ########.fr       */
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
