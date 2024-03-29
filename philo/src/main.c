/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:10 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/13 15:17:38 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (!(ac == 5 || ac == 6))
		return (ft_error("Wrong argument size"), 1);
	if (check_args(av) == FALSE)
		return (ft_error("Numeric arguments required"), 1);
	if (init_table(av, &table))
		return (0);
	if (init_lunch(&table))
		return (EXIT_FAILURE);
	free_all(&table);
	if (table.dead == false)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
