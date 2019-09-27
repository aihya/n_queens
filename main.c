/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 08:22:22 by aihya             #+#    #+#             */
/*   Updated: 2019/07/19 15:22:42 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	node
{
	int			y;
	int			x;
	struct node	*p;
	struct node	*n;
}				t_node;

t_node	*new_node(t_node *p_node, int x)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->y = -1;
	new_node->x = x;
	new_node->n = NULL;
	new_node->p = NULL;
	if (p_node)
		new_node->p = p_node;
	return (new_node);
}

t_node	*creat_list(int depth)
{
	t_node	*head;
	t_node	*curr;
	int		i;

	i = 0;
	head = new_node(NULL, i);
	curr = head;
	while (++i < depth)
	{
		curr->n = new_node(curr, i);
		curr = curr->n;
	}
	return (head);
}

void	reset_from(t_node *node)
{
	while (node)
	{
		node->y = -1;
		node = node->n;
	}
}

int		is_safe(t_node *node)
{
	t_node	*p;
	int		offset;

	if (node->y == -1)
	{
		node->y = 0;
		return (is_safe(node));
	}

	offset = 1;
	p = node->p;
	while (p)
	{
		if (p->y == node->y)
			return (0);
		if (node->y - offset >= 0)
			if (node->y - offset == p->y)
				return (0);
		if (node->y + offset == p->y)
			return  (0);
		offset++;
		p = p->p;
	}
	return (1);
}

void	show(t_node *node, int depth)
{
	int		i;

	while (node->p)
		node = node->p;
	i = 0;
	while (i < depth)
	{
		while (node)
		{
			if (node->y == i)
				printf("\033[1;32mQ\033[0m ");
			else
				printf("\033[1;30m#\033[0m ");
			if (node->x == depth - 1)
				printf("\n");
			if (node->n)
				node = node->n;
			else
				break ;
		}
		while (node->p)
			node = node->p;
		i++;
	}
	printf("\n");
}

void	solve(t_node *node, int depth, int *counter)
{
	if (node)
	{
		while (node->y < depth)
		{
			if (is_safe(node))
			{
				if (node->x == depth - 1)
				{
					*counter = *counter + 1;
					show(node, depth);
				}
				solve(node->n, depth, counter);
			}
			node->y = node->y + 1;
		}
		reset_from(node);
	}
}

int main()
{
	int		counter;
	int		depth;

	counter = 0;
	depth = 10;
	solve(creat_list(depth), depth, &counter);
	printf("%d Solutions Found.\n", counter);
	return (0);
}
