/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:54:35 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/12 14:10:56 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printer(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->time_lock);
	printf("%lu %d %s\n", time_now(philo->table), philo->id + 1, msg);
	pthread_mutex_unlock(&philo->table->time_lock);
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
