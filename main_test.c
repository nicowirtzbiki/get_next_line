/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:07:13 by nico              #+#    #+#             */
/*   Updated: 2025/11/17 12:14:43 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(void)
{
    int fd = open("test_file.txt", O_RDONLY); //abre o arquivo só para leitura
    if (fd == -1)
        return (1); //erro ao abrir
    char *line = get_next_line(fd);
    while (line)
    {
        printf("%s", line); // imprime a linha, já vem como \n
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}