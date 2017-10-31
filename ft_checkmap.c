/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchapka <tchapka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 10:09:09 by rfabre            #+#    #+#             */
/*   Updated: 2017/10/30 15:36:53 by tchapka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_error(int i)
{
	if (i == -1)
		ft_putendl_fd("Map missing", 2);
	if (i == -2)
		ft_putendl_fd("Invalid map", 2);
	if (i == -3)
		ft_putendl_fd("Error on color code", 2);
	if (i == -42)
		ft_putendl_fd("Malloc failed", 2);
	exit(-1);
}

static void		check_color(char *str, int *i)
{
	int	count;

	count = 0;
	if (str[*i] == '0' && str[*i + 1] == 'x')
		*i += 2;
	while (ft_isdigit(str[*i]) || (str[*i] > 64 && str[*i] < 71) ||
		(str[*i] > 96 && str[*i] < 103))
	{
		(*i)++;
		count++;
	}
	if (count != 6)
		ft_error(-3);
}

static void		ft_checkcol(int *save, int *nl, int *nc)
{
	if (!*save)
		*save = *nc;
	else
	{
		if (*save != *nc)
			ft_error(-2);
	}
	*nc = 0;
	(*nl)++;
}

void			check_map(char *str, int *nc, int *nl)
{
	int		i;
	int		save;

	i = 0;
	save = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (ft_isdigit(str[i]) || (str[i] == '-' && ft_isdigit(str[i + 1])))
			(*nc)++;
		while (ft_isdigit(str[i]) || (str[i] == '-' && ft_isdigit(str[i + 1])))
			i++;
		if (str[i] == ',')
		{
			i++;
			check_color(str, &i);
		}
		if (!ft_isdigit(str[i]) && (str[i] != ' ' && str[i] != '\t' &&
			str[i] != '\n'))
			ft_error(-2);
		if (str[i++] == '\n')
			ft_checkcol(&save, nl, nc);
	}
	*nc = save;
}