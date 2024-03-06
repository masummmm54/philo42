/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:10 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/06 09:20:04 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}


int	main(int ac, char **av)
{
	t_table	table;

	if (!(ac == 5 || ac == 6))
		ft_exit("Wrong argument size");
	if (check_args(av) == FALSE)
		ft_exit("Numeric arguments required");
	init_table(av, &table);






	return (EXIT_SUCCESS);
}
