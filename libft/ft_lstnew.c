/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:50:33 by dawwad            #+#    #+#             */
/*   Updated: 2024/06/20 14:51:00 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*curr;

	curr = (t_list *)malloc(sizeof(t_list));
	if (!curr)
		return (NULL);
	curr->content = content;
	curr->next = NULL;
	return (curr);
}
