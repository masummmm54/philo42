/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:49:07 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/13 11:10:36 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *msg)
{
	ft_putendl_fd(msg, 2);
}

void	ft_mutexit(t_table *table, int i, int flag)
{
	while (i >= 0)
		pthread_mutex_destroy(&table->forks[i--]);
	if (flag >= 1)
		pthread_mutex_destroy(&table->time_lock);
	if (flag >= 2)
		pthread_mutex_destroy(&table->dead_lock);
	if (flag >= 3)
		pthread_mutex_destroy(&table->eat_lock);
	free(table->philos);
	free(table->forks);
}

void	free_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
		pthread_mutex_destroy(&table->forks[i++]);
	pthread_mutex_destroy(&table->time_lock);
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->eat_lock);
	free(table->philos);
	free(table->forks);
}
