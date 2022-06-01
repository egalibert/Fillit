/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaliber <egaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:51:24 by egaliber          #+#    #+#             */
/*   Updated: 2022/03/23 13:23:43 by egaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int argc, char **argv)
{
	t_item	*piecelist;

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit source_file\n");
		return (0);
	}
	piecelist = parser(argv[1]);
	if (!piecelist)
	{
		ft_putstr("error\n");
		return (0);
	}
	solver(piecelist);
	if (piecelist)
		free_tet_list (piecelist);
		system("leaks fillit");
	return (1);
}
