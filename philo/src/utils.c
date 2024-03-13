/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:54:35 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/13 15:00:18 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printer(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->dead)
	{
		pthread_mutex_lock(&philo->table->time_lock);
		printf("%lu %d %s\n", time_now(philo->table), philo->id + 1, msg);
		pthread_mutex_unlock(&philo->table->time_lock);
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
}

time_t	time_now(t_table *table)
{
	return (get_time() - table->day_start);
}

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

void	one_philo(t_philo *philo)
{
	printer("is thinking", philo);
	pthread_mutex_lock(&philo->table->forks[philo->id]);
	printer("has taken a fork", philo);
	pthread_mutex_unlock(&philo->table->forks[philo->id]);
}
