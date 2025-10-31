/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/31 16:48:46 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int argc, char const **argv)
{
    t_table	*table;
    int i;

    i = 0;
    if (checking_input(argc, argv) == -1)
        return (1);
    table = create_table(argc, (char **)argv);
    if (!table)
    {
        printf("Failed to init table\n");
        return (1);
    }
    // 3) spawn philosophers (creates threads running philosopher_routine)
    if (spawn_philosophers(table) == 0)  // Успішний spawn
    {
        // Чекати завершення всіх потоків
         
        while (i < table->num_phil)
        {
            pthread_join(table->philos[i].thread, NULL);
            i++;
        }
    }
    else
    {
        destroy_table(table);
        return (1);
    }

    destroy_table(table);
    return (0);
}