/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 17:05:29 by jhille        #+#    #+#                 */
/*   Updated: 2022/08/18 17:30:01 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>
#include "parser.h"
#include "heredoc.h"

static t_ast	*next_exec_block(t_ast *exec_block)
{
	exec_block = exec_block->next_sib_node;
	if (exec_block)
		exec_block = exec_block->next_sib_node;
}

/*
	Tries to find the RDS node. 
	If RDS is found it returns the RDS child node.
	Else it returns NULL
*/
static t_ast	*get_rd(t_ast *exec_block)
{
	if (exec_block->child_node->type == RDS)
		return (exec_block->child_node->child_node);
	else if (exec_block->child_node->next_sib_node)
		return (exec_block->child_node->next_sib_node->child_node);
	else
		return (NULL);
}

void	single_heredoc(char *tmp_filepath, t_ast *rd, char *envv[], int i)
{
	t_ast	*node;
	char	*tmp_file;
	int		file_fd;

	node = rd_iter->child_node->next_sib_node;
	tmp_file = create_tmp_filename(tmp_filepath, i);
	file_fd = open(tmp_file, O_CREAT | O_WRONLY, 0666);
	read_write_to_tmp(node->value, \
					file_fd, envv);
	close(file_fd);
	free(node->value);
	node->value = tmp_file;
}

void	handle_all_heredocs(t_ast *exec_block, char *envv[])
{
	t_ast	*rd_iter;
	char	*tmp_filepath;
	int		i;

	i = 0;
	tmp_filepath = find_tmp_filepath();
	while (exec_block)
	{
		rd_iter = get_rd(exec_block);
		while (rd_iter)
		{
			if (rd_iter->type == RD_DE)
			{
				single_heredoc(tmp_filepath, rd_iter, envv, i);
				rd_iter = rd_iter->next_sib_node;
				i++;
			}
		}
		exec_block = next_exec_block(exec_block);
	}
	free(tmp_filepath);
}
