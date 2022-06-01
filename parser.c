/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamraka <atamraka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:34:26 by atamraka          #+#    #+#             */
/*   Updated: 2022/03/23 10:48:03 by atamraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	get_coordinates(char *input, int inSize, int *coords)
{
	int	row;
	int	column;
	int	ndx;
	int	i;

	row = 0;
	ndx = 0;
	i = 0;
	while (ndx < inSize && i < 8)
	{
		column = 0;
		while (column < 5)
		{
			if (input[ndx] == '#')
			{
				coords[i++] = row;
				coords[i++] = column;
			}
			column++;
			ndx++;
		}
		row++;
	}
	return (1);
}

void	free_tet_list(t_item *list)
{
	t_item	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		ft_memdel((void **)&temp);
	}
}

t_item	*new_t_item(char *input, int inSize, char letter)
{
	t_item	*newlist;

	newlist = (t_item *)malloc(sizeof(t_item));
	if (!newlist)
		return (NULL);
	get_coordinates(input, inSize, newlist->coordinates);
	align_coordinates_top_left(newlist->coordinates);
	newlist->letter = letter;
	newlist->x_offset = 0;
	newlist->y_offset = 0;
	newlist->next = NULL;
	return (newlist);
}

t_item	*make_tet_list(char *input, int inSize)
{
	t_item	*current;
	t_item	*beginning;
	int		i;
	char	pieceletter;

	i = 0;
	pieceletter = 'A';
	while (i < inSize)
	{
		if (pieceletter == 'A')
		{
			beginning = new_t_item(input + i, 20, pieceletter);
			current = beginning;
		}
		else
		{
			current->next = new_t_item(input + i, 20, pieceletter);
			current = current->next;
		}
		pieceletter++;
		i += 21;
	}
	current->next = NULL;
	return (beginning);
}

t_item	*parser(char *filename)
{
	char	buff[MAX_FILE_SIZE];
	int		fd;
	int		bytecount;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	bytecount = read(fd, buff, MAX_FILE_SIZE + 1);
	close(fd);
	if (bytecount > MAX_FILE_SIZE + 1)
		return (0);
	if (bytecount > MAX_FILE_SIZE || bytecount < MIN_FILE_SIZE)
		return (NULL);
	buff[bytecount] = '\0';
	if (!validate_tetriminos_shape(buff, bytecount))
		return (NULL);
	return (make_tet_list(buff, bytecount));
}
