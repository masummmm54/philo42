/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:40 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/06 09:18:54 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

# define TRUE 1
# define FALSE 0

typedef pthread_mutex_t t_mtx;



typedef struct s_philo
{



}	t_philo;

typedef struct s_table
{
	long		nbr_philo;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	long		must_eat;
	bool		end;
	t_philo		*philos;
}	t_table;


void	init_table(char **av, t_table *table);

//utils
void	ft_putendl_fd(char *s, int fd);
long	ft_atoi(const char *str);
int		check_args(char **av);

#endif
