/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <marvin>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:07:30 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/28 15:11:28 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_cmd	*cmd_list_add_back(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!new_cmd)
		return (*cmds);
	if (!*cmds)
	{
		*cmds = new_cmd;
		return (new_cmd);
	}
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
	return (*cmds);
}
